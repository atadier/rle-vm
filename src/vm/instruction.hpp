#pragma once

struct Instruction {
    virtual void execute();
    virtual ~Instruction();
};
