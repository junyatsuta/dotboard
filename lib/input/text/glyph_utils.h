#pragma once

#include <cstdint>
#include <vector>
#include <string>

namespace GlyphUtils {

    int searchGlyphIndex(uint32_t encoding);
    int calcGlyphsWidth(const std::vector<int> &glyph_indices);
    void str2encodings(const std::string &str, std::vector<uint32_t> &encodings);
}