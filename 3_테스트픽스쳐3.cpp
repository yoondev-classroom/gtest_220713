// 3_테스트픽스쳐3.cpp

class Calc
{
public:
  double Display() { return 0; }

  void Enter(double n) {}
  void PressPlus() {}

  void PressEquals() {}

  // Calc(int n) {} // 요구사항의 변경!
};

#include <gtest/gtest.h>

// 2. Test Fixture를 설치하는 방법 3가지
//  3) 암묵적 설치(Implicit Setup)
//  => xUnit Test Framework이 제공하는 기능입니다.
//  => 여러 테스트케이스에서 같은 테스트 픽스쳐의 설치의 코드를 암묵적으로 호출되는
//     함수를 통해서 처리합니다.
//   : 명시적인 테스트 스위트 클래스 => TEST_F

class CalcTest : public testing::Test
{
protected:
  void SetUp() override 
  {
    printf("SetUp()\n"); 
  }
};

#define SPEC printf
TEST_F(CalcTest, PressPlus_TwoPlusTwoEquals_DisplaysFour)
{
  SPEC("계산기에 대해서 2 더하기 2를 하였을 때, 디스플레이가 4를 보여주는지 "
       "검증.\n");

  // Arrange
  Calc *calc = new Calc;

  // Act
  calc->Enter(2);
  calc->PressPlus();
  calc->Enter(2);
  calc->PressEquals();

  // Assert
  ASSERT_EQ(calc->Display(), 4) << "2 + 2 하였을 때";
}

TEST_F(CalcTest, PressPlus)
{
  // Arrange
  Calc *calc = new Calc;

  // Act
  calc->Enter(2);
  calc->PressPlus();
  calc->Enter(2);
  calc->PressEquals();

  // Assert
  if (calc->Display() != 4)
  {
    FAIL() << "2 + 2 하였을 때";
  }
}

TEST_F(CalcTest, foo) {}
TEST_F(CalcTest, goo) {}