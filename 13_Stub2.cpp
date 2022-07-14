// 13_Stub2.cpp
#include <string>

struct Time {
    virtual ~Time() { }

    virtual std::string GetCurrentTime() = 0;
};

class Clock : public Time {
public:
    std::string GetCurrentTime() override
    {
        // 현재 시간을 문자열로 변환해서 전달합니다.
        return "16:09";
    }
};

class User {
    Time* time;

public:
    User(Time* time)
        : time(time)
    {
    }

    int Alarm()
    {
        std::string current = time->GetCurrentTime();
        if (current == "00:00") {
            return 42;
        }

        return 0;
    }
};

//-------
#include <gtest/gtest.h>

// 아래의 테스트가 성공하기 위한 테스트 대역을 직접 만들어보세요.
// => 5분 드리겠습니다.

// 00:00 분에 42의 값을 반환하는지 검증하고 싶다.
TEST(UserTest, Alarm)
{
    Clock time;
    User user(&time);

    EXPECT_EQ(42, user.Alarm());
}