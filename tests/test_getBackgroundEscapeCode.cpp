#include "color.h"
#include <cassert>
#include <iostream>

int main() {
    assert(getBackgroundEscapeCode(DotColor::RED) == "\033[41m");
    assert(getBackgroundEscapeCode(DotColor::WHITE) == "\033[48;2;255;255;255m");
    std::cout << "test_getBackgroundEscapeCode passed!" << std::endl;
    return 0;
}