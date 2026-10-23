#pragma once

#include "environment.h"
#include "object.h"

class Lambda : public Function {
public:
    Lambda(const std::vector<std::string>& params, const std::vector<std::shared_ptr<Object>>& body,
           const std::shared_ptr<Environment>& environment);

    std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>>& args) override;

private:
    std::vector<std::string> params_;
    std::vector<std::shared_ptr<Object>> body_;
    std::shared_ptr<Environment> environment_;
};
