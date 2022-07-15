// 17_Mocking2.cpp
#include <gmock/gmock.h>

struct Element { };

class Calc {
public:
    virtual ~Calc() { }

    virtual int Add(Element x) { }
    virtual int Add(int times, Element x) { }
};

class MockCalc : public Calc {
public:
    // 행위 기반 검증을 수행하고자 하는 함수에 대해서만 MOCK_METHOD 하면 됩니다.
    MOCK_METHOD(int, Add, (int times, Element x), (override));
    // => 동일한 이름을 가지는 오버로딩된 함수를 가립니다.

    // 명시적으로 동일한 이름을 가지는 함수를 선언해야 합니다.
    using Calc::Add;
};

TEST(CalcTest, Add)
{
    MockCalc mock;

    Element x;

    // mock.Add(10, x);
    mock.Add(x);
}