// 13_Stub.cpp
#include <iostream>

struct IConnection {
    virtual ~IConnection() { }

    virtual void Move(int x, int y) = 0;
    virtual void Attack() = 0;
};

class TCPConnection : public IConnection {
    // TCP 패킷을 통해 서버로 요청합니다.
    void Move(int x, int y) override { }
    void Attack() override { }
};

class NetworkException : public std::exception {
public:
    const char* what() noexcept { return "Bad network state"; }
};

class Player {
    IConnection* conn;

public:
    Player(IConnection* conn)
        : conn(conn)
    {
    }

    void Move(int x, int y)
    {
        try {
            conn->Move(x, y);
        } catch (NetworkException& e) {
            // 연결이 끊겼을 때의 동작
            throw e;
        }
    }
};

#include <gtest/gtest.h>

// Test Stub Pattern
//   의도: '다른 컴포넌트로부터의 간접 입력'에 의존하는 로직을 독립적으로 검증하고 싶다.
//   방법: 실제 의존하는 객체를 테스트용 객체로 교체해서,
//        SUT가 테스트하는데 필요한 결과를 보내도록 제어합니다.

// Player의 Move를 수행하였을 때,
// 네트워크 연결이 없다면, 예외가 제대로 발생하는지 여부를 검증하고 싶다.
TEST(PlayerTest, Move)
{
    TCPConnection conn;
    Player player(&conn);

    EXPECT_THROW(player.Move(10, 20), NetworkException);
}

// 의존성 주입
//  장점: 제품 코드를 사용하는 방식 그대로, 테스트도 수행할 수 있습니다.
class StubConnection : public IConnection {
public:
    void Move(int x, int y) override
    {
        throw NetworkException();
    }

    void Attack() override
    {
        throw NetworkException();
    }
};

TEST(PlayerTest, Move2)
{
    StubConnection conn; // !!!
    Player player(&conn);

    EXPECT_THROW(player.Move(10, 20), NetworkException);
}
