#include "token.hpp"

void Tokenizer::fill_buffer() {
    _stream->read(&_buffer[0], BUFFER_SIZE);
    _size = _stream->gcount();
}

bool Tokenizer::cursor_next() {
    if (is_newline()) {
        position.line++;
        position.column = 0;
    }

    _cursor++;
    if (_cursor >= _size) {
        fill_buffer();
        _cursor = 0;
    }

    bool input_not_eof = _size > 0;
    if (input_not_eof) position.column++;
    return input_not_eof;
}

bool Tokenizer::condition_check(bool (*condition)(char)) {
    if (is_eof()) return false;
    char current = _buffer[_cursor];
    return condition(current);
}

bool Tokenizer::is_whitespace() {
    return condition_check([](char c) { return c == ' ' || c == '\t'; });
}

bool Tokenizer::is_newline() {
    return condition_check([](char c) { return c == '\n'; });
}

bool Tokenizer::is_alphanumeric() {
    return condition_check([](char c) { return (bool)isalnum(c) || c == '_' || c == '-'; });
}

bool Tokenizer::is_hash() {
    return condition_check([](char c) { return c == '#'; });
}

bool Tokenizer::is_colon() {
    return condition_check([](char c) { return c == ':'; });
}

bool Tokenizer::is_comma() {
    return condition_check([](char c) { return c == ','; });
}

bool Tokenizer::is_eof() const {
    return _cursor >= _size;
}


Token* Tokenizer::next() {
    string token;
    while (is_whitespace() && cursor_next()) {};

    bool numeric = true;
    const Cursor start = position;
    while (is_alphanumeric()) {
        token.push_back(_buffer[_cursor]);
        numeric &= isdigit(_buffer[_cursor]) || (_buffer[_cursor] == '-' && token.length() < 2);
        cursor_next();
    }

    if (token.empty() && !is_eof()) {
        token.push_back(_buffer[_cursor]);
        TokenType type = TokenType::Unknown;

        if (is_newline()) {
            type = TokenType::Newline;
        } else if (is_hash()) {
            type = TokenType::Hash;
        } else if (is_colon()) {
            type = TokenType::Colon;
        } else if (is_comma()) {
            type = TokenType::Comma;
        }

        cursor_next();
        Span span = Span(start, position);
        return new Token(token,  type, span);
    }

    if (is_eof()) return NULL;
    return new Token(token, numeric ? TokenType::Numeric : TokenType::Identifier, Span(start, position));
}
