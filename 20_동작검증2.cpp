
// 20_동작검증2.cpp
// > 호출 순서

class Dog {
public:
    virtual ~Dog() { }

    virtual void First() = 0;
    virtual void Second() = 0;
    virtual void Third() = 0;
    virtual void Fourth() = 0;
};

#include <gmock/gmock.h>

class MockDog : public Dog {
public:
    MOCK_METHOD(void, First, (), (override));
    MOCK_METHOD(void, Second, (), (override));
    MOCK_METHOD(void, Third, (), (override));
    MOCK_METHOD(void, Fourth, (), (override));
};

void Process(Dog* p)
{
  p->Second();
  p->Third();
  p->Fourth();
  p->First();
}

// First -> Second -> Third -> Fourth
// - 호출 순서 검증
//   testing::InSequence

using testing::InSequence;

TEST(DogTest, Process1)
{
  InSequence seq; // !!!!
  MockDog mock;

  EXPECT_CALL(mock, First);
  EXPECT_CALL(mock, Second);
  EXPECT_CALL(mock, Third);
  EXPECT_CALL(mock, Fourth);

  Process(&mock);
}