// 20_Matcher.cpp
// : 인자 검증할 때 사용하는 개념입니다.
//  Hamcrest Matcher
//  => JUnit/TestNG 안에서 단언문을 작성할 때, 가독성이 좋은 단언문을 작성할 수 있도록 하는
//     "비교 표현의 확장 라이브러리" 입니다.

//  => Google Mock은 단언문에서 Matcher를 사용하는 기능을 제공합니다.
#include <gmock/gmock.h>

int GetAge() { return 42; }
const char* GetMessage() { return "Hello, Google"; }

using testing::Eq;
using testing::MatchesRegex;
using testing::StartsWith;

TEST(HamcrestTest, Sample1)
{
    EXPECT_EQ(GetAge(), 42);

    EXPECT_THAT(GetAge(), Eq(42));
    EXPECT_THAT(GetMessage(), StartsWith("Hello"));
    EXPECT_THAT(GetMessage(), MatchesRegex(".*"));
}

class User {
    // Field
    std::string name;
    int age;

public:
    User(const std::string& name, int age)
        : name(name)
        , age(age)
    {
    }

    // Property
    std::string GetName() const { return name; }
    int GetAge() const { return age; }

    FRIEND_TEST(UserTest, Sample1);
};

using testing::Field;
using testing::Gt;
using testing::Property;

TEST(UserTest, Sample1)
{
    User user("Tom", 42);

    EXPECT_EQ(user.GetName(), "Tom");
    EXPECT_EQ(user.GetAge(), 42);

    EXPECT_THAT(user, Property(&User::GetName, Eq("Tom")));
    EXPECT_THAT(user, Field(&User::age, Gt(10)));
}