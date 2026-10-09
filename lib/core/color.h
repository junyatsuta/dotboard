#pragma once

#include <cstdint>
#include <vector>
#include <string>

#define NUM_DOT_COLORS 9

enum class DotColor { NONE, BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE };

std::vector<uint8_t> dotColor2rgb(DotColor dotColor);

DotColor rgb2NearestDotColor(const std::vector<uint8_t> &rgb);

std::string getForegroundEscapeCode(DotColor dotColor);
std::string getBackgroundEscapeCode(DotColor dotColor);
std::string getResetEscapeCode();