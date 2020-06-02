#ifndef USERINFORMATION_H
#define USERINFORMATION_H

#include<map>
#include<string>

const double METERS_PER_FOOT = 0.30480;
const double FEET_PER_INCH = 0.08333;
const double KILOGRAMS_PER_POUND = 2.20642;

class userInformation
{
public:
    /* Enumerations and Constants */
    enum class Gender{Null, Male, Female};
    const double MSJ_WEIGHT_CONSTANT = 10.0; /* MSJ refers to Mifflin-St Joer Equation Constants */
    const double MSJ_HEIGHT_CONSTANT = 6.25;
    const double MSJ_AGE_CONSTANT = 5.0;
    const double MSJ_MALE_TERM_CONSTANT = 5.0;
    const double MSJ_FEMALE_TERM_CONSTANT = 161.0;
    const double SEDENTARY_ACTIVITY_FACTOR = 1.2;
    const double MILD_ACTIVITY_FACTOR = 1.3;
    const double MODERATE_ACTIVITY_FACTOR = 1.5;
    const double HEAVY_ACTIVITY_FACTOR = 1.7;
    const double FIVE_POUND_LOSS_END_TERM = 583.3;
    const double TEN_POUND_LOSS_END_TERM = 1166.7;
    const int INCHES_PER_FOOT = 12;
    const double KILOGRAMS_PER_POUND = 0.45359;
    const double CENTIMETERS_PER_INCH = 2.54;
    const double CENTIMETERS_PER_FOOT = 30.48;

    /* Constructors */
    userInformation();

    /* Getters and Setters */
    const int & get_height_inches();
    const int & get_height_feet();
    const int & get_weight_pounds();
    const Gender & get_gender();
    const int & get_age_years();
    const int & get_days_exercise_per_week();
    const double & get_bmi();
    const int & get_bmi_percentile();
    const double & get_basal_metabolic_rate();
    const double & get_calorie_intake();
    std::map<std::string,std::map<int,double>> & get_exercise_calories_map();

    void set_height_inches(const int &);
    void set_height_feet(const int &);
    void set_weight_pounds(const int *);
    void set_gender(const Gender &);
    void set_age_years(const int *);
    void set_days_exercise_per_week(const int *);
    void set_bmi(const double &);
    void set_bmi_percentile(const int &);
    void set_basal_metabolic_rate(const double &);
    void set_calorie_intake(const double &);




    /* Other Functions */
    double calculate_BMI();
    void calculate_basal_metabolic_rate();
    void calculate_current_calorie_intake();
    double calculate_calorie_deficit(int &, const double &);
    void configure_calorie_map();


private:

    int height_inches;
    int height_feet;
    int weight_pounds;
    Gender gender;
    int age_years;
    int days_exericise_per_week;
    double bmi;
    int bmi_percentile;
    double basal_metabolic_rate;
    double calorie_intake;
    /* Exercise calories map contains exercise level, lbs lost per month, and calories consumed */
    /* This map will be used to create the calorie exercise chart on the user info section */
    std::map<std::string,std::map<int,double>> exercise_calories_map;


};



#endif // USERINFORMATION_H
