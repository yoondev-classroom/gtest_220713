// 3_테스트픽스쳐.cpp

class Calc {
public:
  double Display() { return 0; }

  void Enter(double n) {}
  void PressPlus() {}

  void PressEquals() {}
};

#include <gtest/gtest.h>

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
