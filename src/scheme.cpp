#include "scheme.h"
#include "builtin.h"
#include "eval.h"
#include "parser.h"
#include "tokenizer.h"
#include "serializer.h"

#include <string>
#include <sstream>

Scheme::Scheme() {
    environment_->Define("+", std::make_shared<Add>());
    environment_->Define("*", std::make_shared<Multiplication>());
    environment_->Define("-", std::make_shared<Subtraction>());
    environment_->Define("/", std::make_shared<Division>());
    environment_->Define("=", std::make_shared<Equal>());
    environment_->Define(">", std::make_shared<Greater>());
    environment_->Define("<", std::make_shared<Less>());
    environment_->Define(">=", std::make_shared<GreaterOrEqual>());
    environment_->Define("<=", std::make_shared<LessOrEqual>());
    environment_->Define("min", std::make_shared<Min>());
    environment_->Define("max", std::make_shared<Max>());
    environment_->Define("abs", std::make_shared<Abs>());
    environment_->Define("number?", std::make_shared<IsNumber>());
    environment_->Define("boolean?", std::make_shared<IsBoolean>());
    environment_->Define("symbol?", std::make_shared<IsSymbol>());
    environment_->Define("not", std::make_shared<Not>());
    environment_->Define("pair?", std::make_shared<IsPair>());
    environment_->Define("null?", std::make_shared<IsNull>());
    environment_->Define("cons", std::make_shared<Cons>());
    environment_->Define("car", std::make_shared<Car>());
    environment_->Define("cdr", std::make_shared<Cdr>());
    environment_->Define("list?", std::make_shared<IsList>());
    environment_->Define("list", std::make_shared<List>());
    environment_->Define("list-ref", std::make_shared<ListRef>());
    environment_->Define("list-tail", std::make_shared<ListTail>());
    environment_->Define("set-car!", std::make_shared<SetCar>());
    environment_->Define("set-cdr!", std::make_shared<SetCdr>());
}

std::string Scheme::Evaluate(const std::string& expression) {
    auto stream = std::stringstream(expression);
    auto tokenizer = Tokenizer(&stream);
    auto ast = Read(&tokenizer);
    const auto res = Eval(ast, environment_);
    return Serialize(res);
}
