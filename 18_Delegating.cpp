// 18_Delegating.cpp
#include <iostream>

class Calc {
public:
    virtual ~Calc() { }

    virtual int Add(int a, int b) 
    { 
        std::cout << "Calc::Add" << std::endl;
        return a + b; 
    }
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

// Mocking된 메소드는 호출여부 판단을 위해서 사용되지, 실제 동작을 수행하지 않습니다.
//  => 동작이 필요하면 위임을 해주어야 합니다.

class MockCalc : public Calc {
public:
    MOCK_METHOD(int, Add, (int a, int b), (override));
    MOCK_METHOD(int, Sub, (int a, int b), (override));

    int AddImpl(int a, int b) {
        return Calc::Add(a, b);
    }

};

// MOCK_METHOD
//  => ON_CALL 
//    : 함수가 호출되었을 때, 결과를 제어할 수 있습니다.

using testing::Return;

// 함수
int Add(int a, int b) { return a + b; }
// 함수 객체
struct Functor {
    int operator()(int a, int b) const { return a + b; }
};

TEST(CalcTest, Process)
{
    MockCalc mock;
    // ON_CALL(mock, Add(10, 20)).WillByDefault(Return(30));
    // ON_CALL(mock, Add(10, 20)).WillByDefault(&Add);
    // ON_CALL(mock, Add(10, 20)).WillByDefault(Functor());
    ON_CALL(mock, Add(10, 20)).WillByDefault([&mock](int a, int b) {
        // return a + b;
        return mock.AddImpl(a, b);
    });

    ON_CALL(mock, Sub(100, 50)).WillByDefault(Return(50));

    EXPECT_CALL(mock, Add(10, 20));
    EXPECT_CALL(mock, Sub(100, 50));

    Process(&mock);
    // std::cout << mock.Add(10, 20) << std::endl;
    // std::cout << mock.Sub(100, 50) << std::endl;
}