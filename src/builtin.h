#pragma once

#include "object.h"

class Add : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>>& args) override;
};

class Multiplication : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>>& args) override;
};

class Subtraction : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>>& args) override;
};

class Division : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>>& args) override;
};

class Equal : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>>& args) override;
};

class Greater : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>>& args) override;
};

class Less : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>>& args) override;
};

class GreaterOrEqual : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>>& args) override;
};

class LessOrEqual : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>>& args) override;
};

class Min : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>>& args) override;
};

class Max : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>>& args) override;
};

class Abs : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>>& args) override;
};

class IsNumber : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>>& args) override;
};

class IsBoolean : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>>& args) override;
};

class IsSymbol : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>>& args) override;
};

class Not : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>>& args) override;
};

class IsPair : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>>& args) override;
};

class IsNull : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>>& args) override;
};

class Cons : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>>& args) override;
};

class Car : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>>& args) override;
};

class Cdr : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>>& args) override;
};

class IsList : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>>& args) override;
};

class List : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>>& args) override;
};

class ListRef : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>>& args) override;
};

class ListTail : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>>& args) override;
};

class SetCar : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>>& args) override;
};

class SetCdr : public Function {
public:
    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>>& args) override;
};
