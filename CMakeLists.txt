cmake_minimum_required(VERSION 3.14)

project(recreate-memory-leak
    LANGUAGES CXX
)

find_package(Qt5
    COMPONENTS
    REQUIRED
        Core
        Network
)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(recreate-memory-leak
    recreate-memory-leak.cpp
)

target_link_libraries(recreate-memory-leak
    Qt5::Core
    Qt5::Network
)
