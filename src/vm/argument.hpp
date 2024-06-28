#pragma once
#include <string>

#include "constants.hpp"

using namespace std;

enum ArgumentType {
    Register,
    Number,
    None // Marker type for null/invalid arguments
};

struct Argument {
    ArgumentType type;
    int _numericValue{};

    Argument() : type(None) {};

    Argument(const ArgumentType type, const int value) : type(type), _numericValue(value) {

    };

    Argument(const ArgumentType type, const string& value) : type(type) {
        switch (type) {
            case Register: {
                if (value.length() == 2 && value.at(0) == 'r') {
                    ssize_t registerId = value.at(1) - 0x30;
                    if (registerId >= 0 && registerId < VM_GP_INTEGER_REGISTERS) {
                        // Register ID is correct and well-formed
                        _numericValue = int(registerId);
                        break;
                    }
                }
                this->type = None; // Invalid argument value
                break;
            }
            case Number: try {
                _numericValue = stoi(value);
                break;
            } catch (invalid_argument&) {
                this->type = None; // Invalid argument value
                break;
            }
            default:
                break;
        }
    }

    [[nodiscard]] string display_value() const {
        switch (type) {
            case Register:
                return "r" + to_string(_numericValue);
            case Number:
                return to_string(_numericValue);
            default:
                return "[INVALID]";
        }
    }
};