// 入力のBDFはJISエンコーディングかつ、16ビットの固定heightであることを前提とする

#pragma once

#include <map>
#include <string>
#include <vector>
#include <cstdint>

#define BITMAP_HEIGHT 16

struct Glyph {
    uint32_t encoding;
    int dwidth, dheight;
    int bbx_w, bbx_h, bbx_x, bbx_y;
    std::vector<std::string> bitmap;
    uint8_t length;
};

class BdfParser {
public:
    BdfParser();
    ~BdfParser();
    
    void parse(const std::string &filename);
    std::map<uint32_t, Glyph> utf8ToGlyph = {};
};