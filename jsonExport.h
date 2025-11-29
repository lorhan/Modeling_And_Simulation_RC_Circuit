#pragma once
#include <vector>
#include <string>
#include <fstream>

template <typename T>
std::string getStringFromVector(const std::vector<T>& myVec){
    std::string vecAsString = "[";
    for(size_t i = 0; i < myVec.size(); i++){
        if(i > 0){
            vecAsString += "," + std::to_string(myVec[i]);
        } else {
            vecAsString += std::to_string(myVec[i]);
        }
    }
    vecAsString += "]";
    return vecAsString;
}

template <typename T>
void exportJson(const std::vector<T>& myVec1, const std::vector<T>& myVec2){
    std::string strFileContent;
    strFileContent += "{\n";
    strFileContent += "\t\"array1\":" + getStringFromVector(myVec1) + ",\n";
    strFileContent += "\t\"array2\":" + getStringFromVector(myVec2);
    strFileContent += "\n}";

    std::ofstream out("output.json");
    out << strFileContent;
}
