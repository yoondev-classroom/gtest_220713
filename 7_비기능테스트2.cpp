// 7_비기능테스트2.cpp

#include <iostream>
#include <string>

// new
//  1) operator new : 메모리 할당
//  2) 생성자 호출

// delete
//  1) 소멸자 호출
//  2) operator delete: 메모리 해지

class Image {
    std::string url;

public:
    Image(const std::string& url)
        : url(url)
    {
    }

    void Draw() const
    {
        std::cout << "Draw image: " << url << std::endl;
    }

    static int alloc;

    // 테스트에서 활용하기 위해서, 메모리 연산자를 재정의합니다.
    void* operator new(size_t size)
    {
        ++alloc;
        return malloc(size);
    }

    void operator delete(void* p, size_t)
    {
        free(p);
        --alloc;
    }
};

int Image::alloc = 0;

#include <gtest/gtest.h>

void DrawImage(const std::string& url)
{
    Image* image = new Image(url);
    image->Draw();

    // delete image;
}

// TestSuite 클래스의 SetUp / TearDown에서 자동적으로 수행되도록 할 수
// 있습니다.
class ImageTest : public testing::Test {
private:
  int alloc;
protected:
  void SetUp() override 
  {
    alloc = Image::alloc;
  }

  void TearDown() override
  {
    int diff = Image::alloc - alloc;
    EXPECT_EQ(diff, 0) << diff << " object(s) leaks";
  }
};

TEST_F(ImageTest, Draw1)
{
  DrawImage("https://a.com");
}

TEST_F(ImageTest, Draw2)
{
  DrawImage("https://a.com");
}

#if 0
TEST(ImageTest, Draw)
{
    // DrawImage를 수행하였을 때, 객체의 메모리가 제대로 해지되었는지 여부를
    // 검증하고 싶다.

    int alloc = Image::alloc;

    DrawImage("https://a.com");

    int diff = Image::alloc - alloc;
    EXPECT_EQ(diff, 0) << diff << " object(s) leaks";
}
#endif