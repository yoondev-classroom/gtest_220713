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

TEST(SampleTest, DISABLED_Sample3)
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
    double b = 0.1 * 7;

    // EXPECT_EQ(a, b);
    // EXPECT_DOUBLE_EQ(a, b); // 4ULP - https://en.wikipedia.org/wiki/Unit_in_the_last_place

    EXPECT_NEAR(a, b, 0.0000000001);
}

// 4. 예외 검증을 위한 단언문을 제공합니다.
//   => EXPECT_THROW
//      EXPECT_ANY_THROW: 예외 종류에 상관없습니다.

void OpenFile(const std::string& filename)
{
    if (filename.empty()) {
        // throw std::invalid_argument("filename is empty!");
        throw 1;
    }

    // ...
}

TEST(SampleTest4, DISABLED_OpenFile2)
{
    // OpenFile에 빈 이름을 전달하였을 때, 예외가 제대로 발생하는지 검증하고 싶다.
    std::string emptyFilename = "";

    EXPECT_THROW(OpenFile(emptyFilename), std::invalid_argument);
    EXPECT_ANY_THROW(OpenFile(emptyFilename));
}

TEST(SampleTest4, OpenFile)
{
    // OpenFile에 빈 이름을 전달하였을 때, 예외가 제대로 발생하는지 검증하고 싶다.
    try {
        OpenFile("");
        FAIL() << "기대한 예외가 발생하지 않음.";
    } catch (std::invalid_argument& e) {
        SUCCEED();
    } catch (...) {
        FAIL() << "다른 종류의 예외가 발생함.";
    }
}

// 5. 테스트 코드가 유지보수 중일 때, 실패시켜야 합니다.
//  => 성공시키면, "잊혀진 테스트"가 됩니다.
//  => 테스트를 비활성화하는 방법이 필요합니다.
//   : GoogleTest에서는 테스트 비활성화는 TestSuite 이름
//     또는 TestCase 이름이 DISABLED_ 로 시작하면 됩니다.
//  > 테스트의 결과에 포함되지 않고, 비활성화된 테스트가 존재한다는 사실을 알립니다.

//  비활성화된 테스트도 구동하는 명령이 있습니다.
//  $ ./a.out --gtest_also_run_disabled_tests

class DISABLED_SampleTest5 : public testing::Test {
};

// 작성중입니다.
TEST_F(DISABLED_SampleTest5, DISABLED_Sample1)
{
    FAIL() << "작성 중입니다.";
}

TEST_F(DISABLED_SampleTest5, Sample2)
{
}