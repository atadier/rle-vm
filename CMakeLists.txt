cmake_minimum_required(VERSION 3.5)

project(rle-vm)
set (CMAKE_CXX_STANDARD 20)

add_executable(tokenizer src/sdk/tokenizer.cpp)

target_include_directories(tokenizer PRIVATE src/front vendor/)

target_sources(tokenizer PRIVATE src/front/token.cpp)

install(TARGETS tokenizer RUNTIME DESTINATION bin)
