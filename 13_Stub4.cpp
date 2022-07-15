// 13_Stub4.cpp
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

        if (current == "10:00") {
            return 100;
        }

        return 0;
    }
};

//-------
#include <gtest/gtest.h>

// 아래의 테스트가 성공하기 위한 테스트 대역을 직접 만들어보세요.
// => 5분 드리겠습니다.
// => Google Mock을 이용해서 만들어야 합니다.
class StubTime : public Time {
    std::string result;

public:
    StubTime(const std::string& result)
        : result(result)
    {
    }

    std::string GetCurrentTime() override
    {
        // return "00:00";
        return result;
    }
};

// 00:00 분에 42의 값을 반환하는지 검증하고 싶다.
TEST(UserTest, Alarm)
{
    // Clock time;
    StubTime time("00:00");
    User user(&time);

    EXPECT_EQ(42, user.Alarm());
}

TEST(UserTest, Alarm2)
{
    // Clock time;
    StubTime time("10:00");
    User user(&time);

    EXPECT_EQ(100, user.Alarm());
}