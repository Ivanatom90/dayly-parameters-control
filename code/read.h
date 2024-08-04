#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <algorithm>

#include "reader.h"
#include "catalog.h"

using namespace std;

void AddMap(map<string, string>& first, map<string, string>& second);
vector<double> ReadNumFromSVBU(string_view, vector<string>& time);
map<string, string> ReadNameKKS(string filenames);

vector<Parameter> ReadKKS(string file_names_, ostream& out);

vector<Parameter> ReadKKSSVBU(string file_names_, map<string, string>& KKSbook);

template <typename T>
list<T> ListFromVector(std::vector<T>& vec) {
    list<T> result;
    for(const T& par:vec){
        result.push_back(par);
    }
    return result;
}

template <typename T>
void AddListtoList(list<T>& a, list<T>& b, int pos){
    auto it = a.begin();
    for(int i = 0; i<pos; i++){
        it++;
    }

    for(auto& par:b){
        a.insert(par, it);
    }

    DelList(b);

}

template<typename T>
void DelList(list<T>& a){
    while(a.size() != 0){
        a.pop_front();
    }
}

