// 15_Spy.cpp

#include <string>
#include <vector>

enum Level {
    INFO,
    WARN,
    ERROR
};

struct DLoggerTarget {
    virtual ~DLoggerTarget() { }

    virtual void Write(Level level, const std::string& message) = 0;
};

class FileTarget : public DLoggerTarget {
public:
    void Write(Level level, const std::string& message) override
    {
        // 파일에 기록
    }
};

class TCPTarget : public DLoggerTarget {
public:
    void Write(Level level, const std::string& message) override
    {
        // 네트워크에 기록
    }
};

class DLogger {
    std::vector<DLoggerTarget*> targets;

public:
    void AddTarget(DLoggerTarget* p) { targets.push_back(p); }

    void Write(Level level, const std::string& message)
    {
        for (DLoggerTarget* p : targets) {
            // p->Write(level, message);
        }
    }
};

#include <gtest/gtest.h>

#include <algorithm>

// DLogger에 Write 하였을 때, 등록된 타겟에 Write가 제대로 수행되었는지 여부를
// 검증하고 싶습니다.

// Test Spy Pattern
//  의도: 함수를 호출하였을 때, 발생하는 부수효과를 관찰할 수 없어서 테스트 안된 요구사항이 있을 때
//  방법: 목격한 일을 기록해두었다가, 나중에 테스트에서 확인할 수 있도록 만들어진 테스트 대역
//      "다른 컴포넌트로부터의 간접 출력을 저장해두었다가 검증에 사용합니다."

class SpyTarget : public DLoggerTarget {
private:
    std::vector<std::string> history;

    std::string concat(Level level, const std::string& message) const
    {
        static std::string levels[] = { "I", "W", "E" };
        return levels[level] + "@" + message;
    }

public:
    void Write(Level level, const std::string& message) override
    {
        history.push_back(concat(level, message));
    }

    bool IsReceived(Level level, const std::string& message) const
    {
        return std::find(begin(history), end(history), concat(level, message))
            != end(history);
    }
};

TEST(DLoggerTest, Write)
{
    DLogger logger;
    SpyTarget t1, t2;
    logger.AddTarget(&t1);
    logger.AddTarget(&t2);
    Level test_level = INFO;
    std::string test_message = "test_message";

    logger.Write(test_level, test_message);

    EXPECT_TRUE(t1.IsReceived(test_level, test_message));
    EXPECT_TRUE(t2.IsReceived(test_level, test_message));
}