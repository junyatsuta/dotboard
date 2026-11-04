#pragma once

#include "dotboard.h"
#include "io_type.h"
#include <memory>

class Input2BoardConverter{
public:

    InputType inputType;
    std::unique_ptr<DotBoard> dotBoard = nullptr;

    virtual void convert() = 0;
};
