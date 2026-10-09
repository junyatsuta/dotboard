#include "input2BoardConverter.h"

Input2BoardConverter::~Input2BoardConverter() {
    if(dotBoard != nullptr){
        delete dotBoard;
        dotBoard = nullptr;
    }
}