#include "EvpPP/EvtPP.hpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

namespace EvtPP::Tests::Unit
{
    struct MockEvent
    {
    };

    class MockEventListener final : public IEventListener<MockEvent>
    {
    public:
        MOCK_METHOD(void, OnReceiveEvent, (const MockEvent& event), (override));
    };

    TEST(EventHandlerUnitTestSuite, Register_WhenCalled_StandardCase)
    {
        // Setup
        MockEventListener mockEventListener;
        EventHandler<MockEvent> eventHandler;
        const size_t expectedListenersCount = eventHandler.GetListenersCount() + 1;

        // Act
        eventHandler.Register(mockEventListener);
        const size_t actualListenersCount = eventHandler.GetListenersCount();

        // Assert
        EXPECT_EQ(expectedListenersCount, actualListenersCount);
    }

    TEST(EventHandlerUnitTestSuite, Register_WhenCalledTwiceForSameObject_MustThrowRuntimeError)
    {
        // Setup
        MockEventListener mockEventListener;
        EventHandler<MockEvent> eventHandler;
        eventHandler.Register(mockEventListener);

        // Act & Assert
        EXPECT_THROW(eventHandler.Register(mockEventListener), std::runtime_error);
    }

    TEST(EventHandlerUnitTestSuite, Deregister_WhenCalled_StandardCase)
    {
        // Setup
        MockEventListener mockEventListener;
        EventHandler<MockEvent> eventHandler;
        eventHandler.Register(mockEventListener);

        // Act
        const size_t expectedListenersCount = eventHandler.GetListenersCount() - 1;
        eventHandler.Deregister(mockEventListener);
        const size_t actualListenersCount = eventHandler.GetListenersCount();

        // Assert
        EXPECT_EQ(expectedListenersCount, actualListenersCount);
    }

    TEST(EventHandlerUnitTestSuite, Deregister_WhenCalledForUnregisteredObject_MustThrowRuntimeError)
    {
        // Setup
        const MockEventListener mockEventListener;
        EventHandler<MockEvent> eventHandler;

        // Act & Assert
        EXPECT_THROW(eventHandler.Deregister(mockEventListener), std::runtime_error);
    }

    TEST(EventHandlerUnitTestSuite, IsRegistered_WhenCalledWithRegisteredObject_MustReturnTrue)
    {
        // Setup
        MockEventListener mockEventListener;
        EventHandler<MockEvent> eventHandler;
        eventHandler.Register(mockEventListener);

        // Act
        const bool actual = eventHandler.IsRegistered(mockEventListener);

        // Assert
        const bool expected = true;
        EXPECT_EQ(expected, actual);
    }

    TEST(EventHandlerUnitTestSuite, IsRegistered_WhenCalledWithUnregisteredObject_MustReturnFalse)
    {
        // Setup
        const MockEventListener mockEventListener;
        EventHandler<MockEvent> eventHandler;

        // Act
        const bool actual = eventHandler.IsRegistered(mockEventListener);

        // Assert
        const bool expected = false;
        EXPECT_EQ(expected, actual);
    }

    TEST(EventHandlerUnitTestSuite, Fire_WhenCalled_StandardCase)
    {
        // Setup
        MockEventListener mockEventListener;
        MockEvent mockEvent;
        EventHandler<MockEvent> eventHandler;
        eventHandler.Register(mockEventListener);

        // Assert
        EXPECT_CALL(mockEventListener, OnReceiveEvent(testing::Ref(mockEvent))).Times(testing::Exactly(1));

        // Act
        eventHandler.Fire(mockEvent);
    }

    TEST(EventHandlerUnitTestSuite, Fire_CalledWhenHaveNoListeners_MustDoNothing)
    {
        // Setup
        const MockEvent mockEvent;
        EventHandler<MockEvent> eventHandler;

        // Act
        eventHandler.Fire(mockEvent);
    }
}
