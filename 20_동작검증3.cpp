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

class MockCalc : public Calc {
public:
    MOCK_METHOD(int, Add, (int a, int b), (override));
    MOCK_METHOD(int, Sub, (int a, int b), (override));

    int AddImpl(int a, int b)
    {
        return Calc::Add(a, b);
    }
};

using testing::Return;

int Add(int a, int b) { return a + b; }
struct Functor {
    int operator()(int a, int b) const { return a + b; }
};

TEST(CalcTest, Process)
{
    MockCalc mock;
    ON_CALL(mock, Add(10, 20)).WillByDefault(Return(30));
    ON_CALL(mock, Sub(100, 50)).WillByDefault(Return(50));

    EXPECT_CALL(mock, Add(10, 20));
    EXPECT_CALL(mock, Sub(100, 50));

    Process(&mock);
    // std::cout << mock.Add(10, 20) << std::endl;
    // std::cout << mock.Sub(100, 50) << std::endl;
}

TEST(CalcTest, Process3)
{
    MockCalc mock;
    
    EXPECT_CALL(mock, Add(10, 20)).WillOnce(Return(30));
    EXPECT_CALL(mock, Sub(100, 50)).WillOnce(Return(50));

    Process(&mock);
}



// ON_CALL + EXPECT_CALL
//  => EXPECT_CALL 만으로 '위임의 기능'도 구현할 수 있습니다.
#if 0
    EXPECT_CALL(mock, Add(10, 20)) 
      .WillOnce(Return(10))
      .WillOnce(Return(20))
      .WillOnce(Return(30));           
    // Times(3)

    EXPECT_CALL(mock, Add(10, 20)) 
      .WillOnce(Return(10))
      .WillRepeatedly(Return(20));

      // N: WillOnce 개수
      // Times(AtLeast(N))

   // 주의사항: WillRepeatedly는 마지막에 1번만 사용 가능하고,
   //         WillRepeatedly를 단독으로 사용하는 것은 좋지 않습니다. - AtLeast(0)

#endif


TEST(CalcTest, Process2)
{
    MockCalc mock;

    EXPECT_CALL(mock, Add(10, 20)) 
      .WillOnce(Return(10))
      .WillRepeatedly(Return(20)); 
      
    std::cout << mock.Add(10, 20) << std::endl; // 10
    std::cout << mock.Add(10, 20) << std::endl; 
    std::cout << mock.Add(10, 20) << std::endl; 
}