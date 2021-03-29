#include "EvpPP/EvtPP.hpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

namespace EvtPP::Tests
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
        MOCK_METHOD(void, Register, (IEventListener& eventListener), (override));
        MOCK_METHOD(void, Deregister, (const IEventListener& eventListener), (override));
        MOCK_METHOD(bool, IsRegistered, (const IEventListener& eventListener), (override));
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
        MOCK_METHOD(void, Register, (IEventListener& eventListener), (override));
        MOCK_METHOD(void, Deregister, (const IEventListener& eventListener), (override));
        MOCK_METHOD(bool, IsRegistered, (const IEventListener& eventListener), (override));
        MOCK_METHOD(void, Fire, (const Event& event), (override));
    };
}

namespace EvtPP
{
    UPtr<Tests::MockEventHandler1> mockEventHandler1;
    UPtr<Tests::MockEventHandler2> mockEventHandler2;

    template <>
    UPtr<IEventHandler<Tests::MockEvent1>> EventHandlerFactory::Create() const
    {
        return std::move(mockEventHandler1);
    }

    template <>
    UPtr<IEventHandler<Tests::MockEvent2>> EventHandlerFactory::Create() const
    {
        return std::move(mockEventHandler2);
    }
}

namespace EvtPP::Tests
{
    TEST(EventBusTestSuite, Register_WhenCalled_StandardCase)
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

    TEST(EventBusTestSuite, Deregister_WhenCalled_StandardCase)
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

    TEST(EventBusTestSuite, Fire_WhenCalledWithExistingEvent_StandardCase)
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

    TEST(EventBusTestSuite, Fire_WhenCalledFromArgs_StandardCase)
    {
        // Setup
        EventBus eventBus;
        mockEventHandler1 = std::make_unique<MockEventHandler1>();

        // Assert
        EXPECT_CALL(*mockEventHandler1, Fire(testing::_)).Times(testing::Exactly(1));

        // Act
        eventBus.Fire<MockEvent1>();
    }

    TEST(EventBusTestSuite, Fire_WhenCalledToOneEvent_StandardCase)
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
}