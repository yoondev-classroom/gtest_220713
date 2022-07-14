// 10_파라미터화테스트2.cpp

bool IsPrime(int value)
{
    for (int i = 2; i < value; ++i) {
        if (value % 2 == 0)
            return false;
    }

    return false;
}

#include <gtest/gtest.h>

// 파라미터화 테스트 패턴(Parameterized Test Pattern)
// : xUnit Test Framework가 제공하는 기능입니다.

// 의도: 입력 데이터를 바꿔가며, 반복 검사하는 데이터 중심의 테스트에서
//      코드 중복을 제거할 수 있습니다.

// 1. 명시적인 Test Suite 클래스
//   부모: testing::Test -> testing::TestWithParam<InputDataType>

//   testing::Test          -> TEST_F
//   testing::TestWithParam -> TEST_P

class PrimeTest : public testing::TestWithParam<int> {
};

// 2. 데이터 셋 정의
// > 2, 3, 5, 7, 11, 13, 17, 23, 29, 37
// INSTANTIATE_TEST_SUITE_P(데이터셋이름, TestSuite클래스, 데이터)

INSTANTIATE_TEST_SUITE_P(PrimeValues, PrimeTest,
    testing::Values(2, 3, 5, 7, 11, 13, 17, 23, 29, 37));

// 3. 데이터 셋을 활용하는 테스트 케이스를 만들면 됩니다.
TEST_P(PrimeTest, IsPrime)
{
    // GetParam(): 값을 하나씩 얻어올 수 있습니다.
    EXPECT_TRUE(IsPrime(GetParam()));
}