#pragma once
#include <utility>
#include <vector>

#include "instruction.hpp"

using namespace std;

struct Module {
    vector<Instruction> _instructions;

    explicit Module(vector<Instruction> instructions): _instructions(move(instructions)) {}
};
