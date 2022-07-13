// 3_테스트픽스쳐.cpp

class Calc {
public:
  double Display() { return 0; }

  void Enter(double n) {}
  void PressPlus() {}

  void PressEquals() {}

  // Calc(int n) {} // 요구사항의 변경!
};

#include <gtest/gtest.h>

// 1. Test Fixture
//  정의: xUnit Test Pattern에서는 SUT를 실행하기 위해 준비해야 하는 모든 것을
//       테스트 픽스쳐라고 합니다.
//       테스트 픽스쳐를 구성하는 모든 코드의 로직 부분을 "픽스쳐
//       설치(Setup)"라고 합니다.

// 2. Test Fixture를 설치하는 방법 3가지
//  1) Inline Fixture Setup
//  : 모든 픽스쳐 설치를 테스트케이스 안에서 수행합니다.

//  장점: 픽스쳐를 설치하는 과정을 검증의 로직이 하나의 테스트 케이스 함수
//       안에서 존재하기 때문에 인과 관계를 쉽게 분석할 수 있다.

//  단점: 모든 테스트 코드 안에서 "코드 중복"이 발생합니다.
//   "테스트 코드 중복" -> 테스트 냄새 : 유지보수성
//   테스트 냄새: 테스트 코드의 가독성을 떨어뜨리거나, 테스트 코드의 유지보수성을 떨어뜨리거나, 테스트 코드의 신뢰성을 떨어뜨릴 수 있습니다.

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
  ASSERT_EQ(calc->Display(), 4) << "2 + 2 하였을 때";
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
