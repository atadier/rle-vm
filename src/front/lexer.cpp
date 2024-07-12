#include <string>
#include <format>
#include "lexer.hpp"

#include "argument.hpp"
#include "definitions.hpp"
#include "module.hpp"
#include "instruction.hpp"

void syntax_error(const Token* tok) {
    const string error = format("syntax error: invalid token at line {}, column {}", tok->span.start.line, tok->span.start.column);
    throw std::runtime_error(error);
}

void argument_error(const Token* tok, const size_t index) {
    const string error = format("argument error: invalid value for argument {} at line {}, column {}", index, tok->span.start.line, tok->span.start.column);
    throw std::runtime_error(error);
}

void unknown_mnemonic(const string& mnemonic, const size_t lineno) {
    const string error = format("error: unknown mnemonic '{}' at line {}", mnemonic, lineno);
    throw std::runtime_error(error);
}


Module* Lexer::build_module()
{
    vector<Instruction*> instructions;
    while (Instruction* instr = parse_toplevel()) {
        instructions.push_back(instr);
    }
    return new Module(instructions);
}

Instruction* Lexer::parse_toplevel(const string* label)
{
    const Token* current = _tokens.next();
    if (current == nullptr) return nullptr;
    switch (current->type) {
        case Newline:
            return parse_toplevel();
        case Identifier: {
            const string mnemonic = current->value;
            return parse_arguments(mnemonic, current->span.start.line);
        }
        case Hash: {
            // Skip to next line
            const Token* next_line = _tokens.next();
            while (next_line != nullptr && next_line->type != Newline) next_line = _tokens.next();
            return parse_toplevel();
        }
        default:
            syntax_error(current);
            return nullptr;
    }
}

Instruction* Lexer::parse_arguments(const string& mnemonic, const size_t lineno) {
    const Token* current = _tokens.next();
    if (current->type == Colon) {
        // What we parsed as the first argument isn't the mnemonic, it is the label.
        return parse_toplevel(&mnemonic);
    }

    const InstructionDefinition definition = get_definition(mnemonic);
    if (definition.mnemonic.empty()) unknown_mnemonic(mnemonic, lineno);

    Argument arguments[3];
    size_t argument_index = 0;
    bool comma_punctuated = false;
    while (current != nullptr) {
        switch (current->type) {
            case Newline:
                goto finish;
            case Identifier:
                [[fallthrough]];
            case Number: {
                if (!comma_punctuated && argument_index != 0) syntax_error(current);
                const Argument arg(definition.get_argument_type(argument_index), current->value);

                if (arg.type == None) argument_error(current, argument_index);
                arguments[argument_index] = arg;
                break;
            }
            case Comma:
                // Comma before first argument or multiple comma is invalid
                if (argument_index == 0 || comma_punctuated) syntax_error(current);

                comma_punctuated = true;
                current = _tokens.next();
                continue;
            default:
                syntax_error(current);
                return nullptr;
        }
        argument_index++;
        comma_punctuated = false;
        current = _tokens.next();
    }
    finish: return init_instruction(mnemonic, arguments);
}
