#include "builtin.h"
#include "error.h"

namespace {
int RequireNumber(const std::shared_ptr<Object>& obj) {
    if (const auto number = As<Number>(obj)) {
        return number->GetValue();
    }
    throw RuntimeError{"RuntimeError"};
}

std::shared_ptr<Cell> RequireCell(const std::shared_ptr<Object>& obj) {
    if (const auto cell = As<Cell>(obj)) {
        return cell;
    }
    throw RuntimeError{"RuntimeError"};
}

bool IsNumbers(const std::vector<std::shared_ptr<Object>>& args) {
    for (const auto& arg : args) {
        if (!Is<Number>(arg)) {
            return false;
        }
    }
    return true;
}

template <class Compare>
std::shared_ptr<Object> CompareNumbers(const std::vector<std::shared_ptr<Object>>& nums,
                                       Compare compare) {
    if (!IsNumbers(nums)) {
        throw RuntimeError{"RuntimeError"};
    }
    for (size_t i = 1; i < nums.size(); ++i) {
        if (!compare(RequireNumber(nums[i - 1]), RequireNumber(nums[i]))) {
            return std::make_shared<Boolean>(false);
        }
    }
    return std::make_shared<Boolean>(true);
}

}  // namespace

std::shared_ptr<Object> Add::Apply(const std::vector<std::shared_ptr<Object>>& args) {
    int res = 0;
    for (const auto& arg : args) {
        res += RequireNumber(arg);
    }
    return std::make_shared<Number>(res);
}

std::shared_ptr<Object> Multiplication::Apply(const std::vector<std::shared_ptr<Object>>& args) {
    int res = 1;
    for (const auto& arg : args) {
        res *= RequireNumber(arg);
    }
    return std::make_shared<Number>(res);
}

std::shared_ptr<Object> Subtraction::Apply(const std::vector<std::shared_ptr<Object>>& args) {
    if (args.empty()) {
        throw RuntimeError{"RuntimeError"};
    }
    int res = RequireNumber(args[0]);
    for (size_t i = 1; i < args.size(); ++i) {
        res -= RequireNumber(args[i]);
    }
    return std::make_shared<Number>(res);
}

std::shared_ptr<Object> Division::Apply(const std::vector<std::shared_ptr<Object>>& args) {
    if (args.empty()) {
        throw RuntimeError{"RuntimeError"};
    }
    int res = RequireNumber(args[0]);
    for (size_t i = 1; i < args.size(); ++i) {
        const int value = RequireNumber(args[i]);
        if (value == 0) {
            throw RuntimeError{"RuntimeError"};
        }
        res /= value;
    }
    return std::make_shared<Number>(res);
}

std::shared_ptr<Object> Equal::Apply(const std::vector<std::shared_ptr<Object>>& args) {
    return CompareNumbers(args, [](const int left, const int right) { return left == right; });
}

std::shared_ptr<Object> Greater::Apply(const std::vector<std::shared_ptr<Object>>& args) {
    return CompareNumbers(args, [](const int left, const int right) { return left > right; });
}

std::shared_ptr<Object> Less::Apply(const std::vector<std::shared_ptr<Object>>& args) {
    return CompareNumbers(args, [](const int left, const int right) { return left < right; });
}

std::shared_ptr<Object> GreaterOrEqual::Apply(const std::vector<std::shared_ptr<Object>>& args) {
    return CompareNumbers(args, [](const int left, const int right) { return left >= right; });
}

std::shared_ptr<Object> LessOrEqual::Apply(const std::vector<std::shared_ptr<Object>>& args) {
    return CompareNumbers(args, [](const int left, const int right) { return left <= right; });
}

std::shared_ptr<Object> Min::Apply(const std::vector<std::shared_ptr<Object>>& args) {
    if (args.empty()) {
        throw RuntimeError{"RuntimeError"};
    }
    int min = RequireNumber(args[0]);
    for (size_t i = 1; i < args.size(); ++i) {
        min = std::min(min, RequireNumber(args[i]));
    }
    return std::make_shared<Number>(min);
}

std::shared_ptr<Object> Max::Apply(const std::vector<std::shared_ptr<Object>>& args) {
    if (args.empty()) {
        throw RuntimeError{"RuntimeError"};
    }
    int max = RequireNumber(args[0]);
    for (size_t i = 1; i < args.size(); ++i) {
        max = std::max(max, RequireNumber(args[i]));
    }
    return std::make_shared<Number>(max);
}

std::shared_ptr<Object> Abs::Apply(const std::vector<std::shared_ptr<Object>>& args) {
    if (args.size() != 1) {
        throw RuntimeError{"RuntimeError"};
    }
    return std::make_shared<Number>(std::abs(RequireNumber(args[0])));
}

std::shared_ptr<Object> IsNumber::Apply(const std::vector<std::shared_ptr<Object>>& args) {
    if (args.size() != 1) {
        throw RuntimeError{"RuntimeError"};
    }
    return std::make_shared<Boolean>(Is<Number>(args[0]));
}

std::shared_ptr<Object> IsBoolean::Apply(const std::vector<std::shared_ptr<Object>>& args) {
    if (args.size() != 1) {
        throw RuntimeError{"RuntimeError"};
    }
    return std::make_shared<Boolean>(Is<Boolean>(args[0]));
}

std::shared_ptr<Object> IsSymbol::Apply(const std::vector<std::shared_ptr<Object>>& args) {
    if (args.size() != 1) {
        throw RuntimeError{"RuntimeError"};
    }
    return std::make_shared<Boolean>(Is<Symbol>(args[0]));
}

std::shared_ptr<Object> Not::Apply(const std::vector<std::shared_ptr<Object>>& args) {
    if (args.size() != 1) {
        throw RuntimeError{"RuntimeError"};
    }
    if (const auto arg = As<Boolean>(args[0]); arg != nullptr) {
        return std::make_shared<Boolean>(!arg->GetValue());
    }
    return std::make_shared<Boolean>(false);
}

std::shared_ptr<Object> IsPair::Apply(const std::vector<std::shared_ptr<Object>>& args) {
    if (args.size() != 1) {
        throw RuntimeError{"RuntimeError"};
    }
    return std::make_shared<Boolean>(Is<Cell>(args[0]));
}

std::shared_ptr<Object> IsNull::Apply(const std::vector<std::shared_ptr<Object>>& args) {
    if (args.size() != 1) {
        throw RuntimeError{"RuntimeError"};
    }
    return std::make_shared<Boolean>(args[0] == nullptr);
}

std::shared_ptr<Object> Cons::Apply(const std::vector<std::shared_ptr<Object>>& args) {
    if (args.size() != 2) {
        throw RuntimeError{"RuntimeError"};
    }
    return std::make_shared<Cell>(args[0], args[1]);
}

std::shared_ptr<Object> Car::Apply(const std::vector<std::shared_ptr<Object>>& args) {
    if (args.size() != 1) {
        throw RuntimeError{"RuntimeError"};
    }
    if (const auto cell = As<Cell>(args[0]); cell != nullptr) {
        return cell->GetFirst();
    }
    throw RuntimeError{"RuntimeError"};
}

std::shared_ptr<Object> Cdr::Apply(const std::vector<std::shared_ptr<Object>>& args) {
    if (args.size() != 1) {
        throw RuntimeError{"RuntimeError"};
    }
    if (const auto cell = As<Cell>(args[0]); cell != nullptr) {
        return cell->GetSecond();
    }
    throw RuntimeError{"RuntimeError"};
}

std::shared_ptr<Object> IsList::Apply(const std::vector<std::shared_ptr<Object>>& args) {
    if (args.size() != 1) {
        throw RuntimeError{"RuntimeError"};
    }
    if (args[0] == nullptr) {
        return std::make_shared<Boolean>(true);
    }
    if (auto cell = As<Cell>(args[0]); cell != nullptr) {
        while (Is<Cell>(cell->GetSecond())) {
            cell = As<Cell>(cell->GetSecond());
        }
        return std::make_shared<Boolean>(cell->GetSecond() == nullptr);
    }
    return std::make_shared<Boolean>(false);
}

std::shared_ptr<Object> List::Apply(const std::vector<std::shared_ptr<Object>>& args) {
    std::shared_ptr<Object> res = nullptr;
    for (auto it = args.rbegin(); it != args.rend(); ++it) {
        const auto curr = std::make_shared<Cell>(*it, res);
        res = curr;
    }
    return res;
}

std::shared_ptr<Object> ListRef::Apply(const std::vector<std::shared_ptr<Object>>& args) {
    if (args.size() != 2) {
        throw RuntimeError{"Incorrect size"};
    }

    auto curr = RequireCell(args[0]);
    const int idx = RequireNumber(args[1]);

    if (idx < 0) {
        throw RuntimeError{"RuntimeError"};
    }

    for (int i = 0; i < idx; ++i) {
        curr = RequireCell(curr->GetSecond());
    }
    return curr->GetFirst();
}

std::shared_ptr<Object> ListTail::Apply(const std::vector<std::shared_ptr<Object>>& args) {
    if (args.size() != 2) {
        throw RuntimeError{"Incorrect size"};
    }

    auto curr = args[0];
    const int idx = RequireNumber(args[1]);

    if (idx < 0) {
        throw RuntimeError{"RuntimeError"};
    }

    for (int i = 0; i < idx; ++i) {
        curr = RequireCell(curr)->GetSecond();
    }

    return curr;
}

std::shared_ptr<Object> SetCar::Apply(const std::vector<std::shared_ptr<Object>>& args) {
    if (args.size() != 2) {
        throw RuntimeError{"RuntimeError"};
    }
    if (!Is<Cell>(args[0])) {
        throw RuntimeError{"RuntimeError"};
    }

    As<Cell>(args[0])->SetFirst(args[1]);
    return nullptr;
}

std::shared_ptr<Object> SetCdr::Apply(const std::vector<std::shared_ptr<Object>>& args) {
    if (args.size() != 2) {
        throw RuntimeError{"RuntimeError"};
    }
    if (!Is<Cell>(args[0])) {
        throw RuntimeError{"RuntimeError"};
    }

    As<Cell>(args[0])->SetSecond(args[1]);
    return nullptr;
}
