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
}

// 2. 함수 호출 횟수 - Cardinality
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

// 3. 함수 호출 인자 매칭
// : 인자 매칭에 따라서 함수 호출 횟수 판단이 달라질 수 있습니다.
//  => Matcher
using testing::_;  // *
using testing::Lt; // <
using testing::Le; // <=
using testing::Gt; // >
using testing::Ge; // >=
using testing::Eq; // ==
using testing::Ne; // !=
using testing::Matcher;

using testing::AllOf;  // &&
using testing::AnyOf;  // ||

void UsePerson3(Person* p)
{
    p->Go(10, 1);
    p->Go(0, 3); // !!
    p->Go(-20, 5);
    p->Go(11, 4);
    p->Go(10, 5);
}

TEST(PersonTest, DISABLED_Sample3)
{
    MockPerson mock;

    // EXPECT_CALL(mock, Go(100, 200)).Times(2);
    // EXPECT_CALL(mock, Go(10, 20)).Times(3);

    // 1) 첫번째 인자가 10이고, 뒤의 인자는 상관없이 5번 호출됩니다.
    // EXPECT_CALL(mock, Go(10, _)).Times(5);

    // 2) 첫번째 인자가 10이상이고, 뒤의 인자는 5미만입니다.
    // Matcher<int> arg1 = Ge(10); // arg1 >= 10
    // auto arg2 = Lt(6);          // arg2 < 6
    // EXPECT_CALL(mock, Go(arg1, arg2)).Times(5);    

    // 3) 첫번째 인자 10보다 크거나 같거나 0보다 작아야 합니다: arg1 >= 10 || arg1 < 0
    //    두번째 인자는 0보다 크고 10보다 작아야 합니다:      arg2 > 0 && arg2 < 10
    auto arg1 = AnyOf(Ge(10), Lt(0));
    auto arg2 = AllOf(Gt(0), Lt(10));
    EXPECT_CALL(mock, Go(arg1, arg2)).Times(5);

    UsePerson3(&mock);
}

void Sample4(Person* p)
{
    std::vector<int> data = {30, 10, 20}; // { 10, 20, 30 };
    p->Print(data);
}

using testing::ElementsAre;
using testing::ElementsAreArray;
using testing::UnorderedElementsAre;
using testing::UnorderedElementsAreArray;

TEST(PersonTest, Sample4)
{
    MockPerson mock;

    // std::vector<int> expected = { 10, 20, 30 };
    // EXPECT_CALL(mock, Print(expected));

    // Matcher의 조합을 통해, 컨테이너 요소 인자에 대한 검증도 가능합니다.
    // Matcher<int> expected[] = { Lt(30), Gt(3), Le(40) };
    // EXPECT_CALL(mock, Print(ElementsAreArray(expected)));

    // EXPECT_CALL(mock, Print(ElementsAre(Lt(30), Gt(3), Le(40))));


    EXPECT_CALL(mock, Print(UnorderedElementsAre(Lt(30), Gt(3), Le(40))));


    Sample4(&mock);
}