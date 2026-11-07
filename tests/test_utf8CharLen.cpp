#include "utf8.h"
#include <cassert>
#include <iostream>

int main() {
    assert(utf8CharLen('a') == 1);
    assert(utf8CharLen(0xC2) == 2);
    assert(utf8CharLen(0xE0) == 3);
    assert(utf8CharLen(0xF0) == 4);
    std::cout << "test_utf8CharLen passed!" << std::endl;
    return 0;
}