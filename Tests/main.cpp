#include <iostream>

#include "EvpPP/evtpp.hpp"
#include "gtest/gtest.h"

/*
class FooTest : public testing::Test
{
protected:
    FooTest()
    {
    }

    ~FooTest() override
    {
    }

    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(FooTest, MethodBarDoesAbc)
{
    std::string a("123");
    std::string b("123");
    EXPECT_EQ(a, b);
}

TEST_F(FooTest, DoesXyz)
{
    EXPECT_EQ("abc", "abc");
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
*/

struct TestEvent
{
    TestEvent(const int a, const int b, const int c)
        : a(a),
          b(b),
          c(c)
    {
    }

    int a;
    int b;
    int c;
};

class TestListener final : public EvtPP::EventListener<TestEvent>, public EvtPP::EventListener<std::string>
{
public:
    explicit TestListener(EvtPP::EventBus& eventBus)
        : EventListener<TestEvent>(eventBus),
          EventListener<std::string>(eventBus)
    {
    }

    ~TestListener() override = default;

    void OnReceiveEvent(const TestEvent& event) override
    {
        std::cout << __FUNCSIG__ << std::endl;
        std::cout << event.a << ", " << event.b << ", " << event.c << std::endl;
        std::cout << std::endl;
    }


    void OnReceiveEvent(const std::string& event) override
    {
        std::cout << __FUNCSIG__ << std::endl;
        std::cout << event << std::endl;
        std::cout << std::endl;
    }
};

void OnReceiveEventFreeFunction(const TestEvent& event)
{
    std::cout << __FUNCSIG__ << std::endl;
    std::cout << event.a << ", " << event.b << ", " << event.c << std::endl;
    std::cout << std::endl;
}

int main(int argc, char** argv)
{
    EvtPP::EventBus eventBus;

    EvtPP::FunctionEventListener<TestEvent> functionEventListener(eventBus, &OnReceiveEventFreeFunction);
    {
        TestListener testListener(eventBus);
        eventBus.Fire<TestEvent>(1, 2, 3);
        eventBus.Fire<std::string>("Hello World!");
    }
    eventBus.Fire<TestEvent>(1, 2, 3);

    return 0;
}
