

#pragma once
#include <vector>

std::vector<double> getPwmSignal(const double Ulow_V,const double Uhigh_V,const double fsw_Hz,const double D_pu, const double Tsim_s, const double Tsimstep_s);


class TransferFunctionRC {
private:
    double C_F;
    double R_ohm;
    double Tsamp_s;
    double k0;
    double k1;
    double k2;

    double Uin1;
    double Uon1;

public:
    // Constructor declaration
    TransferFunctionRC(double aC_F, double aR_ohm, double aTsamp_s);

    // Process a single sample
    double runSample(const double Uin_V);

    // Process a full signal
    std::vector<double> runSignal(const std::vector<double>& inputSignal);
};