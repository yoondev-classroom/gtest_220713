// 10_파라미터화테스트.cpp

bool IsPrime(int value)
{
    for (int i = 2; i < value; ++i) {
        if (value % 2 == 0)
            return false;
    }

    return false;
}

#include <gtest/gtest.h>

TEST(PrimeTest, IsPrime2)
{
    EXPECT_TRUE(IsPrime(2));
    EXPECT_TRUE(IsPrime(3));
    EXPECT_TRUE(IsPrime(5));
    EXPECT_TRUE(IsPrime(7));
    EXPECT_TRUE(IsPrime(11));
    EXPECT_TRUE(IsPrime(13));
    EXPECT_TRUE(IsPrime(17));
    EXPECT_TRUE(IsPrime(23));
    EXPECT_TRUE(IsPrime(29));
    EXPECT_TRUE(IsPrime(37));
}

// 2, 3, 5, 7, 11, 13, 17, 23, 29, 37
TEST(PrimeTest, IsPrime)
{
    int data[] = { 2, 3, 5, 7, 11, 13, 17, 23, 29, 37 };

    for (int i = 0; i < 10; ++i) {
        EXPECT_TRUE(IsPrime(data[i])) << "index: " << i << " data[i]: " << data[i];
    }
}