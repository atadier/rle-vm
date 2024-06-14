cmake_minimum_required(VERSION 3.12)

project(rle-vm)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(tokenizer src/sdk/tokenizer.cpp)

target_include_directories(tokenizer PRIVATE src/front vendor/)

target_sources(tokenizer PRIVATE src/front/token.cpp)

install(TARGETS tokenizer RUNTIME DESTINATION bin)

enable_testing()
add_test(NAME tokenizer COMMAND tokenizer ../tests/syntax/basic.asm)
