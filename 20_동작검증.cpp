// 20_동작검증.cpp

// 동작 검증 / 행위 기반 검증
// 1) 함수 호출 여부
// 2) 함수 호출 횟수
// 3) 함수 호출 인자
// 4) 함수 호출 순서

#include <vector>

class Person {
public:
    virtual ~Person() { }

    virtual void Go(int x, int y) = 0;
    virtual void Print(const std::vector<int>& numbers) const = 0;
};

#include <gmock/gmock.h>

class MockPerson : public Person {
public:
    MOCK_METHOD(void, Go, (int x, int y), (override));
    MOCK_METHOD(void, Print, (const std::vector<int>& numbers), (const, override));
};

void UsePerson(Person* p)
{
    p->Go(100, 200);
    p->Go(10, 20);

    // p->Go(1, 2);
}

// 1. 함수 호출 여부
// => EXPECT_CALL
TEST(PersonTest, Sample1)
{
    MockPerson mock;

    EXPECT_CALL(mock, Go(100, 200));
    EXPECT_CALL(mock, Go(10, 20));

    UsePerson(&mock);
}

void UsePerson2(Person* p)
{
    p->Go(100, 200);
    p->Go(100, 200);
    p->Go(10, 20);
    p->Go(10, 20);
    p->Go(10, 20);
}

// 2. 함수 호출 횟수
// EXPECT_CALL(...).Times(N)
using testing::AtLeast; // N번 이상
using testing::AtMost; // N번 이하
using testing::Between; // 범위

TEST(PersonTest, Sample2)
{
    MockPerson mock;

    // 인자에 상관없이 호출 여부를 판단합니다.
    // EXPECT_CALL(mock, Go).Times(2);
    // EXPECT_CALL(mock, Go).Times(AtLeast(2));
    // EXPECT_CALL(mock, Go).Times(AtMost(2));

    EXPECT_CALL(mock, Go).Times(Between(2, 4));

    UsePerson2(&mock);
}