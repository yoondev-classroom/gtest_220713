// 16_Mock.cpp
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
            p->Write(level, message);
        }
    }
};

//  의도: 함수를 호출하였을 때, 발생하는 부수효과를 관찰할 수 없어서 테스트 안된 요구사항이 있을 때

// Test Spy Pattern
//  방법: 목격한 일을 기록해두었다가, 나중에 테스트에서 확인할 수 있도록 만들어진 테스트 대역
//      "다른 컴포넌트로부터의 간접 출력을 저장해두었다가 검증에 사용합니다."

// Mock Object Pattern
//  방법: 행위 기반 검증을 수행합니다.

//  상태 검증
//    : 객체에 작용을 가한 후, 단언 함수를 통해서 내부 상태값의 변화를 확인합니다.

//  동작 검증
//    : 객체에 작용을 가한 후, 내부적으로 발생하는 함수의 호출 여부, 호출 횟수, 호출 순서 등을
//      통해 정상 동작 여부를 검증합니다.
//    => Mock Object(모의 객체)
//    => Mock Framework을 이용해서, 모의 객체를 만들 수 있습니다.
//    Google Test
//      1.8: Google Test + Google Mock
//    C++: Google Mock
//   Java: jMock, EasyMock, Mockito, Spock ...

// gtest는 아래에서 자동으로 포함됩니다.
#include <gmock/gmock.h>

// 모의 객체를 만드는 방법 - Mocking
#if 0
struct DLoggerTarget {
    virtual ~DLoggerTarget() { }

    virtual void Write(Level level, const std::string& message) = 0;
};
#endif

class MockDLoggerTarget : public DLoggerTarget {
public:
    // MOCK_METHOD2(함수이름, 함수타입) - 1.10 이전
    // MOCK_METHOD2(Write, void(Level level, const std::string& message));

    // MOCK_METHOD(반환타입, 이름, 인자, 한정자) - 1.10 이후
    // void Write(Level level, const std::string& message) override

    MOCK_METHOD(void, Write, (Level level, const std::string& message), (override));
};

TEST(DLoggerTest, Write)
{
    // Arrange
    DLogger logger;
    MockDLoggerTarget t1, t2;
    logger.AddTarget(&t1);
    logger.AddTarget(&t2);
    Level test_level = INFO;
    std::string test_message = "test_message";

    // Assert
    EXPECT_CALL(t1, Write(test_level, test_message));
    EXPECT_CALL(t2, Write(test_level, test_message));

    // Act
    logger.Write(test_level, test_message);
}
// 주의사항: GoogleMock은 수행하기 이전에 EXPECT_CALL이 수행되어야 합니다.
//   => Act보다 Assert가 먼저 나옵니다.

// Test Double(테스트 대역)
// 1. Test Stub
//  - 특수한 상황을 시뮬레이션 합니다.
//  - 협력 객체가 원하는 결과를 주도록 제어한다.

// 2. Fake Object
//  - 가벼운 테스트 대역을 통해 아직 구현되지 않거나 사용하기 어려운 구현체를 대신한다.

// 3. Test Spy
//  - 관찰할 수 있는 부수효과가 없는 경우, 목격한 일을 기록해두었다가 검증에 사용한다.

// 4. Mock Object
//  - 행위 기반 검증
//---------------------------
// : xUnit Test Pattern이전에는 테스트 대역을 Mock이라고 불렀습니다.
//  - Google Mock
//   : 테스트 대역을 지원하는 프레임워크 입니다.