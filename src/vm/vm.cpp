#include "vm.hpp"

void Vm::run(int fuel) {
    flags &= 0xFFFE;
    while (!(flags & 0x1) && fuel != 0) {
        step();
        fuel--;
    }
}

void Vm::step() {
    if (pc >= module->instructions.size()) {
        throw runtime_error("trap: program counter is out of bounds");
    }

    Instruction* instruction = module->instructions[pc];
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

const int Vm::peek() {
    return stack[sp];
}
