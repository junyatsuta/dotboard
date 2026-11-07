//テキストは1行、改行を含まないことを前提とし、UTF-8でエンコードされていることを前提とする

#pragma once

#include "input2board_converter.h"
#include <string>
#include <vector>

class Text2BoardConverter : public Input2BoardConverter{
private:
    std::string inputText = "";
    DotColor defaultBackgroundColor = DotColor::BLACK;
    DotColor defaultForegroundColor = DotColor::WHITE;

public:
    int height = -1;
    int width = -1;
    int scale = -1;

    void setInputText(const std::string &inputText) {
        this->inputText = inputText;
    }

    void setDefaultBackgroundColor(DotColor defaultBackgroundColor) {
        this->defaultBackgroundColor = defaultBackgroundColor;
    }

    void setDefaultForegroundColor(DotColor defaultForegroundColor) {
        this->defaultForegroundColor = defaultForegroundColor;
    }

    void setHeight(int height) {
        this->height = height;
    }

    void convert() override;
};