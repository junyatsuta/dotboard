#include "glyph_utils.h"
#include "c2glyph.h"
#include <vector>
#include <string>
#include <cassert>
#include <iostream>

int main(){
    std::string str = "や 蔦　j（(";
    std::vector<uint32_t> encodings;
    GlyphUtils::str2encodings(str, encodings);
    std::vector<int> glyph_indices;
    for (size_t i = 0; i < encodings.size(); i++) {
        glyph_indices.push_back(GlyphUtils::searchGlyphIndex(encodings[i]));
    }
    int total_width = 8 * (2 + 1 + 2 + 2 + 1 + 2 + 1);
    assert(GlyphUtils::calcGlyphsWidth(glyph_indices) == total_width);
    std::cout << "test_calcGlyphsWidth passed!" << std::endl;
    return 0;
}