
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

//-----
// Fake Object Pattern
// 의도: 아직 준비되지 않은 협력 객체로 인해서, 테스트 되지 않은 요구사항이 존재합니다.
// 방법: 동일한 기능을 제공하는 가벼운 테스트 대역을 만들어서, 테스트 되지 않은 요구사항을
//      검증합니다.
//    1) 협력 객체가 아직 준비되지 않았을 때
//    2) 협력 객체를 사용하기 어려울 때
//    3) 협력 객체로 인해서 느린 테스트의 문제가 발생했을 때

#include <gtest/gtest.h>
#include <map>

class FakeDatabase : public IDatabase {
    std::map<std::string, User*> data;

public:
    void SaveUser(const std::string& name, User* user) override
    {
        data[name] = user;
    }

    User* LoadUser(const std::string& name)
    {
        return data[name];
    }
};

// 사용자 정의 객체에 대해서 단언문을 사용하기 위해서는
// "연산자 재정의"가 필요합니다.

// 같은 파일에서만 접근이 가능합니다.
static bool operator==(const User& lhs, const User& rhs)
{
    return false;
    // return lhs.GetName() == rhs.GetName() && lhs.GetAge() == rhs.GetAge();
}

// Google Test 에서 사용자 정의 객체가 제대로 출력되기 위해서는
// 연산자 오버로딩 함수가 필요합니다.
static std::ostream& operator<<(std::ostream& os, const User& user)
{
    return os << "name=" << user.GetName() << ", "
              << "age=" << user.GetAge();
}

TEST(UserRepositoryTest, Save)
{
    FakeDatabase database;
    UserRepository repo(&database);
    std::string testName = "test_name";
    int testAge = 42;
    User expected(testName, testAge);

    repo.Save(&expected);
    User* actual = repo.Load(testName);

    EXPECT_EQ(expected, *actual);
}
