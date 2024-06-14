#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

enum TokenType {
    IDENTIFIER,
    NUMERIC,
    NEWLINE,
    HASH,
    UNKNOWN,
};

struct Cursor {
    unsigned int line;
    unsigned int column;

    Cursor(unsigned int line, unsigned int column) : line(line), column(column) {}
};

struct Span {
    Cursor start;
    Cursor end;

    Span(Cursor start, Cursor end) : start(start), end(end) {}
};

struct Token {
    string value;
    TokenType type;
    Span span;

    Token(string value, TokenType type, Span span) : value(value), type(type), span(span) {}
};

class Tokenizer {
    const size_t BUFFER_SIZE = 256;

private:
    istream* _stream;
    vector<char> _buffer;
    size_t _cursor = 0;
    streamsize _size = 0;
    Cursor position = Cursor(1, 1);

    void fill_buffer();

    bool cursor_next();

    bool condition_check(bool (*condition)(char));

    bool is_whitespace();
    bool is_newline();
    bool is_alphanumeric();
    bool is_hash();
    bool is_eof();

public:
    Tokenizer(istream* stream) : _stream(stream), _buffer(BUFFER_SIZE) { fill_buffer(); }

    Token* next();
};
