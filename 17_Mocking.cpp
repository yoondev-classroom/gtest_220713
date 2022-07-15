
#include <gmock/gmock.h>

// Mocking: 모의 객체를 만드는 방법
struct MP3 {
    virtual ~MP3() { }

    virtual void Play() = 0;
    virtual void Stop(int n) = 0;

    virtual std::string GetName() const = 0;
    virtual void Go() const noexcept = 0;

    virtual std::pair<bool, int> GetPair() const = 0;
    virtual bool CheckMap(std::map<int, double> a, bool b) const = 0;
};

class MockMP3 : public MP3 {
public:
    // MOCK_METHOD(반환타입, 이름, (인자1, 인자2), (한정자1, 한정자2 ...))
    MOCK_METHOD(void, Play, (), (override));
    MOCK_METHOD(void, Stop, (int n), (override));

    MOCK_METHOD(std::string, GetName, (), (const, override));
    MOCK_METHOD(void, Go, (), (const, noexcept, override));

    // 템플릿 인자가 2개 이상 있는 경우, 괄호 처리가 필요합니다.
    MOCK_METHOD((std::pair<bool, int>), GetPair, (), (const, override));
    MOCK_METHOD(bool, CheckMap, ((std::map<int, double> a), bool b), (const, override));
};

TEST(MP3Test, Sample)
{
    MockMP3 mock; // !!!
}