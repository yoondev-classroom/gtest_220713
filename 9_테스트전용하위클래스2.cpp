// 9_테스트전용하위클래스2.cpp

#include <iostream>

class Engine {
public:
    virtual ~Engine() { }

    // 가상함수
    virtual void Start()
    {
        std::cout << "Engine Start" << std::endl;
        // ...
    }
};

class Car {
private:
    Engine* engine;

public:
    Car(Engine* engine)
        : engine(engine)
    {
    }

    void Go()
    {
        engine->Start();
        // ....
    }
};

#include <gtest/gtest.h>

class TestEngine : public Engine {
    bool isStart = false;

public:
    void Start() override
    {
        Engine::Start(); // 핵심: 부모 기능을 그대로 사용합니다.
        isStart = true;
    }

    // 테스트에서 확인하기 위한 함수를 제공합니다.
    bool IsStart() const { return isStart; }
};

TEST(CarTest, Go)
{
    TestEngine engine;
    Car car(&engine);

    car.Go();

    // 문제점: engine에 시작된 상태가 존재하지 않습니다.
    EXPECT_TRUE(engine.IsStart()) << "Car가 Go하였을 때";
}

#if 0
// Car의 Go를 하였을 때, Engine이 시작된 상태인지 검증하고 싶다.
TEST(CarTest, Go)
{
    Engine engine;
    Car car(&engine);

    car.Go();

    // 문제점: engine에 시작된 상태가 존재하지 않습니다.
}
#endif