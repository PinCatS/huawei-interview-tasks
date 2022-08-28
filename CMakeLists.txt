cmake_minimum_required(VERSION 3.10)

project(Problems)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(include)

option(DEBUG "Build debug version" ON)

set(CMAKE_CXX_STANDARD 17)
if(DEBUG)
    set(CMAKE_CXX_FLAGS "-g -O0 -Wall -Wextra -pedantic -Werror")
else()
    set(CMAKE_CXX_FLAGS "-O2 -Wall -Wextra -pedantic -Werror")   
endif()


add_executable(text1 src/text1.cpp)
add_executable(text2 src/text2.cpp)
add_executable(text3 src/text3.cpp)

# Enable testing via Catch2
Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

add_executable(tests test/test.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

include(CTest)
add_test(NAME Tests COMMAND $<TARGET_FILE:tests>)
