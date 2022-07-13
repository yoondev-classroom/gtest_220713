// 4_스위트픽스쳐2.cpp

#include <string>
#include <unistd.h> // sleep

class Terminal
{
public:
  // Connect / Disconnect가 느리다고 가정합니다.
  void Connect() { sleep(2); }
  void Disconnect() { sleep(1); }

  void Login(const std::string &id, const std::string &password) {}
  void Logout() {}

  bool IsLogin() { return false; }
};

#include <gtest/gtest.h>

// 암묵적 설치 / 해체
// => 명시적인 Test Suite 클래스를 제공해야 합니다.

class TerminalTest : public testing::Test
{
protected:
  static Terminal *term;

  void SetUp() override
  {
  }

  void TearDown() override
  {
  }

  // 1.10 이전에 사용되던 스위트 픽스쳐 설치/해체 함수입니다.
  // - static void TearDownTestCase()
  // - static void SetUpTestCase()

  // Suite Test Fixture 입니다.
  static void SetUpTestSuite()
  {
    printf("SetUpTestSuite()\n");
    term = new Terminal;
    term->Connect();
  }

  static void TearDownTestSuite()
  {
    printf("TearDownTestSuite()\n");
    term->Disconnect();
    delete term;
  }
};

// static은 외부 정의가 필요합니다.
Terminal* TerminalTest::term = nullptr;

// 문제점: SetUp과 TearDown이 느려서 테스트 케이스가 추가될 때마다
//       전체적인 테스트의 수행 시간이 늘어나는 문제가 발생합니다.
//   => Slow Test 문제
//   1) 테스트가 너무 느려서, 테스트를 수행하는 개발자의 생산성을 떨어뜨립니다.
//   2) 테스트가 너무 느려서, 아무도 코드가 변경되어도 테스트를 수행하지 않는다.
//   해결방법: 스위트 픽스쳐
//     => xUnit Test Framework은 테스트 스위트 단위의 SetUp() / TearDown()을
//        제공합니다.

// Suite Fixture
// : "신선한 픽스쳐"의 전략이 "공유 픽스쳐"의 전략으로 변경됩니다.
//   공유 픽스쳐 전략
//  1) 빠릅니다.
//  2) 이전의 테스트 케이스를 통해서 공유 픽스쳐가 망가졌다면, 이후의 테스트의 결과를
//     신뢰할 수 없습니다.   
//    "변덕스러운 테스트"
//   > 스위트 픽스쳐(공유 픽스쳐)에서 변덕스러운 테스트가 발생한다면,
//     테스트 스위트를 분리해야 합니다.
//      100 -> 50 + 50 -> 50 + 25 + 25




TEST_F(TerminalTest, Login)
{
  term->Login("test_id", "test_password");

  ASSERT_TRUE(term->IsLogin()) << "로그인 하였을 때";
}

TEST_F(TerminalTest, Logout)
{
  term->Login("test_id", "test_password");
  term->Logout();

  ASSERT_FALSE(term->IsLogin()) << "로그아웃 하였을 때";
}

TEST_F(TerminalTest, First) {}
TEST_F(TerminalTest, Second) {}
TEST_F(TerminalTest, Third) {}

//-----
// xUnit Test Framework이 테스트를 실행하는 흐름

// SampleTest::SetUpTestSuite();

// SampleTest* ts = new SampleTest;
// ts->SetUp();
// TestBody1();
// ts->TearDown();
// delete ts;

// SampleTest* ts = new SampleTest;
// ts->SetUp();
// TestBody2();
// ts->TearDown();
// delete ts;

// SampleTest::TearDownTestSuite();