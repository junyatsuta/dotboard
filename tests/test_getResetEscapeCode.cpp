#include "color.h"
#include <cassert>
#include <iostream>

int main() {
    assert(getResetEscapeCode() == "\033[0m");
    std::cout << "test_getResetEscapeCode passed!" << std::endl;
    return 0;
}