#include "output_shell.h"
#include <iostream>

OutputShell::OutputShell(DotBoard *db) {
    dotBoard = db;
}

OutputShell::~OutputShell() {
    dotBoard = nullptr;
}

void OutputShell::display() {
    if (dotBoard == nullptr) {
        return;
    }

    for(int y = 0; y < dotBoard->height/2; y++) {
        int y2 = y * 2;
        for(int x = 0; x < dotBoard->width; x++) {
            std::string topColor = getForegroundEscapeCode(dotBoard->board[y2][x]);
            std::string bottomColor = getBackgroundEscapeCode(dotBoard->board[y2 + 1][x]);
            std::string outColor = topColor + bottomColor + "▀" + getResetEscapeCode();
            std::cout << outColor;
        }
        std::cout << std::endl;
    }
}

