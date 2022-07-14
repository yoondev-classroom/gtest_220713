// 10_파라미터화테스트4.cpp

#include <gtest/gtest.h>

class StringTest : public testing::TestWithParam<std::string> {
};

// 1. testing::Values
#if 0
INSTANTIATE_TEST_SUITE_P(StringValues, StringTest,
    testing::Values("Alice", "Tom", "Bob"));
#endif

// 2. testing::ValuesIn
std::string data[] = {
    "Alice", "Tom", "Bob"
};
INSTANTIATE_TEST_SUITE_P(StringValues, StringTest,
    testing::ValuesIn(data));

TEST_P(StringTest, Sample)
{
    std::cout << GetParam() << std::endl;
}
