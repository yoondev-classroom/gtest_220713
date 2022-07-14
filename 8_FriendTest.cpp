// 8_FriendTest.cpp
#include <iostream>
using namespace std;

// User.h
#if 0
class User {
private:
    int age = 0;

    int GetAge() const { return age; }

public:
    void NextYear() { age += 1; }
};
#endif

// 절대 사용하면 안되는 방법입니다.
// #define private public
// #define class struct
#include "User.h"
// #undef private
// #undef class

#include <gtest/gtest.h>

// 1. 제품 코드는 테스트 하기 쉬워야 한다.
// > 단위 테스트를 만드는 비용을 최소화해야 한다.

// 2. 테스트 되지 않은 private 메소드가,
//    테스트 된 public 메소드보다 위험하다.

// 3. public 메소드를 검증할 때, private 메소드도
//    자연스럽게 검증되어야 한다.
//   > private 메소드는 public 메소드의 가독성을 높이기
//     위해 사용해야 한다.

TEST(UserTest, NextYear)
{
    // NextYear의 동작으로 age의 값이 제대로
    // 변경되는지 여부를 검증하고 싶다.

    User user;

    user.NextYear();

    EXPECT_EQ(user.GetAge(), 1);
}