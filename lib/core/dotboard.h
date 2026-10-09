#pragma once

#include "color.h"
#include <vector>

class DotBoard{
    
public:

    DotBoard(int w, int h) : width(w), height(h), board(h, std::vector<DotColor>(w, DotColor::NONE)) {}
    ~DotBoard(){
        width = 0;
        height = 0;
        board.clear();
    }

    int width;
    int height;

    std::vector<std::vector<DotColor>> board;
};



