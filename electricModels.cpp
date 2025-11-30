#include "electricModels.h"

std::vector<double> getPwmSignal(const double Ulow_V,const double Uhigh_V,const double fsw_Hz,const double D_pu, const double Tsim_s, const double Tsimstep_s){
    double Tsw_s = 1/fsw_Hz;
    
    int nrSamples = Tsim_s/Tsimstep_s;
    int idx = 0;
    
    std::vector<double> vecPwmSignal;
    vecPwmSignal.resize(nrSamples);
    
    double Tcumul_s = 0;
    double Ton_s = Tsw_s*D_pu;
    double Toff_s = Tsw_s-Ton_s;
    double Tnextsw_s = Ton_s;
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
    
    return vecPwmSignal;
}



TransferFunctionRC::TransferFunctionRC(double aC_F, double aR_ohm, double aTsamp_s)
{
    C_F = aC_F;
    R_ohm = aR_ohm;
    Tsamp_s = aTsamp_s;
    Uin1 = 0.0;
    Uon1 = 0.0;


    double w0 = 1.0 / (R_ohm * C_F);
    double b0 = w0 * Tsamp_s;
    double b1 = b0;
    double a0 = (2.0 + b0);
    double a1 = (b0 - 2.0);

    k0 = b0/a0;
    k1 = b1/a0;
    k2 = a1/a0;
}

double TransferFunctionRC::runSample(const double Uin_V) {
    double Uo_V = k0 * Uin_V + k1 * Uin1 - k2 * Uon1;
    Uin1 = Uin_V;
    Uon1 = Uo_V;
    return Uo_V;
}

std::vector<double> TransferFunctionRC::runSignal(const std::vector<double>& inputSignal) {
    long nrSamples = inputSignal.size();
    std::vector<double> outputSamples(nrSamples);

    for (long i = 0; i < nrSamples; i++) {
        outputSamples[i] = runSample(inputSignal[i]);
    }
    return outputSamples;
}