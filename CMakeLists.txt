cmake_minimum_required(VERSION 3.28)
project(EventBus VERSION 1.0.0 DESCRIPTION "A versatile EventBus system for C++")

set(CMAKE_CXX_STANDARD 17 CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(EventBus SHARED src/eventbus.cpp
        src/compoundstring.cpp
        src/event.cpp)

add_executable(test test/main.cpp
        test/TestEvent.cpp)

set_target_properties(EventBus PROPERTIES
        PUBLIC_HEADER include/eventbus.h)

target_link_libraries(test EventBus)