// 4_스위트픽스쳐.cpp

#include <string>
#include <unistd.h> // sleep

class Terminal
{
public:
  void Connect() {}
  void Disconnect() {}

  void Login(const std::string &id, const std::string &password) {}
  void Logout() {}

  bool IsLogin() { return false; }
};

#include <gtest/gtest.h>

// 암묵적 설치 / 해체
// => 명시적인 Test Suite 클래스를 제공해야 합니다.

class TerminalTest : public testing::Test {
protected:
  Terminal *term;

  void SetUp() override 
  {
    term = new Terminal;
    term->Connect();
  }

  void TearDown() override
  {
    term->Disconnect();
    delete term;
  }
};

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
