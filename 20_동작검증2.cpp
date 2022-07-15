
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
    p->First();
    p->Second();
    p->Third();
    p->Fourth();
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

void Process2(Dog* p)
{
    p->First();

    p->Third();

    p->Second();

    p->Fourth();
}

// First ------> Second          : 1
//       |
//       ------> Third -> Fourth : 2
using testing::Sequence;

TEST(DogTest, Process2)
{
    MockDog mock;
    Sequence seq1, seq2;

    EXPECT_CALL(mock, First).InSequence(seq1, seq2);
    EXPECT_CALL(mock, Second).InSequence(seq1);
    EXPECT_CALL(mock, Third).InSequence(seq2);
    EXPECT_CALL(mock, Fourth).InSequence(seq2);

    Process2(&mock);
}