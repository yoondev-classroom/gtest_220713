// 7_비기능테스트3.cpp

#include <iostream>
#include <string>

#define DECLARE_GTEST_LEAK_TEST()         \
    static int alloc;                     \
    void* operator new(size_t size)       \
    {                                     \
        ++alloc;                          \
        return malloc(size);              \
    }                                     \
                                          \
    void operator delete(void* p, size_t) \
    {                                     \
        free(p);                          \
        --alloc;                          \
    }

#define IMPLEMENTS_GTEST_LEAK_TEST(classname) \
    int classname::alloc = 0;

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

#ifdef GTEST_LEAK_TEST
    DECLARE_GTEST_LEAK_TEST()
#endif
};

#ifdef GTEST_LEAK_TEST
IMPLEMENTS_GTEST_LEAK_TEST(Image)
#endif

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
#ifdef GTEST_LEAK_TEST
        alloc = Image::alloc;
#endif
    }

    void TearDown() override
    {
#ifdef GTEST_LEAK_TEST
        int diff = Image::alloc - alloc;
        EXPECT_EQ(diff, 0) << diff << " object(s) leaks";
#endif
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