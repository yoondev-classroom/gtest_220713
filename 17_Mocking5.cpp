// 17_Mocking5.cpp

enum Level {
    INFO
};

class Logger {
public:
    virtual ~Logger() { }

    virtual void Send(
        Level level,
        const char* dir,
        const char* filename,
        int line,
        const char* message)
        = 0;
};

class User {
public:
    void Process(Logger* logger)
    {
        logger->Send(INFO, "/tmp", "process.log", 10, "user process start");
    }
};

#include <gmock/gmock.h>

class MockLogger : public Logger {
public:
    // void Send(Level level, const char* message)
    // : 사용자는 위의 인자에 대한 검증만 필요합니다.
    MOCK_METHOD(void, Send, (Level level, const char* message));

    void Send(Level level, const char* dir, const char* filename,
        int line, const char* message) override
    {
        Send(level, message); // Mocking한 함수를 호출합니다.
    }

    // MOCK_METHOD(void, Send,
    //     (Level level, const char* dir, const char* filename, int line, const char* message), (override));
};

TEST(UserTest, Process)
{
    MockLogger mock;
    User user;

    // Mocking 간략화하기.
    EXPECT_CALL(mock, Send(INFO, "user process start"));

    user.Process(&mock);
}

#if 0
class MockLogger : public Logger {
public:
    MOCK_METHOD(void, Send,
        (Level level, const char* dir, const char* filename, int line, const char* message), (override));
};

TEST(UserTest, Process)
{
    MockLogger mock;
    User user;

    EXPECT_CALL(mock, Send(INFO, "/tmp", "process.log", 10, "user process start"));

    user.Process(&mock);
}
#endif