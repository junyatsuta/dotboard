#include "bdfParser.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iconv.h>


//一度JISをEUC-JPに変換してからUTF-8に変換する
uint32_t jisToUtf8(uint16_t jis, iconv_t conv, uint8_t *length) {

    char input[2] = {0};
    char output[4] = {0};
    char *in_ptr = input;
    char *out_ptr = output;
    size_t in_bytes = sizeof(input);
    size_t out_bytes = sizeof(output);

    if(jis < 127){
        in_bytes = 1;
        input[0] = jis & 0xFF;
    }else if(jis < 256){
        in_bytes = 2;
        input[0] = 0x8E;
        input[1] = jis & 0xFF;
    } else {
        input[0] = ((jis >> 8) & 0xFF) + 0x80;
        input[1] = (jis & 0xFF) + 0x80;
    }

    size_t res = iconv(conv, &in_ptr, &in_bytes, &out_ptr, &out_bytes);

    if (res == (size_t)-1) {
        std::cerr << ("Failed to convert EUC-JP \"" +
                                std::to_string(jis) + "\" to UTF-8") << std::endl;
        std::cout << "JIS value: " << jis << std::endl;
        std::cout << "UTF-8 value: " << res << std::endl;
        std::cout << "Input bytes: ";
        for (size_t i = 0; i < sizeof(input); ++i) {
            std::cout << std::hex << (unsigned int)(unsigned char)input[i] << " ";
        }
        std::cout << std::dec << std::endl;
        std::cout << "Output bytes: ";
        for (size_t i = 0; i < sizeof(output); ++i) {
            std::cout << std::hex << (unsigned int)(unsigned char)output[i] << " ";
        }
        std::cout << std::dec << std::endl; 
        iconv_close(conv);
        exit(EXIT_FAILURE);
    }

    uint32_t utf8 = 0;
    for (int i = 0; i < (int)(sizeof(output) - (int)out_bytes); ++i) {
        utf8 = (utf8 << 8) | (unsigned char)output[i];
    }
    *length = sizeof(output) - out_bytes;

    return utf8;
}

BdfParser::BdfParser() {}
BdfParser::~BdfParser() {
    if(utf8ToGlyph.empty()) {
        return;
    }

    for(auto &c2g : utf8ToGlyph) {
        c2g.second.bitmap.clear();
    }
    utf8ToGlyph.clear();
    return;
}


void BdfParser::parse(const std::string &filename) {
    std::ifstream file(filename);
    if(!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    iconv_t conv = iconv_open("UTF-8", "EUC-JP");
    if(conv == (iconv_t)-1) {
        std::cerr << "Failed to open iconv" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string line;
    while(std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        iss >> token;
        if(token == "STARTCHAR") {
            Glyph glyph;
            std::string character;
            iss >> character;// only read, no use

            uint16_t jis = 0;
            uint32_t utf8 = 0;
            uint8_t length = 0;

            while (std::getline(file, line)) {
                std::istringstream iss(line);
                iss >> token;
                if (token == "ENCODING") {
                    int e = 0;
                    iss >> e;
                    if(e == -1){
                        break;
                    }
                    jis = e;
                    utf8 = jisToUtf8(jis, conv, &length);
                } else if (token == "DWIDTH") {
                    iss >> glyph.dwidth >> glyph.dheight;
                } else if (token == "BBX") {
                    iss >> glyph.bbx_w >> glyph.bbx_h >> glyph.bbx_x >> glyph.bbx_y;
                } else if (token == "BITMAP") {
                    while (std::getline(file, line) && line != "ENDCHAR" && (line.length() == 2 || line.length() == 4)) {
                        glyph.bitmap.push_back(line);
                    }
                    if (glyph.bitmap.size() != BITMAP_HEIGHT || glyph.bbx_h != BITMAP_HEIGHT) {
                        std::cerr << "Bitmap size or BBX height does not match 16 for encoding " << utf8 << std::endl;
                        exit(EXIT_FAILURE);
                    }
                    glyph.encoding = utf8;
                    glyph.length = length;
                    utf8ToGlyph[utf8] = glyph;
                    break;
                }
            }
        }    
    }

    file.close();

    iconv_close(conv);
    return;
}



int main(int argc, char *argv[]){
    if(argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <out>.h <out>.cpp" << " <bdf files> ..." << std::endl;
        return 1;
    }

    BdfParser parser;

    for(int i = 3; i < argc; ++i) {
        parser.parse(argv[i]);
    }

    int num_characters = parser.utf8ToGlyph.size();

    // ---- header ----
    std::ofstream headerFile(argv[1]);
    std::ostringstream h;
    h << "#pragma once\n";
    h << "\n";
    h << "#include <cstdint>\n";
    h << "\n";
    h << "#define NUM_CHARACTER " << num_characters << "\n";
    h << "#define BITMAP_HEIGHT " << BITMAP_HEIGHT << "\n";

    h << "struct Glyph {\n";
    h << "    const char *character;\n";
    h << "    uint32_t encoding;\n";
    h << "    int dwidth, dheight;\n";
    h << "    int bbx_w, bbx_h, bbx_x, bbx_y;\n";
    h << "    uint16_t bitmap[BITMAP_HEIGHT];\n";
    h << "};\n";

    h << "namespace C2Glyph {\n";
    h << "    extern const Glyph glyphs[NUM_CHARACTER];\n";
    h << "}\n";

    headerFile << h.str();
    headerFile.close();

    // ---- source ----
    std::ofstream sourceFile(argv[2]);
    std::ostringstream s;

    s << "#include \"c2glyph.h\"\n";

    s << "namespace C2Glyph {\n";

    s << "constexpr Glyph glyphs[NUM_CHARACTER] = {\n";

    for(auto it = parser.utf8ToGlyph.begin(); it != parser.utf8ToGlyph.end(); ++it) {
        const Glyph &g = it->second;
        char character[5] = {0};

        if(0x00 <= g.encoding && g.encoding < 0x20){
            ;
        }else if(g.encoding == 0x7F){
            ;
        } else if (g.encoding == 0x22) {//"
            character[0] = '\\';
            character[1] = '\"';
        } else if (g.encoding == 0x27) {//'
            character[0] = '\\';
            character[1] = '\'';
        } else if (g.encoding == 0x5C) {// backslash
            character[0] = '\\';
            character[1] = '\\';
        } else {
            for (int i = 0; i < g.length; i++) {
                character[i] = (g.encoding >> (8 * (g.length - 1 - i))) & 0xFF;
            }
        }
        s << "        {\n";
        s << "            \"" << character << "\",\n";
        s << "            " << g.encoding << ",\n";
        s << "            " << g.dwidth << ", " << g.dheight << ",\n";
        s << "            " << g.bbx_w << ", " << g.bbx_h << ", " << g.bbx_x << ", " << g.bbx_y << ",\n";
        s << "            {";
        for(int j = 0; j < BITMAP_HEIGHT; ++j) {
            if (g.bitmap[j].length() == 2){
                s << "0x" <<g.bitmap[j] << "00";
            }else if(g.bitmap[j].length() == 4){
                s << "0x" << g.bitmap[j];
            }else{
                std::cerr << "Unexpected bitmap length: " << g.bitmap[j].length() << std::endl;
                exit(EXIT_FAILURE);
            }
            if(j < BITMAP_HEIGHT - 1) s << ", ";
        }
        s << "}\n";
        s << "        },\n";
    }
    s << "    };\n";
    s << "}\n";

    sourceFile << s.str();
    sourceFile.close();

    return 0;
}