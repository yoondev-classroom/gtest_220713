// 3_테스트픽스쳐2.cpp

class Calc
{
public:
  double Display() { return 0; }

  void Enter(double n) {}
  void PressPlus() {}

  void PressEquals() {}

  Calc(int n) {} // 요구사항의 변경!
};

#include <gtest/gtest.h>

// 2. Test Fixture를 설치하는 방법 3가지
//  2) Delegte Setup(위임 설치)
//    : 픽스쳐 설치에 관한 코드를 별도의 "테스트 유틸리티 함수"를 통해
//    캡슐화합니다.
//    > 명시적인 테스트 스위트 클래스가 필요합니다.

//       testing::Test
//             |
//         CalcTest
//             |
//     ------------------
//     |                 |
//  PressPlus      PressPlus_TwoPlusTwoEquals_DisplaysFour

class CalcTest : public testing::Test
{
protected:
  Calc *CreateCalc() { return new Calc(0); }
};

#define SPEC printf
TEST_F(CalcTest, PressPlus_TwoPlusTwoEquals_DisplaysFour)
{
  SPEC("계산기에 대해서 2 더하기 2를 하였을 때, 디스플레이가 4를 보여주는지 "
       "검증.\n");

  // Arrange
  Calc *calc = CreateCalc();

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
  Calc *calc = CreateCalc();

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

//---------------------
// TEST 원리 / 구조
// g++ 3_테스트픽스쳐2.cpp -E -I ./googletest/googletest/include/
// TEST(SampleTest, foo) {}
/*
class SampleTest_foo_Test : public ::testing::Test {
  // ...
};
*/

// TEST(SampleTest, goo) {}
/*
class SampleTest_goo_Test : public ::testing::Test {
  // ...
};
*/

//             testing::Test
//                    |
//       --------------------------
//       |                        |
// SampleTest_foo_Test       SampleTest_goo_Test

// 테스트 유틸리티 함수를 제공하기 위한 클래스
class SampleTest : public testing::Test
{
};

TEST_F(SampleTest, foo) {}

/*
class SampleTest_foo_Test : public SampleTest {
};
*/

TEST_F(SampleTest, goo) {}

/*
class SampleTest_goo_Test : public SampleTest {
};
*/

//             testing::Test
//                    |
//                SampleTest
//                    |
//       --------------------------
//       |                        |
// SampleTest_foo_Test       SampleTest_goo_Test