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

#include <gmock/gmock.h>

class StubConnection : public IConnection {
public:
    MOCK_METHOD(void, Move, (int x, int y), (override));
    MOCK_METHOD(void, Attack, (), (override));
};

using testing::NiceMock;
using testing::Throw;

TEST(PlayerTest, Move2)
{
    NiceMock<StubConnection> conn;
    ON_CALL(conn, Move).WillByDefault(Throw(NetworkException()));
    Player player(&conn);

    EXPECT_THROW(player.Move(10, 20), NetworkException);
}
