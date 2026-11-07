#include "glyph_utils.h"
#include "c2glyph.h"
#include "utf8.h"
#include <stdexcept>

int GlyphUtils::calcGlyphsWidth(const std::vector<int> &glyphIndices) {
    int width = 0;

    for (int glyphIndex : glyphIndices) {
        width += C2Glyph::glyphs[glyphIndex].bbx_w;
    }
    return width;
}

int GlyphUtils::searchGlyphIndex(uint32_t encoding) {

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

void GlyphUtils::str2encodings(const std::string &str, std::vector<uint32_t> &encodings) {

    encodings.clear();

    std::vector<std::string> strs;
    utf8Str2Strs(str, strs);
    for (const std::string &s : strs) {
        size_t charLen = s.size();
        uint32_t encoding = 0;
        for (size_t i = 0; i < charLen; i++) {
            encoding = (encoding << 8) | static_cast<unsigned char>(s[i]);
        }
        encodings.push_back(encoding);
    }
}
