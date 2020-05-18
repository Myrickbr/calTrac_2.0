#include "../include/userinformation.h"
#include <iostream>

userInformation::userInformation()
{
    /* Initialize values to null (except height values since default is 5' 7") */

    this->height_inches = 7;
    this->height_feet = 5;
    this->weight_pounds = NULL;
    this->age_years = NULL;
    this->gender = Gender::Null;
    this->age_years = NULL;
    this->days_exericise_per_week = NULL;
    this->bmi = NULL;
    this->bmi_percentile = NULL;

}

const int & userInformation::get_height_inches(){
    return this->height_inches;
}
const int & userInformation::get_height_feet(){
    return this->height_feet;
}
const int * userInformation::get_weight_pounds(){
    return &(this->weight_pounds);
}
const userInformation::Gender * userInformation::get_gender(){
    return &(this->gender);
}
const int * userInformation::get_age_years(){
    return &(this->age_years);
}
const int * userInformation::get_days_exercise_per_week(){
    return &(this->days_exericise_per_week);
}
const double * userInformation::get_bmi(){
    return &(this->bmi);
}
const int * userInformation::get_bmi_percentile(){
    return &(this->bmi_percentile);
}
const double * userInformation::get_calorie_intake(){
    return &(this->calorie_intake);
}
void userInformation::set_height_inches(const int & heightInches){
    this->height_inches = heightInches;
}
void userInformation::set_height_feet(const int & heightFeet){
    this->height_feet = heightFeet;
}
void userInformation::set_weight_pounds(const int * weightPounds){
    this->weight_pounds = *weightPounds;
}
void userInformation::set_gender(const userInformation::Gender * gender_){
    this->gender = * gender_;
}
void userInformation::set_age_years(const int * ageYears){
    this->age_years = *ageYears;
}
void userInformation::set_days_exercise_per_week(const int * daysExercisePerWeek){
    this->days_exericise_per_week = * daysExercisePerWeek;
}
void userInformation::set_bmi(const double * bmi_){
    this->bmi = *bmi_;
}
void userInformation::set_bmi_percentile(const int * bmiPercentile){
    this->bmi_percentile = *bmiPercentile;
}
void userInformation::set_calorie_intake(const double * calorieIntake){
    this->calorie_intake = *calorieIntake;
}


double userInformation::calculate_BMI(){

    return 0.0;
}

double userInformation::calculate_BMI_percentile(){

    return 0.0;
}
