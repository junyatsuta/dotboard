#include "color.h"
#include <cassert>
#include <iostream>

int main() {
    std::vector<uint8_t> gray = {128, 128, 128};
    std::vector<uint8_t> red = {255, 0, 0};

    DotColor grayColor = rgb2NearestDotColor(gray);
    assert(grayColor == DotColor::WHITE);
    DotColor redColor = rgb2NearestDotColor(red);
    assert(redColor == DotColor::RED);
    std::cout << "test_rgb2NearestDotColor passed!" << std::endl;
    return 0;
}