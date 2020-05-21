#ifndef USERINFORMATION_H
#define USERINFORMATION_H


const double METERS_PER_FOOT = 0.30480;
const double FEET_PER_INCH = 0.08333;
const double KILOGRAMS_PER_POUND = 2.20642;

class userInformation
{
public:
    /* Enumerations and Constants */
    enum class Gender{Null, Male, Female};


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
    const double * get_calorie_intake();
    void set_height_inches(const int &);
    void set_height_feet(const int &);
    void set_weight_pounds(const int *);
    void set_gender(const Gender &);
    void set_age_years(const int *);
    void set_days_exercise_per_week(const int *);
    void set_bmi(const double &);
    void set_bmi_percentile(const int &);
    void set_calorie_intake(const double *);




    /* Other Functions */
    double calculate_BMI();


private:

    int height_inches;
    int height_feet;
    int weight_pounds;
    Gender gender;
    int age_years;
    int days_exericise_per_week;
    double bmi;
    int bmi_percentile;
    double calorie_intake;

};



#endif // USERINFORMATION_H
