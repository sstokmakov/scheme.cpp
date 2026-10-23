#pragma once

#include <memory>
#include <string>
#include <vector>

class Object : public std::enable_shared_from_this<Object> {
public:
    virtual ~Object() = default;
};

class Number : public Object {
public:
    explicit Number(const int value) : value_(value) {
    }

    int GetValue() const {
        return value_;
    }

private:
    int value_;
};

class Symbol : public Object {
public:
    explicit Symbol(const std::string& name) : name_(name) {
    }

    const std::string& GetName() const {
        return name_;
    }

private:
    std::string name_;
};

class Cell : public Object {
public:
    Cell(const std::shared_ptr<Object>& first, const std::shared_ptr<Object>& second)
        : first_(first), second_(second) {
    }

    std::shared_ptr<Object> GetFirst() const {
        return first_;
    }

    std::shared_ptr<Object> GetSecond() const {
        return second_;
    }

    void SetFirst(const std::shared_ptr<Object>& first) {
        first_ = first;
    }

    void SetSecond(const std::shared_ptr<Object>& second) {
        second_ = second;
    }

private:
    std::shared_ptr<Object> first_, second_;
};

class Boolean : public Object {
public:
    explicit Boolean(const bool value) : value_(value) {
    }

    bool GetValue() const {
        return value_;
    }

private:
    bool value_;
};

class Function : public Object {
public:
    virtual std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>>& args) = 0;
};


template <class T>
std::shared_ptr<T> As(const std::shared_ptr<Object>& obj) {
    return std::dynamic_pointer_cast<T>(obj);
}

template <class T>
bool Is(const std::shared_ptr<Object>& obj) {
    return As<T>(obj) != nullptr;
}
