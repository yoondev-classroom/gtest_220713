// 6_GoogleTest2.cpp

#include <gtest/gtest.h>

// 6. 테스트 필터
// $ ./a.out --gtest_filter=ImageTest.foo
// $ ./a.out --gtest_filter=ImageTest.foo:ImageProcessorTest.hoo
// $ ./a.out --gtest_filter=*.foo
// $ ./a.out --gtest_filter=Image*.foo
// $ ./a.out --gtest_filter=*.foo:-ImageProcessorTest.*

// > 테스트 필터가 제대로 활용되기 위해서는 잘 약속된 이름 규칙이 필요합니다.
//   - P_
//   - N_
//   - X_

TEST(ImageTest, foo) { }
TEST(ImageTest, goo) { }
TEST(ImageTest, hoo) { }

TEST(ImageProcessorTest, foo) { }
TEST(ImageProcessorTest, goo) { }
TEST(ImageProcessorTest, hoo) { }

int cnt;
int GetCount() { return ++cnt; }

// 7. 테스트 반복 / 테스트 순서 무작위
// $ ./a.out --gtest_repeat=100 --gtest_shuffle --gtest_break_on_failure
//  > "변덕스러운 테스트"를 확인하는 목적으로 사용할 수 있습니다.
TEST(SampleTest, Sample1)
{
    EXPECT_EQ(GetCount(), 1);
}

TEST(SampleTest, Sample2)
{
    EXPECT_EQ(GetCount(), 2);
    cnt = 0;
}