#pragma once

#include "environment.h"

#include <string>

class Scheme {
public:
    Scheme();

    std::string Evaluate(const std::string& expression);

private:
    std::shared_ptr<Environment> environment_ = std::make_shared<Environment>();
};
