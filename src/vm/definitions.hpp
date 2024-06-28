#pragma once
#include <string>

#include "instruction.hpp"

using namespace std;

Instruction* init_instruction(const string& mnemonic, Argument arguments[3]);

InstructionDefinition get_definition(const string& mnemonic);