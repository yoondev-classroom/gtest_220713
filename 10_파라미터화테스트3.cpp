// 10_파라미터화테스트3.cpp
#include <string>

bool Process(int arg1, const std::string& name)
{
    return arg1 > name.size();
}

struct InputData {
    int arg1;
    std::string name;

    bool expected;
};

#include <gtest/gtest.h>

class ProcessTest : public testing::TestWithParam<InputData> {
};

INSTANTIATE_TEST_SUITE_P(ProcessValues, ProcessTest,
    testing::Values(
        InputData { 10, "Tom", true },
        InputData { 5, "Bob", true },
        InputData { 3, "Alice", false },
        InputData { 4, "Bobby", false },
        InputData { 10, "David", true }));

TEST_P(ProcessTest, Sample1)
{
    const InputData& data = GetParam();

    EXPECT_EQ(data.expected, Process(data.arg1, data.name));
}