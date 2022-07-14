// 9_테스트전용하위클래스.cpp
class User {
    int age = 10;

protected:
    int GetAge() const { return age; }

public:
    void NextYear() { age += 1; }
};

#include <gtest/gtest.h>

// SUT가 제공하는 확인해야 하는 상태가 protected 이면
// => 테스트 전용 하위 클래스(Test Specific Subclass Pattern)
//   의도: SUT가 클래스에 테스트를 위한 기능을 제공하지 않을 때,
//        SUT의 하위 클래스를 만들어서 테스트되지 않은 요구사항을 검증할 수 있습니다.
//   장점: 제품코드를 변경하지 않고, 테스트할 수 있습니다.

class TestUser : public User {
public:
    using User::GetAge; // protected -> public
};

TEST(UserTest, NextYear)
{
    // NextYear의 동작으로 age의 값이 제대로
    // 변경되는지 여부를 검증하고 싶다.

    // User user;
    TestUser user;

    user.NextYear();

    EXPECT_EQ(user.GetAge(), 1);
}