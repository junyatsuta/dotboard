// "▀" を用いて、上下2ピクセルを1文字で表現するシェル出力クラス

#pragma once

#include "dotboard.h"

class OutputShell {
public:
    OutputShell(DotBoard *db);
    ~OutputShell();

    DotBoard *dotBoard = nullptr;

    void display();
};