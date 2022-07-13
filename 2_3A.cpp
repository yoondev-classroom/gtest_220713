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
//  1) Arrange/Given: 테스트 대상 코드(SUT)를 초기화하고, 필요한 경우 설정하고
//  준비합니다.
//  2)     Act/When: 테스트 대상 코드에 작용을 가합니다.
//  3)  Assert/Then: 기대하는 바를 단언한다.

// 3. 테스트 코드의 품질을 판단하는 방법
//  1) 가독성
//   - 테스트케이스의 시나리오가 제대로 드러나는가?
//   - 테스트케이스가 실패하였을 때 실패의 원인이 오류 메세지를 통해 제대로
//   드러나는가?
//
//  2) 유지보수성
//   - 테스트케이스에서 오류가 발생하는 형태의 코드를 지양해야 합니다.
//   - 제어 구문(조건문, 반복문, 예외 처리 등)의 발생을 최소화해야 한다.
//    : 제어 구문을 캡슐화해서 별도의 테스트 유틸리티로 뽑아내고, 테스트
//    케이스안에서는 사용하지 않는 것이 좋다.
//
//  3) 신뢰성
//   - 테스트의 결과를 신뢰할 수 있는가?
//    : 테스트의 결과가 간헐적으로 변경되거나, 테스트가 환경에 따라서 결과가
//    변한다.

// 4. 단언 매크로(함수)
//   ASSERT_XX
//    EQ(==), NE(!=), LT(<), GT(>), LE(<=), GE(>=)
//    TRUE, FALSE ...

// 5. BDD(Behavior Driven Development, 행위 주도 개발) 진영
//   1) 용어: 좀더 사람이 익숙한 용어를 사용해라
//   2) 상태 검증 -> 행위 검증

#define SPEC printf
TEST(CalcTest, PressPlus_TwoPlusTwoEquals_DisplaysFour) {
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
  // => 단언 매크로를 사용해야 합니다.
  ASSERT_EQ(calc->Display(), 4) << "2 + 2 하였을 때";

  /*
  if (calc->Display() != 4) {
    FAIL() << "2 + 2 하였을 때";
  }
  */
}

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
