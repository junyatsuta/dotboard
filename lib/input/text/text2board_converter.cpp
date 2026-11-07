#include "text2board_converter.h"
#include "c2glyph.h"
#include "utf8.h"
#include "glyph_utils.h"
#include <iostream>

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

    GlyphUtils::str2encodings(inputText, encodings);
    for (uint32_t encoding : encodings) {
        int index = GlyphUtils::searchGlyphIndex(encoding);
        glyphIndices.push_back(index);
    }

    width = scale * GlyphUtils::calcGlyphsWidth(glyphIndices);

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