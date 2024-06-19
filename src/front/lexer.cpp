#include <string>
#include <format>
#include "lexer.hpp"

#include "module.hpp"
#include "instruction.hpp"

void syntax_error(const Token* tok) {
    const string error = format("syntax error: invalid token at line {}, column {}", tok->span.start.line, tok->span.start.column);
    throw std::runtime_error(error);
}

Module* Lexer::build_module()
{
    vector<Instruction> instructions;
    while (const Instruction* instr = parse_toplevel()) {
        instructions.push_back(*instr);
    }
    return new Module(instructions);
}

Instruction* Lexer::parse_toplevel(const string* label)
{
    const Token* current = _tokens.next();
    if (current == nullptr) return nullptr;
    switch (current->type) {
        case NEWLINE:
            return parse_toplevel();
        case IDENTIFIER: {
            const string mnemonic = current->value;
            return parse_arguments(mnemonic);
        }
        case HASH: {
            // Skip to next line
            const Token* next_line = _tokens.next();
            while (next_line != nullptr && next_line->type != NEWLINE) next_line = _tokens.next();
            return parse_toplevel();
        }
        default:
            syntax_error(current);
            return nullptr;
    }
}

Instruction* Lexer::parse_arguments(const string& mnemonic) {
    const Token* current = _tokens.next();
    bool is_first_token = true;
    while (current != nullptr) {
        switch (current->type) {
            case COLON:
                if (!is_first_token) syntax_error(current);
                // What we parsed as the first argument isn't the mnemonic, it is the label.
                return parse_toplevel(&mnemonic);
            case NEWLINE:
                goto finish;
            case IDENTIFIER:
                break; // TODO
            case NUMERIC:
                break; // TODO
            default:
                syntax_error(current);
                return nullptr;
        }
        is_first_token = false;
        current = _tokens.next();
    }
    finish: return new Instruction(mnemonic);
}