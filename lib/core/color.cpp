#include "color.h"

std::vector<uint8_t> dotColor2rgb(DotColor dotColor) {
    std::vector<uint8_t> rgb;

    switch (dotColor) {
    case DotColor::BLACK:
        rgb = {0, 0, 0};
        break;
    case DotColor::BLUE:
        rgb = {0, 0, 255};
        break;
    case DotColor::RED:
        rgb = {255, 0, 0};
        break;
    case DotColor::GREEN:
        rgb = {0, 255, 0};
        break;
    case DotColor::YELLOW:
        rgb = {255, 255, 0};
        break;
    case DotColor::MAGENTA:
        rgb = {255, 0, 255};
        break;
    case DotColor::CYAN:
        rgb = {0, 255, 255};
        break;
    case DotColor::WHITE:
        rgb = {255, 255, 255};
        break;
    default:
        rgb = {0, 0, 0};
        break;
    }

    return rgb;
}

DotColor nearestDotColor(const std::vector<uint8_t> &rgb)
{
    DotColor nearestColor = DotColor::BLACK;
    int minDistance = 256 * 256 * 3; // Maximum possible distance squared

    for (int i = 0; i < NUM_DOT_COLORS; ++i) {
        DotColor color = static_cast<DotColor>(i);
        std::vector<uint8_t> colorRgb = dotColor2rgb(color);
        int distance = 0;
        for (int j = 0; j < 3; ++j) {
            int diff = static_cast<int>(rgb[j]) - static_cast<int>(colorRgb[j]);
            distance += diff * diff;
        }
        if (distance < minDistance) {
            minDistance = distance;
            nearestColor = color;
        }
    }

    return nearestColor;
}

std::string getForegroundEscapeCode(DotColor dotColor) {
    switch (dotColor) {
    case DotColor::BLACK:
        return "\033[30m";
    case DotColor::RED:
        return "\033[31m";
    case DotColor::GREEN:
        return "\033[32m";
    case DotColor::YELLOW:
        return "\033[33m";
    case DotColor::BLUE:
        return "\033[34m";
    case DotColor::MAGENTA:
        return "\033[35m";
    case DotColor::CYAN:
        return "\033[36m";
    case DotColor::WHITE:
        return "\033[38;2;255;255;255m";
    default:
        return "\033[30m";
    }
}

std::string getBackgroundEscapeCode(DotColor dotColor) {
    switch (dotColor) {
    case DotColor::BLACK:
        return "\033[40m";
    case DotColor::RED:
        return "\033[41m";
    case DotColor::GREEN:
        return "\033[42m";
    case DotColor::YELLOW:
        return "\033[43m";
    case DotColor::BLUE:
        return "\033[44m";
    case DotColor::MAGENTA:
        return "\033[45m";
    case DotColor::CYAN:
        return "\033[46m";
    case DotColor::WHITE:
        return "\033[48;2;255;255;255m";
    default:
        return "\033[40m";
    }
}

std::string getResetEscapeCode() {
    return "\033[0m";
}