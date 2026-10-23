#include "serializer.h"
#include "error.h"

std::string Serialize(const std::shared_ptr<Object> &object) {
    if (object == nullptr) {
        return "()";
    }
    if (auto const number = As<Number>(object); number != nullptr) {
        return std::to_string(number->GetValue());
    }
    if (auto const boolean = As<Boolean>(object); boolean != nullptr) {
        const auto b = boolean->GetValue();
        return b ? "#t" : "#f";
    }
    if (auto const symbol = As<Symbol>(object); symbol != nullptr) {
        return symbol->GetName();
    }
    if (auto cell = As<Cell>(object); cell != nullptr) {
        std::string res = "(";
        while (true) {
            res += Serialize(cell->GetFirst());

            if (cell->GetSecond() == nullptr) {
                break;
            }
            if (auto next = As<Cell>(cell->GetSecond()); next != nullptr) {
                res += " ";
                cell = next;
            } else {
                res += " . " + Serialize(cell->GetSecond());
                break;
            }
        }
        res += ")";

        return res;
    }
    throw RuntimeError{"RuntimeError"};
}
