#include "tokenizer.h"

bool SymbolToken::operator==(const SymbolToken& other) const {
    return name == other.name;
}

bool QuoteToken::operator==(const QuoteToken&) const {
    return true;
}

bool DotToken::operator==(const DotToken&) const {
    return true;
}

bool ConstantToken::operator==(const ConstantToken& other) const {
    return value == other.value;
}

Tokenizer::Tokenizer(std::istream* in) : in_(in) {
    Next();
}

bool Tokenizer::IsEnd() const {
    return is_end_;
}

static bool IsSymbolContinuation(const int c) {
    return c != EOF && !std::isspace(c) && c != '.' && c != '\'' && c != '(' && c != ')' &&
           c != '+';
}

void Tokenizer::Next() {
    while (!in_->eof() && std::isspace(in_->peek())) {
        in_->get();
    }
    is_end_ = in_->eof();
    if (is_end_) {
        return;
    }

    char ch = in_->get();

    if (ch == '(') {
        current_ = BracketToken::OPEN;
        return;
    }
    if (ch == ')') {
        current_ = BracketToken::CLOSE;
        return;
    }
    if (ch == '\'') {
        current_ = QuoteToken();
        return;
    }
    if (ch == '.') {
        current_ = DotToken();
        return;
    }

    if (((ch == '-' || ch == '+') && isdigit(in_->peek())) || isdigit(ch)) {
        std::string digits;
        digits += ch;
        while (in_->peek() >= '0' && in_->peek() <= '9') {
            digits += in_->get();
        }
        current_ = ConstantToken{std::stoi(digits)};
        return;
    }

    if (ch == '+' || ch == '-' || ch == '/') {
        current_ = SymbolToken{std::string(1, ch)};
        return;
    }

    std::string str;
    str += ch;
    while (IsSymbolContinuation(in_->peek())) {
        str += in_->get();
    }
    current_ = SymbolToken{str};
}

Token Tokenizer::GetToken() {
    return current_;
}
