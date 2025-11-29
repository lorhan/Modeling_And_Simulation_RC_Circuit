

#pragma once
#include <vector>

std::vector<double> getPwmSignal(const double Ulow_V,const double Uhigh_V,const double fsw_Hz,const double D_pu, const double Tsim_s, const double Tsimstep_s);
