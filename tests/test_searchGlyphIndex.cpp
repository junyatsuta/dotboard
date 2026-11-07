#include "glyph_utils.h"
#include "c2glyph.h"
#include <iostream>
#include <cassert>
#include <string>

int main(){
    std::string str = "や 蔦　j（(";
    std::vector<uint32_t> encodings;
    GlyphUtils::str2encodings(str, encodings);
    std::vector<int> glyph_indices;
    for(size_t i=0; i<encodings.size(); i++){
        glyph_indices.push_back(GlyphUtils::searchGlyphIndex(encodings[i]));
    }

    assert(std::string(C2Glyph::glyphs[glyph_indices[0]].character) == "や");
    assert(std::string(C2Glyph::glyphs[glyph_indices[1]].character) == " ");
    assert(std::string(C2Glyph::glyphs[glyph_indices[2]].character) == "蔦");
    assert(std::string(C2Glyph::glyphs[glyph_indices[3]].character) == "　");
    assert(std::string(C2Glyph::glyphs[glyph_indices[4]].character) == "j");
    assert(std::string(C2Glyph::glyphs[glyph_indices[5]].character) == "（");
    assert(std::string(C2Glyph::glyphs[glyph_indices[6]].character) == "(");

    bool caught = false;
    try{
        GlyphUtils::searchGlyphIndex(0); // invalid index
    }catch(...){
        caught = true;
    }
    assert(caught);
    bool caught2 = false;
    try{
        GlyphUtils::searchGlyphIndex(99999999); // invalid index
    }catch(...){
        caught2 = true;
    }
    assert(caught2);

    std::cout << "test_searchGlyphIndex passed!" << std::endl;
    return 0;
}