#pragma once

#include "io_type.h"
#include "dotboard.h"

class Input2BoardConverter{
public:

    InputType inputType;
    DotBoard *dotBoard = nullptr;

    virtual void convert() = 0;
    
    ~Input2BoardConverter();
};
