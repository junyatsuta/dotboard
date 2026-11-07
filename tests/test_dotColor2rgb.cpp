#include "color.h"
#include <cassert>
#include <iostream>

int main(){
    std::vector<uint8_t> r = dotColor2rgb(DotColor::RED);
    assert(r.size() == 3);
    assert(r[0] == 255);
    assert(r[1] == 0);
    assert(r[2] == 0);
    std::cout << "test_dotColor2rgb passed!" << std::endl;
}