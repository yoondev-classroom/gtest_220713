

#include <iostream>
using namespace std;

class User { };

namespace {
bool operator==(const User& lhs, const User& rhs)
{
    return true;
}
}

class Sample {
public:
  void foo() {
    User user1, user2;

    cout << (user1 == user2) << endl;
  }
};

int main()
{
  Sample sample;
  sample.foo();
}