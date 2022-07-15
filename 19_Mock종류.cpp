// 19_Mock종류.cpp

class User {
public:
    virtual ~User() { }

    virtual void Go() { }
    virtual void Say() { }
};

void Process(User* p)
{
    p->Go();
    p->Say();
}

#include <gmock/gmock.h>

/*
GMOCK WARNING:
Uninteresting mock function call - returning directly.
    Function call: Say()
NOTE: You can safely ignore the above warning unless this call should not happen.  Do not suppress it by blindly adding an EXPECT_CALL() if you don't mean to enforce the call.  See https://github.com/google/googletest/blob/master/docs/gmock_cook_book.md#knowing-when-to-expect for details.
*/

// MOCK_METHOD한 메소드가 EXPECT_CALL하지 않았을 때,
// 호출이 된다면?
// 1. Default - Naggy Mock
// : 테스트의 결과는 성공입니다.
//   관심없는 호출에 대한 경고가 발생합니다.

// 2. Nice Mock
// : 테스트의 결과도 성공이고, 경고도 발생하지 않습니다.

// 3. Strict Mock
// : 테스트의 결과는 실패합니다.
//  => 테스트의 통과 기준이 높아집니다.
//     테스트를 작성하는 비용이 증가할 수 있습니다.

class MockUser : public User {
public:
    MOCK_METHOD(void, Go, (), (override));
    MOCK_METHOD(void, Say, (), (override));
};

using testing::NiceMock;
using testing::StrictMock;

TEST(UserTest, Process)
{
    // MockUser mock;
    // NiceMock<MockUser> mock;
    StrictMock<MockUser> mock;

    EXPECT_CALL(mock, Go);

    Process(&mock);
}