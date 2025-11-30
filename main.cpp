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





class TransferFunctionRC{
    private:
    double C_F = 0;
    double R_ohm = 0;
    double Tsamp_s = 0;
    double k0 = 0;
    double k1 = 0;
    double k2 = 0;

    double Uin1 = 0;
    double Uon1 = 0;


    public:
    TransferFunctionRC(double aC_F, double aR_ohm, double aTsamp_s){
        C_F = aC_F;
        R_ohm = aR_ohm;
        Tsamp_s = aTsamp_s;

        double w0 = 1/(R_ohm*C_F);
        double b0 = w0*Tsamp_s;
        double b1 = b0;
        double a0 = (2+b0);
        double a1 = (b0-2);


        k0 = b0/a0;
        k1 = b1/a0;
        k2 = a1/a0;

    }

    double runSample(const double Uin_V){
        double Uo_V = k0*Uin_V + k1*Uin1 - k2*Uon1;
        Uin1 = Uin_V;
        Uon1 = Uo_V;
        return Uo_V;
    }


};



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