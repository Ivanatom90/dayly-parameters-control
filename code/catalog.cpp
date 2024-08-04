#include "catalog.h"
#include "read.h"

Parameter::Parameter(string KKS, vector<double>& values, vector<string> time): KKS_(KKS){
     dayly_.reserve(10);
     values_ = move(values);
     time_ = move(time);
     date_ = time_.front()+ "     " + time_.back();
     CreateDayly();
}


Parameter::Parameter(vector<double> values, vector<string> time){
    values_ = move(values);
    time_ = move(time);
    date_ = time_.front();
    KKS_ = this->KKS_;
}


DaylyParameters::DaylyParameters(string time, vector<double>& val): time_(time), parameters_(val){}

double DaylyParameters::GetMin() const{
    return *min_element(begin(parameters_), end(parameters_));
}
double DaylyParameters::GetMax() const{
    return *max_element(parameters_.begin(), parameters_.end());
}
double DaylyParameters::GetMid() const{
    return accumulate(parameters_.begin(), parameters_.end(), 0.00)/parameters_.size();
}


string Parameter::GetKKS() const{
     return KKS_;
 }

void Parameter::CreateDayly(){
     int i = 0;
     int date = 0;
     //vector<string> result_dates;
     vector<double> result_values;
     for(const string& moment:time_){
         int point = moment.find('.');
         string_view day = moment;
         day.remove_suffix(point+1);
         int last_date = date;
         date = stoi(string(day));
         if(date != last_date && last_date != 0){
             dayly_.push_back(DaylyParameters(moment, result_values));
             //result_dates.clear();
             result_values.clear();
         }
         //result_dates.push_back(string(day));
         result_values.push_back(values_[i]);
         i++;
     }
     values_.clear();
 }


 void Parameter::Monitoring(std::ostream& out) const{
     out.width(30);
     out<<KKS_;
     out.precision(5);
     for(const DaylyParameters& par:dayly_){
         int width = 10;
         out<<setw(width)<<par.GetMin()<<setw(width)<<par.GetMid()<<setw(width)<<par.GetMax()<<"                ";
     }
 }


 void Parameter::HaveDates(std::ostream& out) const{
     out<<setw(14)<<"";
     for(const DaylyParameters& par:dayly_){
         out<<setw(46)<<par.GetTime();
     }
     out<<endl;
 }

 size_t Parameter::GetDaylySize(){
     return dayly_.size();
 }

 string DaylyParameters::GetTime() const{
     return time_;
 }

bool operator==(const Parameter& a, const Parameter& b){
    return a.GetKKS() == b.GetKKS();
}


std::vector<DaylyParameters>& Parameter::GetDayly() {
    return dayly_;
}

std::vector<double>& DaylyParameters::GetParameters(){
    return parameters_;
}

void DaylyParameters::NegativeParDelete(){
    std::vector<double> result;
    for(const double& par:parameters_){
        if(par>0){
            result.push_back(par);
        }
    }
    result.swap(parameters_);
}

void DeleteEmptySells(list<Parameter>& con){
    std::_List_iterator<Parameter> it = con.begin();
     while(it != con.end()){
        it = find_if(con.begin(), con.end(), [](Parameter& p){
                return p.GetKKS() == "";
            });
        if(it != con.end()){
            con.erase(it);
        }
    };
}

