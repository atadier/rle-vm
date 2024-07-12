#pragma once
#include <utility>
#include <vector>

#include "instruction.hpp"

using namespace std;

struct Module {
    vector<Instruction*> instructions;

    explicit Module(vector<Instruction*> instructions): instructions(move(instructions)) {}
};
