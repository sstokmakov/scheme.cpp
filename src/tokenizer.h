#pragma once

#include <variant>
#include <istream>
#include <string>

struct SymbolToken {
    std::string name;

    bool operator==(const SymbolToken&) const;
};

struct QuoteToken {
    bool operator==(const QuoteToken&) const;
};

struct DotToken {
    bool operator==(const DotToken&) const;
};

enum class BracketToken { OPEN, CLOSE };

struct ConstantToken {
    int value;

    bool operator==(const ConstantToken&) const;
};

using Token = std::variant<ConstantToken, BracketToken, SymbolToken, QuoteToken, DotToken>;

// Интерфейс, позволяющий читать токены по одному из потока.
class Tokenizer {
public:
    Tokenizer(std::istream* in);

    bool IsEnd() const;

    void Next();

    Token GetToken();

private:
    std::istream* in_;
    Token current_;
    bool is_end_ = false;
};
