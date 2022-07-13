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

int foo() { return -1; }
int goo() { return -1; }

// - ASSERT_XXX
//  1. 단언문이 실패할 경우, 이후의 코드를 수행하지 않습니다.
//  2. 하나의 테스트케이스 안에 여러개의 단언문이 존재하면,
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
