#pragma once

#include "environment.h"
#include "object.h"

std::shared_ptr<Object> Eval(std::shared_ptr<Object> object, const std::shared_ptr<Environment> &environment);
