#pragma once

#include "object.h"
#include <unordered_map>

class Environment {
public:
    explicit Environment(const std::shared_ptr<Environment>& parent = nullptr);

    void Define(const std::string& name, const std::shared_ptr<Object>& value);

    void Set(const std::string& name, const std::shared_ptr<Object>& value);

    std::shared_ptr<Object> Get(const std::string& name) const;

private:
    std::unordered_map<std::string, std::shared_ptr<Object>> values_;

    std::shared_ptr<Environment> parent_;
};
