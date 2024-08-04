#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <ostream>
#include <memory>
#include <numeric>
#include <list>

#include "catalog.h"
#include "read.h"
#include "domain.h"
#include "printer.h"
#include "parameters_group.h"

using namespace std;


int main()
{

    ofstream file("outfile.txt");
    vector<Parameter> parameters;
    parameters = ReadKKS("CONTROL.txt", file);
    map<string, string> KKS_translator = ReadNameKKS("CONTROL_names.txt");
    vector<Parameter> Suz;
    Suz = ReadKKS("OR_SUZ.txt", file);
    map<string, string> KKS_SUZ = ReadNameKKS("OR_SUZ_names.txt");
    AddMap(KKS_translator, KKS_SUZ);
    vector<Parameter> JNK = ReadKKSSVBU("JNK.txt", KKS_translator);

    vector<Parameter> KD = ReadKKSSVBU("KD.txt", KKS_translator);
    list<Parameter> KD_list = ListFromVector(KD);

    list<Parameter> P_kd = CreateParametersGroup(KD_list, "0JAA10CP8"sv, 1, 8);
    ParametersGroup P_kd_pg(P_kd);

    list<Parameter> L_kd = CreateParametersGroup(KD_list, "03ER060"sv, 5, 6);
    ParametersGroup L_kd_pg(L_kd);

    vector<Parameter> Lpg1 = ReadKKSSVBU("L_PG_1.txt", KKS_translator);
    list<Parameter> Lpg1_list = ListFromVector(Lpg1);

    list<Parameter> L_pg1 = CreateParametersGroup(Lpg1_list, "0JEA10CL8"sv, 1, 8);
    ParametersGroup L_pg1_PG(L_pg1);

    list<Parameter> L_pg2 = CreateParametersGroup(Lpg1_list, "0JEA20CL8"sv, 1, 8);
    ParametersGroup L_pg2_PG(L_pg2);

    vector<Parameter> Lpg2 = ReadKKSSVBU("L_PG_2.txt", KKS_translator);
    list<Parameter> Lpg2_list = ListFromVector(Lpg2);

    list<Parameter> L_pg3 = CreateParametersGroup(Lpg2_list, "0JEA30CL8"sv, 1, 8);
    ParametersGroup L_pg3_PG(L_pg3);

    list<Parameter> L_pg4 = CreateParametersGroup(Lpg2_list, "0JEA40CL8"sv, 1, 8);
    ParametersGroup L_pg4_PG(L_pg4);

    vector<Parameter> Ppg1 = ReadKKSSVBU("P_PG_1.txt", KKS_translator);
    list<Parameter> Ppg1_list = ListFromVector(Ppg1);

    list<Parameter> P_pg1 = CreateParametersGroup(Ppg1_list, "0LBA10CP8"sv, 1, 8);
    ParametersGroup P_pg1_PG(P_pg1);

    list<Parameter> P_pg2 = CreateParametersGroup(Ppg1_list, "0LBA20CP8"sv, 1, 8);
    ParametersGroup P_pg2_PG(P_pg2);

    vector<Parameter> Ppg34 = ReadKKSSVBU("P_PG_2.txt", KKS_translator);
    list<Parameter> Ppg34_list = ListFromVector(Ppg34);

    list<Parameter> P_pg3 = CreateParametersGroup(Ppg34_list, "0LBA30CP8"sv, 1, 8);
    ParametersGroup P_pg3_PG(P_pg3);

    list<Parameter> P_pg4 = CreateParametersGroup(Ppg34_list, "0LBA40CP8"sv, 1, 8);
    ParametersGroup P_pg4_PG(P_pg4);

    list<Parameter> par_list = ListFromVector(parameters);
    list<Parameter> temperatures = CreateTemp(par_list);

    list<Parameter> Peri = CreateParametersGroup(par_list, "75FX014"sv, 5, 4);


    AddVectorToList(par_list, Suz, 15);
    AddVectorToList(par_list, JNK, par_list.size());

    list<Parameter> Ql = CreateParametersGroup(par_list, "25FX906"sv, 5, 4);
    ParametersGroup Qlgroup(Ql);
    list<Parameter> Qlptvel = CreateParametersGroup(par_list, "27FX906"sv, 5,4);
    ParametersGroup Qlpt_gp(Qlptvel);
    list<Parameter> Qltveg = CreateParametersGroup(par_list, "26FX906"sv,5,4);
    ParametersGroup Qltveggroup(Qltveg);

    DeleteEmptySells(par_list);
    Print(file, par_list, KKS_translator);

    L_pg1_PG.Print(file, "level PG_1", false);
    L_pg2_PG.Print(file, "level PG_2", false);
    L_pg3_PG.Print(file, "level PG_3", false);
    L_pg3_PG.Print(file, "level PG_4", false);

    P_pg1_PG.Print(file, "P PG_1", false);
    P_pg2_PG.Print(file, "P PG_2", false);
    P_pg3_PG.Print(file, "P PG_3", false);
    P_pg4_PG.Print(file, "P PG_4", false);

    P_kd_pg.Print(file, "P KD", false);
    L_kd_pg.Print(file, "L KD", false);


    Qlgroup.Print(file, " zap Ql", true);
    Qlpt_gp.Print(file, " zap Ql_peref_tvel", true);
    Qltveggroup.Print(file, " zap Ql_tveg", true);

    Temperature Temp(temperatures);
    Period Perio(Peri);

    Temp.Print(file);

    Perio.Print(file, "Min_period", true);

    cout << "good_work!" << endl;
    return 0;
}



