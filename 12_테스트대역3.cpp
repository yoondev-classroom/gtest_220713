// 12_테스트대역3.cpp
#include <string>

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

class Logger {
private:
    IFileSystem* fs;

public:
    Logger(IFileSystem* fs = nullptr)
        : fs(fs)
    {
        if (fs == nullptr) {
            this->fs = new FileSystem;
        }
    }

    bool IsValidLogFilename(const std::string& filename)
    {
        //-------
        size_t index = filename.find_last_of(".");
        std::string name = filename.substr(0, index);
        if (name.size() < 5) {
            return false;
        }
        //-------

        return fs->IsValid(filename);
    }
};

#include <gmock/gmock.h>

class StubFileSystem : public IFileSystem {
public:
    MOCK_METHOD(bool, IsValid, (const std::string& filename), (override));
};

using testing::NiceMock;
using testing::Return;

TEST(LoggerTest, IsValidLogFilename_NameLoggerThan5Chars_ReturnsTrue)
{
    NiceMock<StubFileSystem> fs;
    ON_CALL(fs, IsValid).WillByDefault(Return(true));
    Logger logger(&fs);
    std::string validFilename = "valid_file.log";

    EXPECT_TRUE(logger.IsValidLogFilename(validFilename))
        << "확장자를 제외한 파일명이 다섯글자 이상일 때";
}

TEST(LoggerTest, IsValidLogFilename_NameShorterThan5Chars_ReturnsFalse)
{
    NiceMock<StubFileSystem> fs;
    ON_CALL(fs, IsValid).WillByDefault(Return(true));
    Logger logger(&fs);
    std::string invalidFilename = "bad.log";

    EXPECT_FALSE(logger.IsValidLogFilename(invalidFilename))
        << "확장자를 제외한 파일명이 다섯글자 미만일 때";
}