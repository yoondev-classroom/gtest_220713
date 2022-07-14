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
        InputData { 3, "Alice", true }, // !!
        InputData { 4, "Bobby", false },
        InputData { 10, "David", true }));

// 사용자 정의 타입은 구글 테스트 프레임워크에 의해서 제대로 출력되지 않습니다.
std::ostream& operator<<(std::ostream& os, const InputData& data)
{
    return os << "Input{arg1=" << data.arg1 << ", name=" << data.name << "}";
}

TEST_P(ProcessTest, Sample1)
{
    const InputData& data = GetParam();

    EXPECT_EQ(data.expected, Process(data.arg1, data.name));
}

//--------------------
// std::tuple을 이용하면 여러개의 타입을 하나의 타입으로 묶을 수 있습니다.
using InputDataType2 = std::tuple<int, std::string, bool>;

class ProcessTest2 : public testing::TestWithParam<InputDataType2> {
};

INSTANTIATE_TEST_SUITE_P(ProcessValues2, ProcessTest2,
    testing::Values(
        InputDataType2{ 10, "Tom", true },
        InputDataType2{ 5, "Bob", true },
        InputDataType2{ 3, "Alice", true }, // !!
        InputDataType2{ 4, "Bobby", false },
        InputDataType2{ 10, "David", true }));

TEST_P(ProcessTest2, Sample1)
{
    const InputDataType2& data = GetParam();
    
    int arg1 = std::get<0>(data);
    std::string name = std::get<1>(data);
    bool expected = std::get<2>(data);
      
    EXPECT_EQ(expected, Process(arg1, name));
}