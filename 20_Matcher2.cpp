#include <gmock/gmock.h>

class Printer {
public:
    virtual void Print(int n) = 0;
    virtual void Print(char c) = 0;
};

void Print(Printer* p)
{
    p->Print('A');
    p->Print(42);
}

class MockPrinter : public Printer {
public:
    // ambiguous
    MOCK_METHOD(void, Print, (int n), (override));
    MOCK_METHOD(void, Print, (char c), (override));
};

using testing::Matcher;
using testing::TypedEq;
using testing::An;

TEST(PrinterTest, Print)
{
    MockPrinter mock;

    // Matcher
    EXPECT_CALL(mock, Print(Matcher<char>('A')));
    EXPECT_CALL(mock, Print(Matcher<int>(42)));

    // TypedEq
    EXPECT_CALL(mock, Print(TypedEq<char>('A')));
    EXPECT_CALL(mock, Print(TypedEq<int>(42)));

    // An
    EXPECT_CALL(mock, Print(An<char>()));
    EXPECT_CALL(mock, Print(An<int>()));

    Print(&mock);
}