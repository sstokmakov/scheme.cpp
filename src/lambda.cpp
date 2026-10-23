#include "lambda.h"

#include "error.h"
#include "eval.h"

Lambda::Lambda(const std::vector<std::string> &params,
               const std::vector<std::shared_ptr<Object>> &body,
               const std::shared_ptr<Environment> &environment)
    : params_(params), body_(body), environment_(environment) {
}

std::shared_ptr<Object> Lambda::Apply(const std::vector<std::shared_ptr<Object>> &args) {
    if (args.size() != params_.size()) {
        throw RuntimeError{"RuntimeError"};
    }
    const auto lambda_env = std::make_shared<Environment>(environment_);
    for (size_t i = 0; i < args.size(); ++i) {
        lambda_env->Define(params_[i], args[i]);
    }
    std::shared_ptr<Object> result;
    for (size_t i = 0; i < body_.size(); ++i) {
        result = Eval(body_[i], lambda_env);
    }
    return result;
}
