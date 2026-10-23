#pragma once

#include "object.h"
#include "tokenizer.h"

#include <memory>

std::shared_ptr<Object> ReadList(Tokenizer*);

std::shared_ptr<Object> ReadValue(Tokenizer*);

std::shared_ptr<Object> Read(Tokenizer* tokenizer);
