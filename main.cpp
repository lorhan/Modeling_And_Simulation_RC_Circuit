/*
g++ main.cpp -o main ; ./main.exe

g++ main.cpp -o main
*/

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include "jsonExport.h"

template <typename T>
void printAux(const std::string& myText, const T& myVar){
    std::cout << myText <<": " <<myVar << std::endl;
}

std::vector<double> getPwmSignal(const double Ulow_V,const double Uhigh_V,const double fsw_Hz,const double D_pu, const double Tsim_s, const double Tsimstep_s){
    double Tsw_s = 1/fsw_Hz;
    
    int nrSamples = Tsim_s/Tsimstep_s;
    int idx = 0;
    
    std::vector<double> vecPwmSignal;
    vecPwmSignal.resize(nrSamples);
    
    double Tcumul_s = 0;
    double Ton_s = Tsw_s*D_pu;
    double Toff_s = Tsw_s*(1-D_pu);
    double Tnextsw_s = Tsw_s*D_pu;
    bool nowHigh = true;
    while(Tcumul_s < Tsim_s){
        if(nowHigh){
            vecPwmSignal[idx++] = Uhigh_V;
        } else {
            vecPwmSignal[idx++] = Ulow_V;
        }
        
        Tcumul_s += Tsimstep_s;
        if(Tcumul_s > Tnextsw_s){
            if(nowHigh){
                Tnextsw_s += Toff_s;
            } else {
                Tnextsw_s += Ton_s;
            }
            nowHigh = !nowHigh;
        }
    }
    
    printAux("Tsim_s",Tsim_s);
    printAux("Tsimstep_s",Tsimstep_s);
    printAux("nrSamp",nrSamples);
    printAux("vecPwmLen",vecPwmSignal.size());
    printAux("vecPwm",vecPwmSignal[0]);
    printAux("vecPwm",vecPwmSignal[30]);
    
    return vecPwmSignal;
}

int main() {
    int arrSize = 7;

    double Ulow_V = 10;
    double Uhigh_V = 0;
    double fsw_Hz = 10e3;
    double D_pu = 0.9;
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