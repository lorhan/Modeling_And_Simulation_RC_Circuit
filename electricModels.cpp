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
