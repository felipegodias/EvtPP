cmake_minimum_required(VERSION 3.16)

add_executable(EvtPP.Tests
    "Main.cpp"
    "Unit/EventHandlerUnitTestSuite.cpp"
    "Unit/EventBusUnitTestSuite.cpp"
)

find_package(GTest CONFIG REQUIRED)
target_link_libraries(EvtPP.Tests PRIVATE 
    EvtPP
    GTest::gmock
    GTest::gtest
    GTest::gmock_main
    GTest::gtest_main
)