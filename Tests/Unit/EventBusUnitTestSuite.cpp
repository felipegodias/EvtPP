#include "EvpPP/EvtPP.hpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

namespace EvtPP::Tests::Unit
{
    struct MockEvent1
    {
    };

    class MockEventListener1 : public IEventListener<MockEvent1>
    {
    public:
        MOCK_METHOD(void, OnReceiveEvent, (const MockEvent1& event), (override));
    };

    class MockEventHandler1 : public IEventHandler<MockEvent1>
    {
    public:
        MOCK_METHOD(size_t, GetListenersCount, (), (const, override));
        MOCK_METHOD(void, Register, (IEventListenerType& eventListener), (override));
        MOCK_METHOD(void, Deregister, (const IEventListenerType& eventListener), (override));
        MOCK_METHOD(bool, IsRegistered, (const IEventListenerType& eventListener), (override));
        MOCK_METHOD(void, Fire, (const Event& event), (override));
    };

    struct MockEvent2
    {
    };

    class MockEventListener2 : public IEventListener<MockEvent2>
    {
    public:
        MOCK_METHOD(void, OnReceiveEvent, (const MockEvent2& event), (override));
    };

    class MockEventHandler2 : public IEventHandler<MockEvent2>
    {
    public:
        MOCK_METHOD(size_t, GetListenersCount, (), (const, override));
        MOCK_METHOD(void, Register, (IEventListenerType& eventListener), (override));
        MOCK_METHOD(void, Deregister, (const IEventListenerType& eventListener), (override));
        MOCK_METHOD(bool, IsRegistered, (const IEventListenerType& eventListener), (override));
        MOCK_METHOD(void, Fire, (const Event& event), (override));
    };

    UPtr<MockEventHandler1> mockEventHandler1;
    UPtr<MockEventHandler2> mockEventHandler2;
}

namespace EvtPP
{
    template <>
    IEventHandler<Tests::Unit::MockEvent1>& EventHandlerContainer::FetchHandler()
    {
        return *Tests::Unit::mockEventHandler1;
    }

    template <>
    IEventHandler<Tests::Unit::MockEvent2>& EventHandlerContainer::FetchHandler()
    {
        return *Tests::Unit::mockEventHandler2;
    }
}

namespace EvtPP::Tests::Unit
{
    class MockEventHandlerContainer : public EventHandlerContainer
    {
    public:
        MOCK_METHOD(EventHandlerContainer::EventHandlers, GetEventHandlers, (), (const, override));
    };

    TEST(EventBusUnitTestSuite, Register_WhenCalled_StandardCase)
    {
        // Setup
        EventBus eventBus;
        MockEventListener1 mockEventListener;
        mockEventHandler1 = std::make_unique<MockEventHandler1>();

        // Assert
        EXPECT_CALL(*mockEventHandler1, Register(testing::Ref(mockEventListener))).Times(testing::Exactly(1));

        // Act
        eventBus.Register(mockEventListener);
    }

    TEST(EventBusUnitTestSuite, Deregister_WhenCalled_StandardCase)
    {
        // Setup
        EventBus eventBus;
        MockEventListener1 mockEventListener;
        mockEventHandler1 = std::make_unique<MockEventHandler1>();

        // Assert
        EXPECT_CALL(*mockEventHandler1, Deregister(testing::Ref(mockEventListener))).Times(testing::Exactly(1));

        // Act
        eventBus.Deregister(mockEventListener);
    }

    TEST(EventBusUnitTestSuite, Fire_WhenCalledWithExistingEvent_StandardCase)
    {
        // Setup
        MockEvent1 mockEvent;
        EventBus eventBus;
        mockEventHandler1 = std::make_unique<MockEventHandler1>();

        // Assert
        EXPECT_CALL(*mockEventHandler1, Fire(testing::Ref(mockEvent))).Times(testing::Exactly(1));

        // Act
        eventBus.Fire<MockEvent1>(mockEvent);
    }

    TEST(EventBusUnitTestSuite, Fire_WhenCalledFromArgs_StandardCase)
    {
        // Setup
        EventBus eventBus;
        mockEventHandler1 = std::make_unique<MockEventHandler1>();

        // Assert
        EXPECT_CALL(*mockEventHandler1, Fire(testing::_)).Times(testing::Exactly(1));

        // Act
        eventBus.Fire<MockEvent1>();
    }

    TEST(EventBusUnitTestSuite, Fire_WhenCalledToOneEvent_StandardCase)
    {
        // Setup
        EventBus eventBus;
        mockEventHandler1 = std::make_unique<MockEventHandler1>();
        mockEventHandler2 = std::make_unique<MockEventHandler2>();

        // Assert
        EXPECT_CALL(*mockEventHandler1, Fire(testing::_)).Times(testing::Exactly(1));
        EXPECT_CALL(*mockEventHandler2, Fire(testing::_)).Times(testing::Exactly(0));

        // Act
        eventBus.Fire<MockEvent1>();
    }

    TEST(EventBusUnitTestSuite, GetListenersCount_WhenCalled_StandardCase)
    {
        // Setup
        const auto handlerContainer = std::make_shared<MockEventHandlerContainer>();
        const EventBus eventBus(handlerContainer);
        mockEventHandler1 = std::make_unique<MockEventHandler1>();
        mockEventHandler2 = std::make_unique<MockEventHandler2>();
        const EventHandlerContainer::EventHandlers getEventHandlersResult = { mockEventHandler1.get(), mockEventHandler2.get() };
        const size_t eventHandler1Expected = 1;
        const size_t eventHandler2Expected = 1;
        const size_t expected = eventHandler1Expected + eventHandler2Expected;

        // Assert
        EXPECT_CALL(*mockEventHandler1, GetListenersCount()).Times(testing::Exactly(1)).WillRepeatedly(testing::Return(eventHandler1Expected));
        EXPECT_CALL(*mockEventHandler2, GetListenersCount()).Times(testing::Exactly(1)).WillRepeatedly(testing::Return(eventHandler2Expected));
        EXPECT_CALL(*handlerContainer, GetEventHandlers).Times(testing::Exactly(1)).WillRepeatedly(testing::Return(getEventHandlersResult));

        // Act
        const size_t actual = eventBus.GetListenersCount();

        // Assert
        EXPECT_EQ(expected, actual);
    }
}