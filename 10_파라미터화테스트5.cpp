// 10_파라미터화테스트5.cpp
#include <gtest/gtest.h>


// testing::Combine
// => 두 개 이상의 데이터 셋을 조합해서 검증에 사용할 수 있습니다.

enum Color {
    RED = 100,
    WHITE,
    BLACK,
};

std::vector<std::string> cars = {
    "Sonata",
    "Avante",
    "Genesis",
};

int third[] = { 10, 20, 30 };

// std::tuple<std::string, Color>
class CarTest : public testing::TestWithParam<std::tuple<std::string, Color, int>> {
};

INSTANTIATE_TEST_SUITE_P(CarValues, CarTest,
    testing::Combine(
        testing::ValuesIn(cars),
        testing::Values(RED, WHITE, BLACK),
        testing::ValuesIn(third)
        ));

TEST_P(CarTest, Sample)
{
    const std::tuple<std::string, Color, int>& data = GetParam();
    std::cout << std::get<0>(data) << " - " 
    << std::get<2>(data) << ": "
    << std::get<1>(data) << std::endl;
}