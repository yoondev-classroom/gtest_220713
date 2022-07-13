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

TEST(SampleTest, FirstTest) {}