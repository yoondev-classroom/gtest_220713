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
#include <gmock/gmock.h>

class StubTime : public Time {
public:
    MOCK_METHOD(std::string, GetCurrentTime, (), (override));
}

using testing::Return;
using testing::NiceMock;

// 00:00 분에 42의 값을 반환하는지 검증하고 싶다.
TEST(UserTest, Alarm)
{
    NiceMock<StubTime> time;
    ON_CALL(time, GetCurrentTime).WillByDefault(Return("00:00"));
    User user(&time);

    EXPECT_EQ(42, user.Alarm());
}

TEST(UserTest, Alarm2)
{
    NiceMock<StubTime> time;
    ON_CALL(time, GetCurrentTime).WillByDefault([] {
        return "10:00";
    }));
    User user(&time);

    EXPECT_EQ(100, user.Alarm());
}