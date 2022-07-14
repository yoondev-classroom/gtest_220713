// 12_테스트대역2.cpp

// SUT가 테스트 대역을 사용할 수 있도록 만드는 작업
// => 틈새 만들기
// => 약한 결합
//   : 협력 객체를 직접 생성하면, 강한 결합이 형성됩니다.
//     외부에서 생성해서 전달해야 합니다.
//     => 의존성 주입(Dependency Injection)
//      1) 생성자 주입
//       : 협력 객체가 필수적일 때
//      2) 메소드 주입
//       : 협력 객체가 필수적이지 않을 때

#include <string>

// 1. 인터페이스를 도입합니다.
// 2. 협력 객체를 외부에서 생성해서 전달하도록 변경합니다.
//   => 의존성 주입, 생성자 주입
// 3. 기존의 동작과 동일하게 동작하는 것이 좋습니다.

struct IFileSystem {
    virtual ~IFileSystem() { }

    virtual bool IsValid(const std::string& filename) = 0;
};

class FileSystem : public IFileSystem {
public:
    bool IsValid(const std::string& filename) override
    {
        // 현재의 파일 시스템에서 적합한 이름인지 확인합니다.
        // return true;
        return false;
    }
};

// Logger --------> FileSystem(협력 객체)

class Logger {
private:
    IFileSystem* fs;

public:
    Logger(IFileSystem* fs = nullptr)
        : fs(fs)
    {
        // 호환성
        // : 제품 코드가 깨지는 것을 막아줍니다.
        if (fs == nullptr) {
            this->fs = new FileSystem;
        }
    }

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
        // FileSystem fs;
        // return fs.IsValid(filename);

        // IFileSystem* fs = new FileSystem; // !!
        return fs->IsValid(filename);
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