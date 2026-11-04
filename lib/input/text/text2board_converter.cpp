#include "text2board_converter.h"
#include "c2glyph.h"

#include <iostream>

static size_t utf8CharLen(unsigned char c) {
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

static void str2strs(const std::string &str, std::vector<std::string> &strs) {
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


void Text2BoardConverter::convert()
{
    if (inputText.empty()) {
        throw std::runtime_error("Input text is empty.");
    }
    if (height <= 0) {
        throw std::runtime_error("Invalid board height:" + std::to_string(height));
    }
    if (height % 16 != 0) {
        throw std::runtime_error("Height must be a multiple of 16:" + std::to_string(height));
    }
    scale = height / 16;

    std::vector<uint32_t> encodings;
    std::vector<int> glyphIndices;

    text2encodings(encodings);
    for (uint32_t encoding : encodings) {
        int index = searchGlyphIndex(encoding);
        glyphIndices.push_back(index);
    }

    width = calcWidth(glyphIndices);

    dotBoard = std::make_unique<DotBoard>(width, height);
    
    int xOffset = 0;
    for(int i = 0; i < (int)glyphIndices.size(); i++) {
        int glyphIndex = glyphIndices[i];
        const Glyph &glyph = C2Glyph::glyphs[glyphIndex];
        int glyphWidth = glyph.bbx_w * scale;
        
        for(int y = 0; y < height; y++) {
            for(int x = 0; x < glyphWidth; x++) {
                if (glyph.bitmap[y / scale] & (1 << (16 - 1 - (x / scale)))) { // bitmapは16ビット幅固定左詰め
                    dotBoard->board[y][xOffset + x] = defaultForegroundColor;
                } else {
                    dotBoard->board[y][xOffset + x] = defaultBackgroundColor;
                }
            }
        }
        xOffset += glyphWidth;
    }

    return;
}


int Text2BoardConverter::calcWidth(const std::vector<int> &glyphIndices) {
    int width = 0;

    for (int glyphIndex : glyphIndices) {
        width += C2Glyph::glyphs[glyphIndex].bbx_w * scale;
    }
    return width;
}

void Text2BoardConverter::text2encodings(std::vector<uint32_t> &encodings) {

    encodings.clear();

    std::vector<std::string> strs;
    str2strs(inputText, strs);
    for (const std::string &s : strs) {
        size_t charLen = s.size();
        uint32_t encoding = 0;
        for (size_t i = 0; i < charLen; i++) {
            encoding = (encoding << 8) | static_cast<unsigned char>(s[i]);
        }
        encodings.push_back(encoding);
    }
}

int Text2BoardConverter::searchGlyphIndex(uint32_t encoding) {

    int left = 0;
    int right = NUM_CHARACTER - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (C2Glyph::glyphs[mid].encoding == encoding) {
            return mid;
        } else if (C2Glyph::glyphs[mid].encoding < encoding) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    throw std::runtime_error("Encoding not found: " + std::to_string(encoding));
}

