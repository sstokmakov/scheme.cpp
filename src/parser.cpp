#include "object.h"
#include "parser.h"

#include "error.h"
#include "tokenizer.h"

#include <memory>
#include <iostream>

std::shared_ptr<Object> ReadList(Tokenizer* tokenizer) {
    if (tokenizer->IsEnd()) {
        throw SyntaxError{"SyntaxError"};
    }
    const auto token = tokenizer->GetToken();
    if (const auto bracket = std::get_if<BracketToken>(&token);
        bracket && *bracket == BracketToken::CLOSE) {
        tokenizer->Next();
        return nullptr;
    }

    const auto first = ReadValue(tokenizer);

    if (tokenizer->IsEnd()) {
        throw SyntaxError{"SyntaxError"};
    }

    std::shared_ptr<Object> second;
    if (std::holds_alternative<DotToken>(tokenizer->GetToken())) {
        tokenizer->Next();
        second = ReadValue(tokenizer);
        if (tokenizer->IsEnd()) {
            throw SyntaxError{"SyntaxError"};
        }
        const auto closing = tokenizer->GetToken();
        if (const auto bracket = std::get_if<BracketToken>(&closing);
            bracket && *bracket == BracketToken::CLOSE) {
            tokenizer->Next();
        } else {
            throw SyntaxError{"SyntaxError"};
        }
    } else {
        second = ReadList(tokenizer);
    }
    return std::make_shared<Cell>(first, second);
}

std::shared_ptr<Object> ReadValue(Tokenizer* tokenizer) {
    if (tokenizer->IsEnd()) {
        throw SyntaxError{"SyntaxError"};
    }
    const auto token = tokenizer->GetToken();
    if (const auto number = std::get_if<ConstantToken>(&token)) {
        auto result = std::make_shared<Number>(number->value);
        tokenizer->Next();
        return result;
    }
    if (const auto symbol = std::get_if<SymbolToken>(&token)) {
        if (symbol->name == "#f") {
            tokenizer->Next();
            return std::make_shared<Boolean>(false);
        }
        if (symbol->name == "#t") {
            tokenizer->Next();
            return std::make_shared<Boolean>(true);
        }
        auto result = std::make_shared<Symbol>(symbol->name);
        tokenizer->Next();
        return result;
    }
    if (const auto bracket = std::get_if<BracketToken>(&token);
        bracket && *bracket == BracketToken::OPEN) {
        tokenizer->Next();
        return ReadList(tokenizer);
    }
    if (std::get_if<QuoteToken>(&token)) {
        tokenizer->Next();
        return std::make_shared<Cell>(std::make_shared<Symbol>("quote"),
                                      std::make_shared<Cell>(ReadValue(tokenizer), nullptr));
    }

    throw SyntaxError{"SyntaxError"};
}

std::shared_ptr<Object> Read(Tokenizer* tokenizer) {
    auto result = ReadValue(tokenizer);
    if (!tokenizer->IsEnd()) {
        throw SyntaxError("SyntaxError");
    }
    return result;
}