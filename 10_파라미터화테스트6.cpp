
// 10_파라미터화테스트6.cpp
#include <gtest/gtest.h>

class SampleTest : public testing::TestWithParam<int> {
};

INSTANTIATE_TEST_SUITE_P(SampleValues, SampleTest,
    // testing::Range(0, 100) // [0, 100)
    testing::Range(0, 100, 5) // [0, 100)
);

TEST_P(SampleTest, foo)
{
    std::cout << GetParam() << std::endl;
}