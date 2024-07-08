#pragma once

#include <module.hpp>

#include "constants.hpp"

using namespace std;

class Vm
{
    Module* module; // execution module

    size_t sp = 0; // stack pointer
    size_t pc = 0; // program counter

    // Optimization: leave as last member of the class
    int stack[VM_STACK_SIZE] = {}; // stack space

    explicit Vm(Module* module) : module(module) {};
};
