// 17_Mocking3.cpp
#include <gmock/gmock.h>

template <typename T>
struct StackInterface {
    virtual ~StackInterface() { }

    virtual int GetSize() const = 0;
    virtual void Push(const T& x) = 0;
};

// 템플릿 기반 인터페이스/추상클래스도 Mocking이 가능합니다.
template <typename T>
class MockStackInterface : public StackInterface<T> {
public:
    // MOCK_METHOD(int, GetSize, (), (const, override));
    // MOCK_METHOD(void, Push, (const T& x), (override));
};

TEST(StackTest, Sample)
{
    MockStackInterface<int> mock;

    // MOCK_METHOD한 함수에 대해서만 사용할 수 있습니다.
    EXPECT_CALL(mock, GetSize);
}