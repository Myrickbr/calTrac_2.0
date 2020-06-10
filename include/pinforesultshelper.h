#ifndef PINFORESULTSHELPER_H
#define PINFORESULTSHELPER_H
#include<string>

/* --------------------------------------------------------------------------------- */
/* This is a helper class for the personal info page (results section). This class */
/* helps read from bmi data file and performs calculations required for this section */
/* --------------------------------------------------------------------------------- */

class pInfoResultsHelper
{
public:

    /* Enumerations and Constants */
    enum class WeightStatus{Null, Underweight, Healthy, Overweight, Obese};
    const double UNDERWEIGHT_BMI_THRESHOLD = 18.9;
    const double HEALTHY_WEIGHT_BMI_THRESHOLD = 24.9;
    const double OVERWEIGHT_BMI_THRESHOLD = 29.9;
    const double KILOGRAMS_PER_POUND = 0.45359;
    const double POUNDS_PER_KILOGRAM = 2.20462;
    const double METERS_PER_FOOT = 0.30480;


    /* Constructors and Destructors */
    pInfoResultsHelper();

    /* Getters and Setters */
    const WeightStatus & getWeightStatus();
    void setWeightStatus(const WeightStatus &);

    /* Other functions */
    std::string is_threshold(const double &);
    std::string get_healthy_weight_statement(double &, double &);

private:
    WeightStatus weightStatus;

};

#endif // PINFORESULTSHELPER_H
