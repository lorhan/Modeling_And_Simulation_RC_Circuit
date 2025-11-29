/*
g++ main.cpp -o main
g++ main.cpp -o main ; ./main.exe
g++ main.cpp -o main ; ./main.exe ; python pyView.py
g++ main.cpp electricModels.cpp -o main ; ./main.exe ; python pyView.py

*/

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include "jsonExport.h"
#include "electricModels.h"

template <typename T>
void printAux(const std::string& myText, const T& myVar){
    std::cout << myText <<": " <<myVar << std::endl;
}



int main() {
    int arrSize = 7;

    double Ulow_V = 0;
    double Uhigh_V = 10;
    double fsw_Hz = 10e3;
    double D_pu = 0.75;
    double Tsim_s = 10e-3;
    double Tsimstep_s = 1/(200*fsw_Hz); 
    std::vector<double> pwmSignal = getPwmSignal(Ulow_V, Uhigh_V, fsw_Hz, D_pu, Tsim_s, Tsimstep_s);

    std::vector<double> myVec(arrSize);

    for (int i = 0; i < arrSize; i++) {
        myVec[i] = i * 11.2;
    }

    exportJson(myVec, pwmSignal);


    std::cout << "Array written to output.txt\n";
    return 0;
}