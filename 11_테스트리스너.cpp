// 11_테스트리스너.cpp
#include <gtest/gtest.h>
// => GoogleTest 고유의 기능입니다.
// => 테스트가 수행되면서 발생하는 모든 단계의 이벤트를 수신할 수 있습니다.
//   <활용>
//    : 나만의 테스트 출력 만들기

#include <iostream>
using namespace std;
using namespace testing;

TEST(SampleTest, foo) { }
TEST(SampleTest, goo) { }

class MyTestResultPrinter : public testing::EmptyTestEventListener {
public:
    void OnTestProgramStart(const UnitTest& /*unit_test*/) override
    {
        cout << "My Test Program Start" << endl;
    }

    void OnTestProgramEnd(const UnitTest& /*unit_test*/) override
    {
        cout << "My Test Program End" << endl;
    }

    void OnTestSuiteStart(const TestSuite& test_suite) override
    {
        cout << test_suite.name() << " Start" << endl;
    }

    void OnTestSuiteEnd(const TestSuite& test_suite) override
    {
        cout << test_suite.name() << " End" << endl;
    }

    void OnTestStart(const TestInfo& test_info) override
    {
        cout << test_info.name() << endl;
    }
    void OnTestEnd(const TestInfo& test_info) override
    {
        cout << test_info.name() << ": "
             << (test_info.result()->Passed()
                        ? "[PASS]"
                        : "[FAIL]")
             << endl;
    }
};

// 테스트를 이벤트를 등록하기 위한 main을 구현해야 합니다.
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    testing::TestEventListeners& listeners = testing::UnitTest::GetInstance()->listeners();

    // 기본 프린터 이벤트 리스너를 제거하는 방법.
    delete listeners.Release(listeners.default_result_printer());

    listeners.Append(new MyTestResultPrinter); // !!

    return RUN_ALL_TESTS();
}