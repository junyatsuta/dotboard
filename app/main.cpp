#include "dotboard.h"
#include "output_shell.h"
#include "text2board_converter.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_text>" << std::endl;
        return 1;
    }
    
    std::string input_text = argv[1];
    Text2BoardConverter converter;
    converter.setInputText(input_text);
    converter.setHeight(16);
    converter.setDefaultBackgroundColor(DotColor::WHITE);
    converter.setDefaultForegroundColor(DotColor::BLACK);
    converter.convert();
    
    DotBoard *board = converter.dotBoard;

    OutputShell output_shell(board);
    output_shell.display();

    return 0;
}