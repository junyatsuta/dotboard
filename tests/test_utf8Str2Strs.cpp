#include "utf8.h"
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::string utf8Str = u8"や 蔦　j（(";
    std::vector<std::string> strs;
    utf8Str2Strs(utf8Str, strs);
    assert(!strs.empty());
    assert(strs.size() == 7);
    assert(strs[0] == u8"や");
    assert(strs[1] == u8" ");
    assert(strs[2] == u8"蔦");
    assert(strs[3] == u8"　");
    assert(strs[4] == u8"j");
    assert(strs[5] == u8"（");
    assert(strs[6] == u8"(");
    std::cout << "test_utf8Str2Strs passed!" << std::endl;
    return 0;
}