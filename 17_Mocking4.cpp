
#include <iostream>
using namespace std;

struct Packet { };

class PacketStream {
public:
    void AppendPacket(Packet* newPacket)
    {
        cout << "AppendPacket" << endl;
    }

    const Packet* GetPacket(size_t packetNumber) const
    {
        cout << "GetPacket" << endl;
        return nullptr;
    }
};

class PacketReader {
public:
    // 암묵적인 인터페이스, 단위 전략(Policy based Design)
    // => 컴파일 타임에 교체 가능합니다.
    template <typename PacketStream>
    void ReadPacket(PacketStream* stream, size_t packetNumber)
    {
        // stream->AppendPacket(nullptr);
        stream->GetPacket(10);
    }
};

#include <gmock/gmock.h>
// 암묵적인 인터페이스에 모의 객체를 만드는 방법

class MockPacketStream {
public:
    // void AppendPacket(Packet* newPacket)
    // const Packet* GetPacket(size_t packetNumber) const

    MOCK_METHOD(void, AppendPacket, (Packet * newPacket));
    MOCK_METHOD(const Packet*, GetPacket, (size_t packetNumber), (const));
};

TEST(PacketReaderTest, Sample)
{
    MockPacketStream stream;
    PacketReader reader;

    EXPECT_CALL(stream, AppendPacket);
    EXPECT_CALL(stream, GetPacket);

    reader.ReadPacket(&stream, 42);
}

#if 0
int main()
{
    PacketStream stream;
    PacketReader reader;

    reader.ReadPacket(&stream, 42);
}
#endif