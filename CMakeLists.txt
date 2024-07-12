cmake_minimum_required(VERSION 3.20)

project(rle-vm LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(front
    src/front/token.cpp
    src/front/lexer.cpp
)
add_library(vm
    src/vm/vm.cpp
    src/vm/definitions.cpp
)
target_include_directories(front PUBLIC src/front)
target_include_directories(vm PUBLIC src/vm)

target_link_libraries(front PRIVATE vm)

# enable all warnings
if(MSVC)
  target_compile_options(front PRIVATE /W4)
else()
  target_compile_options(front PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_executable(tokenizer src/sdk/tokenizer.cpp)
add_executable(assembler src/sdk/assembler.cpp)

# Qt GUI targets
add_subdirectory(src/dbg)

target_link_libraries(tokenizer PRIVATE front)
target_include_directories(tokenizer PRIVATE vendor/)

target_link_libraries(assembler PRIVATE front vm)
target_include_directories(assembler PRIVATE vendor/)

install(TARGETS tokenizer assembler RUNTIME DESTINATION bin)

# testing setup
enable_testing()
add_test(NAME tokenizer_runs COMMAND tokenizer ../tests/syntax/basic.asm)
add_test(NAME assembler_runs COMMAND assembler ../tests/syntax/basic.asm)
