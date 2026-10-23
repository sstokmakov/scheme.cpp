#include "eval.h"
#include "error.h"
#include "lambda.h"

namespace {
bool IsTrue(const std::shared_ptr<Object>& condition) {
    if (!Is<Boolean>(condition)) {
        return true;
    }
    return As<Boolean>(condition)->GetValue();
}

std::vector<std::shared_ptr<Object>> ListToVector(const std::shared_ptr<Object>& list) {
    std::vector<std::shared_ptr<Object>> args;
    auto tail = list;
    while (tail != nullptr) {
        if (const auto tail_cell = As<Cell>(tail); tail_cell != nullptr) {
            args.push_back(tail_cell->GetFirst());
            tail = tail_cell->GetSecond();
        } else {
            throw SyntaxError{"SyntaxError"};
        }
    }
    return args;
}

std::vector<std::string> ParseParams(const std::shared_ptr<Object>& list) {
    std::vector<std::string> params;
    auto curr = list;
    while (curr != nullptr) {
        if (!Is<Cell>(curr)) {
            throw SyntaxError{"SyntaxError"};
        }
        const auto curr_cell = As<Cell>(curr);
        if (const auto symbol = As<Symbol>(curr_cell->GetFirst()); symbol != nullptr) {
            params.push_back(symbol->GetName());
        } else {
            throw SyntaxError{"SyntaxError"};
        }
        curr = curr_cell->GetSecond();
    }
    return params;
}

std::shared_ptr<Object> EvalLambda(const std::shared_ptr<Environment>& environment,
                                   const std::shared_ptr<Object>& second) {
    const auto args = ListToVector(second);

    if (args.size() < 2) {
        throw SyntaxError{"SyntaxError"};
    }

    std::vector<std::string> params = ParseParams(args[0]);
    std::vector body(args.begin() + 1, args.end());
    return std::make_shared<Lambda>(params, body, environment);
}

std::shared_ptr<Object> EvalDefine(const std::shared_ptr<Environment>& environment,
                                   const std::shared_ptr<Object>& second) {
    const auto args = ListToVector(second);

    if (args.size() < 2) {
        throw SyntaxError{"SyntaxError"};
    }

    if (const auto first_arg = As<Symbol>(args[0]); first_arg != nullptr) {
        if (args.size() != 2) {
            throw SyntaxError{"SyntaxError"};
        }
        environment->Define(first_arg->GetName(), Eval(args[1], environment));
        return nullptr;
    }
    if (const auto first_arg = As<Cell>(args[0]); first_arg != nullptr) {
        const auto name = As<Symbol>(first_arg->GetFirst());

        if (name == nullptr) {
            throw SyntaxError{"SyntaxError"};
        }

        std::vector<std::string> params = ParseParams(first_arg->GetSecond());
        std::vector body(args.begin() + 1, args.end());

        const auto function = std::make_shared<Lambda>(params, body, environment);
        environment->Define(name->GetName(), function);
        return nullptr;
    }
    throw SyntaxError{"SyntaxError"};
}

std::shared_ptr<Object> EvalSet(const std::shared_ptr<Environment>& environment,
                                const std::shared_ptr<Object>& second) {
    const auto args = ListToVector(second);
    if (args.size() != 2) {
        throw SyntaxError{"SyntaxError"};
    }
    if (const auto first_arg = As<Symbol>(args[0]); first_arg != nullptr) {
        environment->Set(first_arg->GetName(), Eval(args[1], environment));
        return nullptr;
    }
    throw SyntaxError{"SyntaxError"};
}

std::shared_ptr<Object> EvalIf(const std::shared_ptr<Environment>& environment,
                               const std::shared_ptr<Object>& second) {
    const auto args = ListToVector(second);
    if (args.size() != 2 && args.size() != 3) {
        throw SyntaxError{"SyntaxError"};
    }
    const auto condition = Eval(args[0], environment);

    if (IsTrue(condition)) {
        return Eval(args[1], environment);
    }

    if (args.size() == 3) {
        return Eval(args[2], environment);
    }
    return nullptr;
}

std::shared_ptr<Object> EvalAnd(const std::shared_ptr<Environment>& environment,
                                const std::shared_ptr<Object>& second) {

    const auto args = ListToVector(second);

    if (args.empty()) {
        return std::make_shared<Boolean>(true);
    }

    auto condition = Eval(args[0], environment);
    for (size_t i = 1; i < args.size(); ++i) {
        if (!IsTrue(condition)) {
            break;
        }
        condition = Eval(args[i], environment);
    }
    return condition;
}

std::shared_ptr<Object> EvalOr(const std::shared_ptr<Environment>& environment,
                               const std::shared_ptr<Object>& second) {
    const auto args = ListToVector(second);
    if (args.empty()) {
        return std::make_shared<Boolean>(false);
    }
    auto condition = Eval(args[0], environment);
    for (size_t i = 1; i < args.size(); ++i) {
        if (IsTrue(condition)) {
            break;
        }
        condition = Eval(args[i], environment);
    }
    return condition;
}

std::shared_ptr<Object> EvalQuote(const std::shared_ptr<Object>& second) {
    if (const auto second_cell = As<Cell>(second); second_cell != nullptr) {
        if (second_cell->GetSecond() != nullptr) {
            throw SyntaxError{"SyntaxError"};
        }
        return second_cell->GetFirst();
    }
    throw SyntaxError{"SyntaxError"};
}

std::shared_ptr<Object> EvalFunc(const std::shared_ptr<Environment>& environment,
                                 const std::shared_ptr<Object>& first,
                                 const std::shared_ptr<Object>& second) {
    const auto func = As<Function>(Eval(first, environment));

    if (func == nullptr) {
        throw RuntimeError{"RuntimeError"};
    }

    std::vector<std::shared_ptr<Object>> args;
    auto tail = second;
    while (tail != nullptr) {
        if (const auto tall_cell = As<Cell>(tail); tall_cell != nullptr) {
            const auto res = Eval(tall_cell->GetFirst(), environment);
            args.push_back(res);
            tail = tall_cell->GetSecond();
        } else {
            throw RuntimeError{"RuntimeError"};
        }
    }
    return func->Apply(args);
}
}  // namespace

std::shared_ptr<Object> Eval(std::shared_ptr<Object> object,
                             const std::shared_ptr<Environment>& environment) {
    if (Is<Number>(object)) {
        return object;
    }
    if (Is<Boolean>(object)) {
        return object;
    }
    if (Is<Symbol>(object)) {
        const auto symbol = As<Symbol>(object);
        return environment->Get(symbol->GetName());
    }
    if (Is<Cell>(object)) {
        const auto cell = As<Cell>(object);
        const auto first = cell->GetFirst();
        const auto second = cell->GetSecond();

        if (const auto symbol = As<Symbol>(first); symbol != nullptr) {
            const auto& name = symbol->GetName();
            if (name == "lambda") {
                return EvalLambda(environment, second);
            }
            if (name == "define") {
                return EvalDefine(environment, second);
            }
            if (name == "set!") {
                return EvalSet(environment, second);
            }
            if (name == "if") {
                return EvalIf(environment, second);
            }
            if (name == "and") {
                return EvalAnd(environment, second);
            }
            if (name == "or") {
                return EvalOr(environment, second);
            }
            if (name == "quote") {
                return EvalQuote(second);
            }
        }

        return EvalFunc(environment, first, second);
    }

    throw RuntimeError{"RuntimeError"};
}
