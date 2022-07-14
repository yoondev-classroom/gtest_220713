// 12_테스트대역.cpp

// 테스트 대역 목적
// : 테스트 환경을 통제하기 위해 사용한다.
// > 테스트 대역은 협력 객체를 "교체 가능"하도록 설계해야 합니다.
//  - 강한 결합: 협력 객체를 이용할 때, 구체적인 타입에 의존하는 것
//  - 약한 결합: 협력 객체를 이용할 때, 추상 타입(추상 클래스나 인터페이스)에 의존하는 것

// 객체지향 설계 원칙
//   - OCP(개방 폐쇄 원칙)
//     : 수정에는 닫혀 있고, 확장에는 열려 있어야 한다.
//   - DIP(의존 관계 역전 원칙)
//     : 클라이언트는 구체적인 타입에 의존하는 것이 아니라, 추상 개념에 의존해야 한다.
//     => 교체 가능한 설계

#include <string>

class FileSystem {
public:
    bool IsValid(const std::string& filename)
    {
        // 현재의 파일 시스템에서 적합한 이름인지 확인합니다.
        // return true;
        return false;
    }
};

// Logger --------> FileSystem(협력 객체)

class Logger {
public:
    // log 파일은 확장자를 제외한 파일의 이름이 5글자 이상이어야 한다.
    //  >  file.log - invalid
    //    hello.log - valid
    bool IsValidLogFilename(const std::string& filename)
    {
        //-------
        size_t index = filename.find_last_of(".");
        std::string name = filename.substr(0, index);
        if (name.size() < 5) {
            return false;
        }
        //-------

        // 파일 시스템에서 확인이 필요합니다.
        FileSystem fs;
        return fs.IsValid(filename);
    }
};

#include <gtest/gtest.h>

TEST(LoggerTest, IsValidLogFilename_NameLoggerThan5Chars_ReturnsTrue)
{
    Logger logger;
    std::string validFilename = "valid_file.log";

    EXPECT_TRUE(logger.IsValidLogFilename(validFilename))
        << "확장자를 제외한 파일명이 다섯글자 이상일 때";
}

TEST(LoggerTest, IsValidLogFilename_NameShorterThan5Chars_ReturnsFalse)
{
    Logger logger;
    std::string invalidFilename = "bad.log";

    EXPECT_FALSE(logger.IsValidLogFilename(invalidFilename))
        << "확장자를 제외한 파일명이 다섯글자 미만일 때";
}