// 2_3A.cpp

// SUT: System Under Test(테스트 대상 시스템, 코드, 클래스)
class Calc {
public:
  double Display() { return 0; }

  void Enter(double n) {}
  void PressPlus() {}

  void PressEquals() {}
};

// #include "Calc.h"
//--------------------------------

#include <gtest/gtest.h>

// TEST(TestSuiteName, TestCaseName)
// 1. TestSuite Name
//  > 테스트 스위트의 이름은 테스트 대상 클래스(모듈)의 이름의 마지막에
//    Test 또는 Spec을 많이 사용합니다.
//  > CalcTest or CalcSpec

// 2. 테스트케이스를 구성하는 방법: 3A
//  1) Arrange: 테스트 대상 코드(SUT)를 초기화하고, 필요한 경우 설정하고
//  준비합니다.
//  2)     Act: 테스트 대상 코드에 작용을 가합니다.
//  3)  Assert: 기대하는 바를 단언한다.

TEST(CalcTest, PressPlus) {
  // Arrange
  Calc *calc = new Calc;

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
