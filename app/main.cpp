#include "dotboard.h"
#include "output_shell.h"
#include "text2board_converter.h"
#include <iostream>
#include <string>
#include <memory>

int main(int argc, char *argv[])
{

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_text>" << std::endl;
        return 1;
    }
    
    std::string input_text = argv[1];
    std::unique_ptr<Text2BoardConverter> converter = std::make_unique<Text2BoardConverter>();
    converter->setInputText(input_text);
    converter->setHeight(16);
    converter->setDefaultBackgroundColor(DotColor::WHITE);
    converter->setDefaultForegroundColor(DotColor::BLACK);

    try{
        converter->convert();
    } catch (const std::exception &e){
        std::cerr << e.what() << std::endl;
        return 1;
    }

    DotBoard *board = converter->dotBoard.get();

    OutputShell outputShell(board);
    outputShell.display();

    return 0;
}