// 3_테스트픽스쳐4.cpp
// => 테스트 프레임워크가 테스트를 수행하는 흐름

#include <gtest/gtest.h>

#include <iostream>
using namespace std;

// 1. 신선한 픽스쳐 전략
// : xUnit Test Framework은 각 테스트케이스를 수행할 때마다,
//   매번 새롭게 테스트 스위트 클래스를 생성합니다.
//  목적: 각각의 테스트케이스가 독립적으로 유지하는데 도움이 됩니다.

// 2. Test Suite
// : A test suite is a set of tests that all share the same fixture.
// => 동일한 픽스쳐를 가지는 테스트케이스의 집합입니다.

class ImageProcessorTest : public testing::Test
{
protected:
  ImageProcessorTest()
  {
    cout << "ImageProcessorTest()" << endl;
  }

  ~ImageProcessorTest()
  {
    cout << "~ImageProcessorTest()" << endl;
  }

  void SetUp() override { cout << "SetUp()" << endl; }
  void TearDown() override { cout << "TearDown()" << endl; }
};

TEST_F(ImageProcessorTest, BlurImage)
{
  cout << "ImageProcessorTest.BlurImage()" << endl;
}

TEST_F(ImageProcessorTest, ResizeImage)
{
  cout << "ImageProcessorTest.ResizeImage()" << endl;
}

#if 0
ts = new ImageProcessorTest()
ts.SetUp()
ImageProcessorTest.BlurImage()
ts.TearDown() 
delete ts;

// ts = new ImageProcessorTest()
ts.SetUp()
ImageProcessorTest.ResizeImage()
ts.TearDown()
delete ts;

#endif