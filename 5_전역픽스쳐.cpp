// 5_전역픽스쳐.cpp
//  => xUnit Test Framework의 기능이 아닙니다.
//  => Google Test 고유의 기능입니다.
//  => 프로그램의 시작/종료에서 픽스쳐를 설치하고 해체할 수 있는 기능입니다.

#include <gtest/gtest.h>

// - 테스트케이스 단위 픽스쳐 - xUnit / 신선한 픽스쳐 전략
// - 테스트스위트 단위 픽스쳐 - xUnit / 공유 픽스쳐 전략
// - 프로그램 단위 픽스쳐    - Google Test

TEST(SampleTest, First)
{
}
TEST(SampleTest, Second)
{
}

TEST(ImageTest, First)
{
}
TEST(ImageTest, Second)
{
}

// 전역 픽스쳐를 사용하는 방법
// 1. testing::Environment 를 상속받아서 SetUp()/TearDown()을
//    정의합니다.
class MyTestEnvironment : public testing::Environment {
public:
    void SetUp() override
    {
        printf("MyTestEnvironment.SetUp()\n");
    }

    void TearDown() override
    {
        printf("MyTestEnvironment.TearDown()\n");
    }
};

class MyTestEnvironment2 : public testing::Environment {
public:
    void SetUp() override
    {
        printf("MyTestEnvironment.SetUp2()\n");
    }

    void TearDown() override
    {
        printf("MyTestEnvironment.TearDown2()\n");
    }
};

// 2. TestEnvironment를 설치하는 방법
//  1) main: 사용자가 main을 직접 정의하고 있을 때 => 권장
#if 1
int main(int argc, char** argv)
{
    // 1. 구글 테스트 라이브러리 초기화
    testing::InitGoogleTest(&argc, argv);

    // 반드시 new를 통해 생성해야 합니다.
    testing::AddGlobalTestEnvironment(new MyTestEnvironment);
    testing::AddGlobalTestEnvironment(new MyTestEnvironment2);

    // 2. 모든 테스트를 실행하고, 테스트 결과를 리포트합니다.
    return RUN_ALL_TESTS();
}
#endif

//  2) 전역 변수: 사용자가 main을 정의하고 있지 않을 때
//  > 전역 변수의 초기화가 main 이전에 수행되는 특징을 이용합니다.
#if 0
testing::Environment* env1 = testing::AddGlobalTestEnvironment(new MyTestEnvironment);
#endif
