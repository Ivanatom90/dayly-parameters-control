#include "parameters_group.h"


ostream& operator<<(ostream& out, const std::vector<double>& vec) {
    for(const double& par:vec){
        out<<setw(46)<<par;
    }
    return out;
}


Temperature::Temperature(std::list<Parameter>& t){
    temperatures_ = std::move(t);
    CreateHotCold();
    CreateHotPetDayly();
    CreateColdPetDayly();
}


void Temperature::CreateHotCold(){
    for(Parameter& par:temperatures_ ){
        //6
        if(par.GetKKS().at(6) == '1'){
            T_hot_pet_.push_front(std::move(par));
        } else if(par.GetKKS().at(6) == '3'){
            T_cold_pet_.push_front(std::move(par));
        } else{
            dT_az_ = std::move(par);
        }

    }

};


void Temperature::CreateHotPetDayly(){
    std::vector<std::vector<DaylyParameters>> result;
    std::for_each(T_hot_pet_.begin(), T_hot_pet_.end(), [this, &result](Parameter& par){
        std::vector<DaylyParameters> tmp;
        for(const DaylyParameters& dp:par.GetDayly()){
            tmp.push_back(dp);
        }

        result.push_back(std::move(tmp));

    });

    std::vector<DaylyParameters> tempmax;
    size_t size = result.size();
    for(int i = 0; i<int(result[0].size()); i++){
        for(std::vector<DaylyParameters>& dp:result){
            tempmax.push_back(dp.at(i));
        }
        sort(tempmax.begin(), tempmax.end(), [](const DaylyParameters& a, const DaylyParameters& b){
            return a.GetMax()>b.GetMax();
        });
        Hot_pet_dayly_max.push_back(tempmax[0]);
        tempmax.clear();
    }

}

void Temperature::CreateColdPetDayly(){

    std::vector<std::vector<DaylyParameters>> result;
    std::for_each(T_cold_pet_.begin(), T_cold_pet_.end(), [this, &result](Parameter& par){
        std::vector<DaylyParameters> tmp;
        for(const DaylyParameters& dp:par.GetDayly()){
            tmp.push_back(dp);
        }

        result.push_back(std::move(tmp));

    });

    std::vector<DaylyParameters> tempmax;
    size_t size = result.size();
    for(int i = 0; i<int(result[0].size()); i++){
        for(std::vector<DaylyParameters>& dp:result){
            tempmax.push_back(dp.at(i));
        }
        sort(tempmax.begin(), tempmax.end(), [](const DaylyParameters& a, const DaylyParameters& b){
            return a.GetMax()>b.GetMax();
        });
        Cold_pet_dayly_max.push_back(tempmax[0]);
        tempmax.clear();
    }

}


std::vector<DaylyParameters> Temperature::GetHotDayly(){
    return Hot_pet_dayly_max;
}
std::vector<DaylyParameters> Temperature::GetColdDayly(){
    return Cold_pet_dayly_max;
}


std::ostream& Temperature::Print(ostream& out){
    int width = 46;
    out<<setw(4)<<"";
/*    for(const DaylyParameters& par:Hot_pet_dayly_max){
        out<<setw(width)<<par.GetTime();
    }
    out<<endl;
*/
    for(const DaylyParameters& par:Hot_pet_dayly_max){
        out<<setw(width)<<par.GetMax();
    }
    out<<"                                     Max Temperatures in hot pet"<<endl;

    out<<setw(4)<<"";
    for(const DaylyParameters& par:Cold_pet_dayly_max){
        out<<setw(width)<<par.GetMax();
    }
    out<<"                                     Max Temperatures in cold pet"<<endl;

    return out;
}





list<Parameter> CreateTemp(list<Parameter>& parameters){
    list<Parameter> result_t;
    list<Parameter>::iterator it = parameters.begin();
    list<list<Parameter>::iterator> list_it;
    for(Parameter& par:parameters){
        string s(par.GetKKS());
        string_view str = s;
        str.remove_prefix(7);
        str.remove_suffix(str.size() - 2);
        if(str == "CT"sv){
            result_t.push_front(std::move(par));
            list_it.push_front(it);
        }
        it++;
    }

    for(auto& iter:list_it){
        parameters.erase(iter);
    }

    return result_t;

}


Period::Period(std::list<Parameter>& period){
    SetParameters(period);
    CreateMin();
}

list<Parameter> CreateParametersGroup(list<Parameter>& parameters,  string_view s_in, int8_t a = 1, int8_t b = 8){
    list<Parameter> result_t;
    for(Parameter& par:parameters){
        string s(par.GetKKS());
        string_view str = s;
        str.remove_prefix(a);
        str.remove_suffix(b);
        if(str == s_in){
            result_t.push_front(std::move(par));
        }
    }

    for(const Parameter& res:result_t){
        auto it = find_if(parameters.begin(), parameters.end(), [&res](const Parameter& par){
            return (res.GetKKS() == par.GetKKS());
        });
        if(it != parameters.end()){
            parameters.erase(it);
        }
    }

    return result_t;
}



void Period::CreateMin() {
    std::vector<double> result;
    result.reserve(GetParameters().front().GetDaylySize());
    for(size_t i = 0; i<GetParameters().front().GetDaylySize(); i++){
        double min_per = 1000;
        for(Parameter& per:GetParameters()){
            per.GetDayly()[i].NegativeParDelete();
            double dayly_min = per.GetDayly()[i].GetMin();
             if(min_per > dayly_min  && dayly_min>0){
                 min_per = dayly_min;
             }
        }
        result.push_back(min_per);
        std::cout<<min_per<<"     ";
    }
    SetMinDayly(result);
}

ostream& Period::Print(ostream& out, std::string text, bool only_min){
    out<<"    "<<GetMinDayly()<<"                                 "<<text<<endl;
    return out;
}


ParametersGroup::ParametersGroup(std::list<Parameter>& parameters){
    parameters_=  std::move(parameters);
    //parameters_.swap(parameters);
    CreateMin();
    CreateMax();
    CreateMid();
}

std::list<Parameter>& ParametersGroup::GetParameters() {
    return parameters_;
}

void ParametersGroup::SetParameters(std::list<Parameter>& parameters){
    parameters_ = std::move(parameters);
}

void ParametersGroup::CreateMin(){
    for(size_t i = 0; i<parameters_.front().GetDaylySize(); i++){
        std::vector<double> result;
            for(Parameter& par:parameters_){
                result.push_back(par.GetDayly()[i].GetMin());
            }
        min_dayly_parameters.push_back(*min_element(result.begin(), result.end()));
    }
}

void ParametersGroup::CreateMax(){
    for(size_t i = 0; i<parameters_.front().GetDaylySize(); i++){
        std::vector<double> result;
            for(Parameter& par:parameters_){
                result.push_back(par.GetDayly()[i].GetMax());
            }
        max_dayly_parameters.push_back(*max_element(result.begin(), result.end()));
    }
}

void ParametersGroup::CreateMid(){
    for(size_t i = 0; i<parameters_.front().GetDaylySize(); i++){
        std::vector<double> result;
            for(Parameter& par:parameters_){
                result.push_back(par.GetDayly()[i].GetMid());
            }
            std::sort(result.begin(), result.end());
            int indef =result.size()/2;
        mid_dayly_parameters.push_back(result[indef]);
    }
}

void ParametersGroup::SetMinDayly(std::vector<double>& par){
    min_dayly_parameters.swap(par);
}
void ParametersGroup::SetMaxDayly(std::vector<double>& par){
    max_dayly_parameters.swap(par);
}

const std::vector<double>& ParametersGroup::GetMinDayly() const{
    return min_dayly_parameters;
}
const std::vector<double>& ParametersGroup::GetMaxDayly() const{
    return max_dayly_parameters;
}

const std::vector<double>& ParametersGroup::GetMidDayly() const{
    return mid_dayly_parameters;
}

ostream& ParametersGroup::Print(ostream& out, std::string text, bool only_min){       

        if(only_min){
            out<<setw(10)<<""<<GetMinDayly()<<"                             "<<"Min"s + text<<endl;
            return out;
        }
        int i = 0;
        out<<setw(14)<<"";
        for(const auto& par:GetMinDayly()){
            out<<setw(26)<<par<<"     "<<GetMidDayly()[i]<<"     "<<GetMaxDayly()[i];
            i++;
        }
        out<<"              "<<"Min/Max "s + text<<endl;

    return out;
}
