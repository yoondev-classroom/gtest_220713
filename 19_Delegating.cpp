// 20_Delegating.cpp

#include <iostream>

class Calc {
public:
    virtual ~Calc() { }

    virtual int Add(int a, int b) { return a + b; }
    virtual int Sub(int a, int b) { return a - b; }
};

void Process(Calc* calc)
{
    if (calc->Add(10, 20) == 30) {
        int result = calc->Sub(100, 50);
        std::cout << "result: " << result << std::endl;
    } else {
        std::cout << "failed" << std::endl;
    }
}

#include <gmock/gmock.h>

class MockCalc : public Calc {
public:
    MOCK_METHOD(int, Add, (int a, int b), (override));
    MOCK_METHOD(int, Sub, (int a, int b), (override));
};

TEST(CalcTest, Process)
{
    MockCalc mock;

    EXPECT_CALL(mock, Add(10, 20));
    EXPECT_CALL(mock, Sub(100, 50));

    Process(&mock);
}