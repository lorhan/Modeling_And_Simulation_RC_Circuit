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
#include "generalUtilities.h"







int main() {

    // RC characteristics
    double C_F = 33e-6;
    double R_ohm = 10;

    // PWM characteristics
    double Ulow_V = 0;
    double Uhigh_V = 10;
    double fsw_Hz = 10e3;
    double D_pu = 0.75;
    
    
    // Simulation time characteristics
    double Tsim_s = 5e-3;
    double Tsimstep_s = 1/(200*fsw_Hz); 



    std::vector<double> pwmSignal = getPwmSignal(Ulow_V, Uhigh_V, fsw_Hz, D_pu, Tsim_s, Tsimstep_s);



    long nrSamples = pwmSignal.size();
    std::vector<double> outputSamples;
    outputSamples.resize(nrSamples);

    TransferFunctionRC tfRC(C_F, R_ohm, Tsimstep_s);
    for(long i=0; i<nrSamples; i++){
        outputSamples[i] = tfRC.runSample(pwmSignal[i]);
    }


    exportJson(pwmSignal, outputSamples);


    std::cout << "Array written to output.txt\n";
    return 0;
}