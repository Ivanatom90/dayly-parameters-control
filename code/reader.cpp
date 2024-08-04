#include "reader.h"

vector<string> ReadlineS(const string& str)
{
    vector <string> strv_v;
    strv_v.reserve(129);
    string_view sv = str;
    size_t space = sv.find('|');
    sv.remove_prefix(space + 1);
    while(true){
        space = sv.find('|');
        string_view a = sv.substr(0, space);
        strv_v.push_back(string(a));
        if(space != sv.npos){
            sv.remove_prefix(space+1);
        } else {
            break;
        }

    }

return strv_v;
}

string GetTime(const string& str){
    string_view s = str;
    int space = s.find('|');
    return {string(s.substr(0, space))};
}


vector<double> ReadlineNum(const string& str)
{
    string_view s = str;
    vector <double> num;
    vector<string_view> v_str;
    int space = s.find('|');
    s.remove_prefix(space);
    while(true){
        size_t space = s.find('|');
        string_view sp = s.substr(space+1);
        size_t num_border = sp.find_first_of(' ');
        sp.remove_suffix(sp.size() - num_border);
        v_str.push_back(sp);
        if(space == s.npos){
            break;
        } else {
            s.remove_prefix(space+1);
        }
    }

    for_each(v_str.begin(), v_str.end(), [&num](string_view text){
        if((text[0]>='0' && text[0] <= '9') || text[0]=='-'){
            num.push_back(stod(string(text)));
        }
    });

return num;
}
