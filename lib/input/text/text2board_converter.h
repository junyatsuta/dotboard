//テキストは1行、改行を含まないことを前提とし、UTF-8でエンコードされていることを前提とする

#pragma once

#include "input2BoardConverter.h"
#include <string>
#include <vector>

class Text2BoardConverter : public Input2BoardConverter{
private:
    std::string input_text = "";
    DotColor defaultBackgroundColor = DotColor::BLACK;
    DotColor defaultForegroundColor = DotColor::WHITE;

public:
    int height = -1;
    int width = -1;
    int scale = -1;

    void setInputText(const std::string &input_text) {
        this->input_text = input_text;
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

private:
    int calc_width(const std::vector<int> &glyph_indices);
    void text2encodings(std::vector<uint32_t> & encodings);
    int searchGlyphIndex(uint32_t encoding);
};