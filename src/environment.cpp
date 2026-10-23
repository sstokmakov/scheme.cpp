#include "environment.h"
#include "error.h"

Environment::Environment(const std::shared_ptr<Environment>& parent) : parent_(parent) {
}

void Environment::Define(const std::string& name, const std::shared_ptr<Object>& value) {
    values_[name] = value;
}

void Environment::Set(const std::string& name, const std::shared_ptr<Object>& value) {
    if (const auto it = values_.find(name); it != values_.end()) {
        it->second = value;
        return;
    }
    if (parent_) {
        parent_->Set(name, value);
        return;
    }
    throw NameError{name};
}

std::shared_ptr<Object> Environment::Get(const std::string& name) const {
    if (const auto it = values_.find(name); it != values_.end()) {
        return it->second;
    }
    if (parent_) {
        return parent_->Get(name);
    }
    throw NameError{name};
}
