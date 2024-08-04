#pragma once
#include <list>
#include "catalog.h"


class ParametersGroup{
    public:
        ParametersGroup() = default;
        ParametersGroup(std::list<Parameter>& parameters);


        virtual void CreateMin();
        void CreateMid();
        void CreateMax();
        void SetParameters(std::list<Parameter>& parameters);
        void SetMinDayly(std::vector<double>& par);
        void SetMaxDayly(std::vector<double>& par);
        std::list<Parameter>& GetParameters();
        const std::vector<double>& GetMinDayly() const;
        const std::vector<double>& GetMidDayly() const;
        const std::vector<double>& GetMaxDayly() const;
        virtual ostream& Print(ostream& out, std::string text, bool only_min);

    private:
        std::vector<double> min_dayly_parameters;
        std::vector<double> mid_dayly_parameters;
        std::vector<double> max_dayly_parameters;
        std::list<Parameter> parameters_;

};

class Period : ParametersGroup{
    public:
        Period(std::list<Parameter>& period);
        void CreateDaylyPeriods();
        void PeriodMake();
        ostream& Print(ostream& out, std::string text, bool only_min) override;
        void CreateMin() override;
    private:
        //std::list<Parameter> periods_;
        //std::vector<double> min_dayly_per_;

};

class Temperature{
    public:
        Temperature(std::list<Parameter>& t);

        std::vector<DaylyParameters> GetHotDayly();
        std::vector<DaylyParameters> GetColdDayly();
        std::ostream& Print(std::ostream& out);


    private:
        std::list<Parameter> temperatures_;
        std::list<Parameter> T_hot_pet_;
        std::list<Parameter> T_cold_pet_;
        Parameter dT_az_;
        std::vector<DaylyParameters> Hot_pet_dayly_max;
        std::vector<DaylyParameters> Cold_pet_dayly_max;

        void CreateHotCold();
        void CreateHotPetDayly();
        void CreateColdPetDayly();
};




list<Parameter> CreateTemp(list<Parameter>& parameters);
//list<Parameter> CreateParametersGroup(list<Parameter>& parameters,  string_view s);
list<Parameter> CreateParametersGroup(list<Parameter>& parameters,  string_view s, int8_t a, int8_t b);

