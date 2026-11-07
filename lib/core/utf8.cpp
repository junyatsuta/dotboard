#include "utf8.h"
#include <cstddef>
#include <stdexcept>

size_t utf8CharLen(unsigned char c) {
    if (c < 0x80) // 0xxxxxxx
        return 1;
    if ((c & 0xE0) == 0xC0) // 110xxxxx
        return 2;
    if ((c & 0xF0) == 0xE0) // 1110xxxx
        return 3;
    if ((c & 0xF8) == 0xF0) // 11110xxx
        return 4;
    return 0;
}

void utf8Str2Strs(const std::string &str, std::vector<std::string> &strs) {
    strs.clear();
    for (size_t i = 0; i < str.size();) {
        size_t len = utf8CharLen(static_cast<unsigned char>(str[i]));
        if (len == 0) {
            throw std::runtime_error("Invalid UTF-8 character " + std::to_string(i));
        }
        strs.push_back(str.substr(i, len));
        i += len;
    }
    return;
}