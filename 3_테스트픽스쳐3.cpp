// 3_테스트픽스쳐3.cpp

#include <stdio.h>

class Calc {
public:
    double Display() { return 0; }

    void Enter(double n) { }
    void PressPlus() { }

    void PressEquals() { }

    Calc() { printf("Calc()\n"); }
    ~Calc() { printf("~Calc()\n"); }

    // Calc(int n) {} // 요구사항의 변경!
};

#include <gtest/gtest.h>

// 2. Test Fixture를 설치하는 방법 3가지
//  3) 암묵적 설치/해체(Implicit SetUp/TearDown) => *
//  => xUnit Test Framework이 제공하는 기능입니다.
//  => 여러 테스트케이스에서 같은 테스트 픽스쳐의 설치와 해체의 코드를 암묵적으로 호출되는
//     함수를 통해서 처리합니다.
//   : 명시적인 테스트 스위트 클래스 => TEST_F
//  장점: 테스트 코드 중복을 제거하고, 불필요한 준비 과정을 캡슐화할 수 있습니다.
//  단점: 픽스쳐 설치 코드가 테스트 케이스 외부에 존재하기 때문에
//       테스트 케이스만으로 테스트 코드를 분석하기 어렵다.

// 3. ASSERT_XXX
//  : 단언문이 실패하면, 이후의 코드를 수행하지 않습니다.

// 4. xUnit Test Pattern에서 테스트 케이스를 구성하는 방법
//   => 4단계 테스트 패턴(Four Phase Test Pattern)
//  1단계: 테스트 픽스쳐를 설치하거나, 실제 결과를 관찰하기 위해서 필요한 것을 설정하는 작업
//     => SetUp()
//  2단계: SUT와 상호작용 합니다. => TestBody()
//  3단계: 기대 결과를 확인한다.   => TestBody()
//  4단계: 테스트 픽스쳐를 해체해서, 테스트 시작 이전의 상태로 돌려놓습니다.
//     => TearDown()

class CalcTest : public testing::Test {
protected:
    Calc* calc = nullptr;

    void SetUp() override
    {
        printf("SetUp()\n");
        calc = new Calc;
    }

    // 테스트의 결과와 상관없이 무조건 수행됩니다.
    void TearDown() override
    {
        printf("TearDown()\n");
        delete calc;
    }
};

#define SPEC printf
TEST_F(CalcTest, PressPlus_TwoPlusTwoEquals_DisplaysFour)
{
    SPEC("계산기에 대해서 2 더하기 2를 하였을 때, 디스플레이가 4를 보여주는지 "
         "검증.\n");

    // Act
    calc->Enter(2);
    calc->PressPlus();
    calc->Enter(2);
    calc->PressEquals();

    // Assert
    ASSERT_EQ(calc->Display(), 4) << "2 + 2 하였을 때";

    // delete calc;
    //  : 단언문이 실패할 경우 수행되지 않습니다.
}

TEST_F(CalcTest, PressPlus)
{
    // Act
    calc->Enter(2);
    calc->PressPlus();
    calc->Enter(2);
    calc->PressEquals();

    // Assert
    if (calc->Display() != 4) {
        FAIL() << "2 + 2 하였을 때";
    }
}

TEST_F(CalcTest, foo) { }
TEST_F(CalcTest, goo) { }