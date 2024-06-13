cmake_minimum_required(VERSION 3.26)
project(Skillbox_Project)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

add_executable(Skillbox_Project main.cpp
        JsonHandler.h
        InvertedIndex.h
        SearchServer.h
        JsonHandler.cpp
        SearchServer.cpp
        InvertedIndex.cpp)

target_link_libraries(Skillbox_Project PRIVATE nlohmann_json::nlohmann_json)
