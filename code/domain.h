#pragma once
#include <string>
#include <list>
#include <vector>

struct Value{
  std::string KKS, name;
  double max, mid, min;
};


class Day_values{
    private:
        double Nakz,
        Naknp,
        Tgn,
        Tcold,
        deltaT_AZ,
        T_tvs_out,
        zap_Ql,
        zap_DNBR,
        Kq_max,
        Kq_max_coord,
        Kv_min_zap,
        Ntvs_max,
        dTpet,
        dP_az,
        G_az,
        C_bor,
        Paz_min,
        Paz_max;
        std::pair<double, double>P_pg1; // min max
        std::pair<double, double>P_pg2;
        std::pair<double, double>P_pg3;
        std::pair<double, double>P_pg4;



};

template <typename T>
void AddVectorToList(std::list<T>& l, std::vector<T>& v, int pos){
    auto it = l.begin();
    for(int i = 0; i<pos; i++){
        it++;
    }
    for(T& par:v){
          l.insert(it, par);
      }
};
