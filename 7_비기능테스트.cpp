// 7_비기능테스트.cpp
// 정의: 기능적인 동작 뿐 아니라 성능이나 메모리 등의 비기능부분을 검증할 수 있습니다.

#include <string>
#include <unistd.h>

void OpenDatabase(const std::string& url)
{
    sleep(2);
}

#include <gtest/gtest.h>

// 사용자 정의 단언문
#define EXPECT_TIMEOUT(fn, limit)                    \
    do {                                             \
        time_t startTime = time(nullptr);            \
        fn;                                          \
        time_t duration = time(nullptr) - startTime; \
        EXPECT_LE(duration, limit);                  \
    } while (0)

TEST(OpenDatabaseTest, OpenDatabase2)
{
    EXPECT_TIMEOUT(OpenDatabase("https://a.com"), 1);
}

TEST(OpenDatabaseTest, OpenDatabase)
{
    // 위의 함수가 1초 안에 수행되는지 여부를 검증하고 싶다.
    time_t limit = 1;
    time_t startTime = time(nullptr);

    OpenDatabase("https://a.com");

    time_t duration = time(nullptr) - startTime;

    EXPECT_LE(duration, limit);
}
