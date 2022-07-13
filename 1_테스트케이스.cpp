// 1_테스트케이스.cpp

// 1) Google Test 사용하는 방법
#include <gtest/gtest.h>

// 2) Google Test Framework
//  1.10 이전: xUnit Test Framework 용어와 차이가 있습니다.
// > TestCase
//   - Test1
//   - Test2
//   - Test3

//  1.10 이후: xUnit Test Framework 용어가 통일되었습니다.
// > TestSuite
//  - TestCase1
//  - TestCase2
//  - TestCase3

// 3) TestCase를 만드는 방법
//   - TEST(TestSuiteName, TestCaseName)

// 4) 테스트는 실패하지 않으면, 무조건 성공합니다.
//   - FAIL(): 테스트를 실패시킬 수 있습니다.
// 5) 테스트가 실패할 경우, 코드를 보지 않아도 실패의 원인을 알 수 있어야
// 합니다.
// 6) 테스트의 이름이 테스트가 어떤 동작을 검증하는지 드러내야 합니다.
//   - 테스트대상메소드_시나리오_결과값

#define SPEC printf

TEST(SampleTest, FirstTest) {
  SPEC("이미지를 리사이즈 하였을 때, 이미지의 길이나 높이가 제대로 "
       "변경되었는지 여부를 검증\n");
  FAIL() << "작성 중입니다.";
}