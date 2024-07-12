#include "vm.hpp"

void Vm::run() {
    flags &= 0xFFFE;
    while (!(flags & 0x1)) {
        step();
    }
}

void Vm::step() {
    if (pc >= module->_instructions.size()) {
        throw runtime_error("trap: program counter is out of bounds");
    }

    Instruction* instruction = module->_instructions[pc];
    instruction->execute(this);
}

void Vm::push(int value) {
    sp++;
    if (sp >= VM_STACK_SIZE) throw runtime_error("trap: stack overflow");
    stack[sp] = value;
}

int Vm::pop() {
    if (sp == 0) throw runtime_error("trap: stack underflow");
    const int value = stack[sp];
    sp--;
    return value;
}
