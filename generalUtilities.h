#pragma once
#include <string>
#include <iostream>

template <typename T>
void printAux(const std::string& myText, const T& myVar){
    std::cout << myText <<": " <<myVar << std::endl;
}
