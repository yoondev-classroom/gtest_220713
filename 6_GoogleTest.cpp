// 6_GoogleTest.cpp
#include <gtest/gtest.h>

// xUnit Test Framework
// 1. Fixture
// 2. Assertions

class User {
    std::string name = "Tom";
    int age = 42;

public:
    std::string GetName() const { return name; }
    int GetAge() const { return age; }
};

User* GetCurrentUser() { return nullptr; }

TEST(SampleTest, Sample3)
{
    User* user = GetCurrentUser();

    // 사전 조건 단언문
    ASSERT_NE(user, nullptr);
    EXPECT_EQ(user->GetName(), "Tom");
    EXPECT_EQ(user->GetAge(), 42);
}

int foo() { return 42; }
int goo() { return 100; }

// 1. ASSERT_XXX
//  1) 단언문이 실패할 경우, 이후의 코드를 수행하지 않습니다.
//  2) 하나의 테스트케이스 안에 여러개의 단언문이 존재하면,
//     이후의 단언문은 수행되지 않는 문제가 있습니다.
//      : 죽은 단언문 문제
//   <해결방법>
//   1) 하나의 테스트 케이스 안에 여러 개의 단언문을 사용하지 않는 것이 좋습니다.
//      => 중복된 테스트케이스 문제
//   2) EXPECT_XXX
//      => 하나의 단언문이 실패할 경우, 테스트의 결과는 실패하지만,
//         이후의 코드는 계속 수행됩니다.

TEST(SampleTest, Sample1)
{
    int actualFoo = foo();
    int actualGoo = goo();

    ASSERT_EQ(actualFoo, 42);
    ASSERT_EQ(actualGoo, 100);
}

TEST(SampleTest, Sample2)
{
    int actualFoo = foo();
    int actualGoo = goo();

    EXPECT_EQ(actualFoo, 42);
    EXPECT_EQ(actualGoo, 100);
}

// 2. 문자열 비교 단언문
//  > C의 문자열: char[] / const char*
//  : EXPECT_STREQ/STRNE - strcmp
//    EXPECT_STRCASEEQ/STRCASENE - strcmpi
TEST(SampleTest2, Sample1)
{
    std::string s1 = "hello";
    std::string s2 = "hello";

    // C의 문자열
    char s3[] = "hello";
    const char* s4 = "hello";

    EXPECT_EQ(s1, s2);
    // EXPECT_EQ(s3, s4);
    EXPECT_STREQ(s3, s4);

    char s5[] = "Hello";
    const char* s6 = "hello";
    EXPECT_STRCASEEQ(s5, s6);
}

// 3. 부동 소수점 단언문
//  > 오차 범위가 존재하므로, EQ 연산은 항상 실패합니다.
//    EXPECT_DOUBLE_EQ / EXPECT_FLOAT_EQ
//    EXPECT_NEAR: 오차 범위를 지정할 수 있습니다.
TEST(SampleTest3, Sample1)
{
    double a = 0.7;
    double b = 0.1 * 7.1;

    // EXPECT_EQ(a, b);
    // EXPECT_DOUBLE_EQ(a, b); // 4ULP - https://en.wikipedia.org/wiki/Unit_in_the_last_place

    EXPECT_NEAR(a, b, 0.0000000001);
}