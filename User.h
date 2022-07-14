
#ifndef USER_H
#define USER_H

// gtest 의존성이 발생합니다.
//  > 조건부 컴파일을 통해 제어가능합니다.
#include <gtest/gtest.h>

class User {
    int age = 10;

    int GetAge() const { return age; }

public:
    void NextYear() { age += 1; }

    FRIEND_TEST(UserTest, NextYear);
};

#endif