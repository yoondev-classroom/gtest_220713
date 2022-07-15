
#include <string>

class User {
private:
    std::string name;
    int age;

public:
    User(const std::string& name, int age)
        : name(name)
        , age(age)
    {
    }

    std::string GetName() const { return name; }
    int GetAge() const { return age; }
};

struct IDatabase {
    virtual ~IDatabase() { }

    virtual void SaveUser(const std::string& name, User* user) = 0;
    virtual User* LoadUser(const std::string& name) = 0;
};

class UserRepository {
private:
    IDatabase* database;

public:
    UserRepository(IDatabase* database)
        : database(database)
    {
    }

    void Save(User* user)
    {
        // ...
        database->SaveUser(user->GetName(), user);
    }

    User* Load(const std::string& name)
    {
        // ...
        return database->LoadUser(name);
    }
};

#include <gmock/gmock.h>
#include <map>

// 같은 파일에서만 접근이 가능합니다.
static bool operator==(const User& lhs, const User& rhs)
{
    // return false;
    return lhs.GetName() == rhs.GetName() && lhs.GetAge() == rhs.GetAge();
}

static std::ostream& operator<<(std::ostream& os, const User& user)
{
    return os << "name=" << user.GetName() << ", "
              << "age=" << user.GetAge();
}

class FakeDatabase : public IDatabase {
public:
    MOCK_METHOD(void, SaveUser, (const std::string& name, User* user), (override));
    MOCK_METHOD(User*, LoadUser, (const std::string& name), (override));
};

using testing::NiceMock;

TEST(UserRepositoryTest, Save)
{
    NiceMock<FakeDatabase> database;
    std::map<std::string, User*> data;
    ON_CALL(database, SaveUser).WillByDefault([&data](const std::string& name, User* user) {
      data[name] = user;
    });
    ON_CALL(database, LoadUser).WillByDefault([&data](const std::string& name) {
      return data[name];
    });
    UserRepository repo(&database);
    std::string testName = "test_name";
    int testAge = 42;
    User expected(testName, testAge);

    repo.Save(&expected);
    User* actual = repo.Load(testName);

    ASSERT_NE(actual, nullptr);
    EXPECT_EQ(expected, *actual);
}
