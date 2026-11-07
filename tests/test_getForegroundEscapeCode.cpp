#include "color.h"
#include <cassert>
#include <iostream>

int main() {
    assert(getForegroundEscapeCode(DotColor::RED) == "\033[31m");
    assert(getForegroundEscapeCode(DotColor::WHITE) == "\033[38;2;255;255;255m");
    std::cout << "test_getForegroundEscapeCode passed!" << std::endl;
    return 0;
}