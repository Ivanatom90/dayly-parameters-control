#include "read.h"

map<string, string> ReadNameKKS(string filenames_kks)
{
            ifstream file(filenames_kks);
            string s;
            string KKS;
            string name;
            map<string, string> KKS_translator_;

            for (int i=0;i<5;i++)
            {
                getline(file, s);
            }

            while(getline(file, s))
            {
                string_view str = s;
                int space = str.find('|');
                KKS = str.substr(0, space-1);
                str.remove_prefix(space+1);
                space = str.find('|');
                name = str.substr(0, space);
                KKS_translator_[KKS] = name;
            }
    return KKS_translator_;
}



vector<Parameter> ReadKKS(string fileRSA, ostream& out)
{
    ifstream file(fileRSA);
    string str;
        for (int i=0; i<5; i++)
        {
            getline(file, str);
        }
    vector<string> KKS =  ReadlineS(str);
    KKS.pop_back();
    vector<vector<double>> parameters;
    parameters.resize(KKS.size());
    vector<string> timer;
        while (getline(file, str))
        {
            int i = 0;
            int t = str.find('|');
            string time = str.substr(0, t);
            timer.push_back(time);
            for (double num:ReadlineNum(str)){
                parameters[i].push_back(num);
                i++;
            }
        }

    vector<Parameter> result;
    int i = 0;
        for(string kks:KKS){
            Parameter par(kks, parameters[i], timer);
            result.push_back(move(par));
            i++;
        }

return result;
}


vector<Parameter> ReadKKSSVBU(string file_names_, map<string, string>& KKSbook){
    ifstream file(file_names_);
    string str;
    for(int i=0; i<4; i++){
        getline(file, str);
    }
    string_view sv = str;
    std::map<string, string> resultmap;
    do {
        string_view strv = str;
        int pos = strv.find_first_of('\t');
        strv.remove_suffix(strv.size() - pos);
        pair<string, string> res;
        res.first = string(strv);
        strv = str;
        pos = strv.find_first_of('\t');
        strv.remove_prefix(pos);
        res.second = string(strv);
        resultmap.insert(res);
        getline(file, str);
    } while(str[1] >= '0' && str[1]<='9');

    AddMap(KKSbook, resultmap);

    sv = str;
    int pos = sv.find_first_of('\t');
    sv.remove_prefix(pos+1);
    std::vector<string> KKS;
    while(pos != sv.npos){
        pos = sv.find_first_of('\t');
        string_view kks = sv.substr(0, pos);
        KKS.push_back(string(kks));
        sv.remove_prefix(pos+1);
    }
    KKS.pop_back();
    using Dubvec = std::vector<std::vector<double>>;
    Dubvec dubvec;
    dubvec.reserve(KKS.size());
    vector<string> time;
    while(getline(file, str)){
        dubvec.push_back(ReadNumFromSVBU(str, time));
    }
    vector<Parameter> resvec;
    resvec.reserve(dubvec[0].size());

    for(int i=0; i<dubvec[0].size(); i++){
        vector<double> result;
        result.reserve(dubvec.size());
        for(int j=0; j<dubvec.size(); j++){
            result.push_back(dubvec[j][i]);
        }
        Parameter par(KKS[i], result, time);
        resvec.push_back(par);
    }
    return resvec;

}

vector<double> ReadNumFromSVBU(string_view sv, vector<string>& time){
        int pos = sv.find_first_of('\t');
        time.push_back(string(sv.substr(0,pos)));
        sv.remove_prefix(pos+1);
        vector<double> result;
        pos = sv.find_first_of('\t');
        while(pos != sv.npos){         
            string_view number = sv.substr(0, pos);
            double num = stod(string(number));
            result.push_back(num);
            sv.remove_prefix(pos+1);
            pos = sv.find_first_of('\t');
        }
    return result;
}

void AddMap(map<string, string>& first, map<string, string>& second){
    for(const std::pair<string, string>& param:second){
        first.insert(param);
    }

}
