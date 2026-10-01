cmake_minimum_required(VERSION 3.15)
project(CAC LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE SRC_FILES 
    "main.cpp"
    "src/*.cpp"
)

add_executable(cac_app ${SRC_FILES})

target_include_directories(cac_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(MSVC)
    target_compile_options(cac_app PRIVATE /W4)
else()
    target_compile_options(cac_app PRIVATE -Wall -Wextra -Wpedantic)
endif()
