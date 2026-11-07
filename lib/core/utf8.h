#pragma once

#include <cstddef>
#include <string>
#include <vector>

size_t utf8CharLen(unsigned char c);

void utf8Str2Strs(const std::string &str, std::vector<std::string> &strs);