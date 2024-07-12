#pragma once

#include "module.hpp"
#include "constants.hpp"

using namespace std;

class Vm
{
public:
    Module* module; // execution module

    size_t sp = 0; // stack pointer
    size_t pc = 0; // program counter
    unsigned int flags = 0; // program flags:
    // 0x1: STOP

    // Optimization: leave as last member of the class
    int stack[VM_STACK_SIZE] = {}; // stack space

    explicit Vm(Module* module) : module(module) {};

    void run(int fuel = -1);
    void step();

    void push(int value);
    int pop();
    const int peek();
};
