#include "text2board_converter.h"
#include "c2glyph.h"

#include <iostream>

static size_t utf8_char_len(unsigned char c) {
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
        size_t len = utf8_char_len(static_cast<unsigned char>(str[i]));
        if (len == 0) {
            std::cerr << "Invalid UTF-8 character at position " << i << std::endl;
            exit(EXIT_FAILURE);
        }
        strs.push_back(str.substr(i, len));
        i += len;
    }
    return;
}


void Text2BoardConverter::convert()
{
    if (input_text.empty()) {
        std::cerr << "Input text is empty." << std::endl;
        return;
    }

    if(height <= 0){
        std::cerr << "Invalid board height." << std::endl;
        std::cout << "height = " << height << std::endl;
        return;
    }

    if(height % 16 != 0) {
        std::cerr << "Height must be a multiple of 16." << std::endl;
        std::cout << "height = " << height << std::endl;
        return;
    }
    
    scale = height / 16;

    std::vector<uint32_t> encodings;
    std::vector<int> glyph_indices;

    text2encodings(encodings);
    for (uint32_t encoding : encodings) {
        glyph_indices.push_back(searchGlyphIndex(encoding));
    }

    width = calc_width(glyph_indices);

    dotBoard = new DotBoard(width, height);
    
    int x_offset = 0;
    for(int i = 0; i < (int)glyph_indices.size(); i++) {
        int glyph_index = glyph_indices[i];
        const Glyph &glyph = C2Glyph::glyphs[glyph_index];
        int glyph_width = glyph.bbx_w * scale;
        
        for(int y = 0; y < height; y++) {
            for(int x = 0; x < glyph_width; x++) {
                if (glyph.bitmap[y / scale] & (1 << (16 - 1 - (x / scale)))) { // bitmapは16ビット幅固定左詰め
                    dotBoard->board[y][x_offset + x] = defaultForegroundColor;
                } else {
                    dotBoard->board[y][x_offset + x] = defaultBackgroundColor;
                }
            }
        }
        
        x_offset += glyph_width;
    }

    return;
}


int Text2BoardConverter::calc_width(const std::vector<int> &glyph_indices) {
    int width = 0;

    for (int glyph_index : glyph_indices) {
        width += C2Glyph::glyphs[glyph_index].bbx_w * scale;
    }
    return width;
}

void Text2BoardConverter::text2encodings(std::vector<uint32_t> &encodings) {
    encodings.clear();

    std::vector<std::string> strs;
    str2strs(input_text, strs);
    for (const std::string &s : strs) {
        size_t char_len = s.size();
        uint32_t encoding = 0;
        for (size_t i = 0; i < char_len; i++) {
            encoding = (encoding << 8) | static_cast<unsigned char>(s[i]);
        }
        encodings.push_back(encoding);
    }
    
    return;
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
    std::cerr << "Encoding not found: " << encoding << std::endl;
    exit(EXIT_FAILURE);
    return -1;
}

