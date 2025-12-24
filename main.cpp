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
// #include "jsonExport.h"
#include "electricModels.h"
#include "generalUtilities.h"


class SignalExporter{
    private:
    std::vector<std::string> names;
    std::vector<std::vector<double>*> values;
    
    public:
    
    void addSignal(const std::string aname, std::vector<double>* avalues){
        names.push_back(aname);
        values.push_back(avalues);
    }

    void listAllNames(){
        std::cout << "Here go all the names:";
        for (const auto itName : names){
            std::cout << itName;
        }
    }
    
    void listData(){
        std::cout << "\nHere goes all data:" << std::endl;
        for(int i = 0; i<names.size(); i++){
            std::cout<< names[i] << std::endl;
            for(int i2 = 0; i2<5; i2++){ 
                std::cout << (*(values[i]))[i2] << ", ";
            }
            std::cout << std::endl;
        }
    }

    std::string getStringFromVector(const std::vector<double>& myVec){
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

    void exportSignals(){
        std::string strFileContent = "";
        strFileContent += "{\n";
        size_t nrArrays = names.size();
        size_t lastIdx = nrArrays-1;
        for(size_t i = 0; i < nrArrays; i++){
            strFileContent += "\t\""+ names[i] + "\" : " + getStringFromVector(*(values[i]));
            if(i<lastIdx) strFileContent += ",\n";
        }
        strFileContent += "\n}";

        std::ofstream out("output.json");
        out << strFileContent;
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



    size_t nrSamples = pwmSignal.size();
    std::vector<double> outputSamples;
    outputSamples.resize(nrSamples);

    TransferFunctionRC tfRC(C_F, R_ohm, Tsimstep_s);
    for(size_t i=0; i<nrSamples; i++){
        outputSamples[i] = tfRC.runSample(pwmSignal[i]);
    }

    SignalExporter sigExp;
    sigExp.addSignal("outputSamples", &outputSamples);
    sigExp.addSignal("pwmSignal", &pwmSignal);
    sigExp.exportSignals();

    return 0;
}