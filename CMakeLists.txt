cmake_minimum_required(VERSION 3.15)
project(CAC LANGUAGES CXX)

file(GLOB_RECURSE SRC_FILES
    "main.cpp"
    "src/*.cpp"
)

add_executable(cac_app ${SRC_FILES})

target_include_directories(cac_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(MSVC)
    target_compile_options(cac_app PRIVATE /W4 /std:c++latest)
else()
    target_compile_options(cac_app PRIVATE -Wall -Wextra -Wpedantic -std=c++2c)
endif()