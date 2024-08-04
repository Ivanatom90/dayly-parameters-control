#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <map>

#include "domain.h"

using namespace std;


class DaylyParameters{
    public:
        DaylyParameters() = default;
        DaylyParameters(string time, vector<double>& val);
        void CreateMinMaxMid();
        double GetMin() const;
        double GetMax() const;
        double GetMid() const;
        string GetTime() const;
        void NegativeParDelete();
        vector<double>& GetParameters();
    private:
        string time_;
        vector<double> parameters_;
};


class Parameter{
    public:
       Parameter() = default;
       Parameter(string KKS, vector<double>& values, vector<string> time);
       Parameter(vector<double> values, vector<string> time);

       void CreateDayly();
       string GetKKS() const;

       void Monitoring(std::ostream& out) const;
       void HaveDates(std::ostream& out) const;

       std::vector<DaylyParameters>& GetDayly();
       size_t GetDaylySize();


    private:
        string KKS_;
        vector<string> time_;
        vector<double> values_;
        string date_;       
        vector<DaylyParameters> dayly_;

};

bool operator==(const Parameter& a, const Parameter& b);

template <typename Conteiner>
void Print(ostream& out, Conteiner& parameters, map<string, string>& KKS_translator){
    parameters.back().HaveDates(out);

    for(const Parameter& par:parameters){   //общая инфа по всем датчикам
            par.Monitoring(out);
            try {
                out<<"       "<<KKS_translator.at(par.GetKKS())<<endl;
            }  catch (...) {
                out<<"       "<<"non_parameters"<<endl;
            }
    }
}

//static bool operator=(Parameter t1, Parameter t2) const;

vector<Parameter> MergeVec(vector<Parameter>& a, vector<Parameter>& b);

void DeleteEmptySells(list<Parameter>& con);
