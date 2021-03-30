#include "EvpPP/EvtPP.hpp"
#include "gtest/gtest.h"

namespace EvtPP::Tests::Integration
{
    struct FooEvent
    {
        explicit FooEvent(const int val)
            : val(val)
        {
        }

        int val;
    };

    struct BarEvent
    {
        explicit BarEvent(const int val)
            : val(val)
        {
        }

        int val;
    };

    class FooEventListener final : EventListener<FooEvent>
    {
    public:
        explicit FooEventListener(EventBus& eventBus, int* actual = nullptr)
            : EventListener<FooEvent>(eventBus), actual(actual)
        {
        }

        void OnReceiveEvent(const FooEvent& event) override
        {
            if (actual != nullptr)
            {
                *actual = event.val;
            }
        }

    private:
        int* actual;
    };

    TEST(EventBusIntegrationTestSuite, Register_WhenCalled_StandardCase)
    {
        // Setup
        EventBus eventBus;
        const size_t expected = 2;

        // Act
        FooEventListener fooEventListener(eventBus);
        FunctionEventListener<BarEvent> eventListener(eventBus, [](const BarEvent&) {});
        const size_t actual = eventBus.GetListenersCount();

        EXPECT_EQ(expected, actual);
    }

    TEST(EventBusIntegrationTestSuite, Deregister_WhenCalled_StandardCase)
    {
        // Setup
        EventBus eventBus;
        const size_t firstTimeExpected = 1;
        const size_t secondTimeExpected = 0;

        // Act
        size_t firstTimeActual;

        {
            FunctionEventListener<BarEvent> eventListener(eventBus, [](const BarEvent&) {});
            firstTimeActual = eventBus.GetListenersCount();
        }
        const size_t secondTimeActual = eventBus.GetListenersCount();

        // Assert
        EXPECT_EQ(firstTimeExpected, firstTimeActual);
        EXPECT_EQ(secondTimeExpected, secondTimeActual);
    }

    TEST(EventBusIntegrationTestSuite, Fire_WhenCalled_StandardCase)
    {
        // Setup
        EventBus eventBus;
        const int fooExpected = std::rand();
        const int barExpected = std::rand();

        // Act
        int fooActual = 0;
        int barActual = 0;
        FooEventListener fooEventListener(eventBus, &fooActual);
        FunctionEventListener<BarEvent> eventListener(eventBus, [&](const BarEvent& event)
        {
            barActual = event.val;
        });

        eventBus.Fire<FooEvent>(fooExpected);

        BarEvent barEvent(barExpected);
        eventBus.Fire(barEvent);

        // Assert
        EXPECT_EQ(fooExpected, fooActual);
        EXPECT_EQ(barExpected, barActual);
    }
}
