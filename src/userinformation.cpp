#include "../include/userinformation.h"
#include <iostream>
#include <cmath>

userInformation::userInformation()
{
    /* Initialize values to null (except height values since default is 5' 7") */

    this->age_years = -1;
    this->bmi = -1.0;
    this->weight_pounds = -1;
    this->days_exericise_per_week = 0;
    this->height_feet = 5;
    this->height_inches = 7;
    this->gender = Gender::Null;
    this->basal_metabolic_rate = -1;
    this->calorie_intake = -1;

}

const int & userInformation::get_height_inches(){
    return this->height_inches;
}
const int & userInformation::get_height_feet(){
    return this->height_feet;
}
const int & userInformation::get_weight_pounds(){
    return this->weight_pounds;
}
const userInformation::Gender & userInformation::get_gender(){
    return this->gender;
}
const int & userInformation::get_age_years(){
    return this->age_years;
}
const int & userInformation::get_days_exercise_per_week(){
    return this->days_exericise_per_week;
}
const double & userInformation::get_bmi(){
    return this->bmi;
}
const int & userInformation::get_bmi_percentile(){
    return this->bmi_percentile;
}
const double & userInformation::get_basal_metabolic_rate(){
    return this->basal_metabolic_rate;
}
const double & userInformation::get_calorie_intake(){
    return this->calorie_intake;
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
void userInformation::set_gender(const userInformation::Gender & gender_){
    this->gender = gender_;
}
void userInformation::set_age_years(const int * ageYears){
    this->age_years = *ageYears;
}
void userInformation::set_days_exercise_per_week(const int * daysExercisePerWeek){
    this->days_exericise_per_week = *daysExercisePerWeek;
}
void userInformation::set_bmi(const double & bmi_){
    this->bmi = bmi_;
}
void userInformation::set_bmi_percentile(const int & bmiPercentile){
    this->bmi_percentile = bmiPercentile;
}
void userInformation::set_basal_metabolic_rate(const double & basalMetabolicRate){
    this->basal_metabolic_rate = basalMetabolicRate;
}
void userInformation::set_calorie_intake(const double & calorieIntake){
    this->calorie_intake = calorieIntake;
}
double userInformation::calculate_BMI(){

    /* To calculate BMI, first convert weight to kilograms and height to meters */
    double weightKilograms = this->weight_pounds * KILOGRAMS_PER_POUND;
    double heightMeters = (this->height_inches * FEET_PER_INCH + this->height_feet) * METERS_PER_FOOT;

    /* Now divide weight (kg) by height squared (m^2) */
    double bmi = (weightKilograms) / (pow(heightMeters,2));

    return bmi;
}
void userInformation::calculate_basal_metabolic_rate(){
    double weightInKilograms = this->weight_pounds * KILOGRAMS_PER_POUND;
    double heightInCentimeters = this->height_feet * CENTIMETERS_PER_FOOT + this->height_inches * CENTIMETERS_PER_INCH;

    switch(this->get_gender()){
        case userInformation::Gender::Male:{
            double tempBMR = weightInKilograms * MSJ_WEIGHT_CONSTANT + heightInCentimeters * MSJ_HEIGHT_CONSTANT -
                             this->get_age_years() * MSJ_AGE_CONSTANT + MSJ_MALE_TERM_CONSTANT;
            this->set_basal_metabolic_rate(tempBMR);
            break;
        }
        case userInformation::Gender::Female:{
            double tempBMR = weightInKilograms * MSJ_WEIGHT_CONSTANT + heightInCentimeters * MSJ_HEIGHT_CONSTANT -
                             this->get_age_years() * MSJ_AGE_CONSTANT - MSJ_FEMALE_TERM_CONSTANT;
            this->set_basal_metabolic_rate(tempBMR);
            break;
        }
        case userInformation::Gender::Null:{
            perror("ERROR: No gender selected!");
            return;
        }

    }
}
void userInformation::calculate_current_calorie_intake(){
    /* Take the user BMR and multiply it by the corresponding activity factor */
    /* 0 Days = Sedentary, 1-2 Days = Mild, 3-6 Days = Moderate, 7 Days = Heavy */

    if(this->get_basal_metabolic_rate() == -1){
        perror("Basal Metabolic Rate has not been calculated yet!");
        this->calculate_basal_metabolic_rate();
    }

    double tempCalorieIntake = 0;

    switch(this->get_days_exercise_per_week()){
        case 0:
            tempCalorieIntake = this->get_basal_metabolic_rate() *  SEDENTARY_ACTIVITY_FACTOR;
            this->set_calorie_intake(tempCalorieIntake);
            break;
        case 1 ... 2:
            tempCalorieIntake = this->get_basal_metabolic_rate() * MILD_ACTIVITY_FACTOR;
            this->set_calorie_intake(tempCalorieIntake);
            break;
        case 3 ... 6:
            tempCalorieIntake = this->get_basal_metabolic_rate() * MODERATE_ACTIVITY_FACTOR;
            this->set_calorie_intake(tempCalorieIntake);
            break;
        case 7:
            tempCalorieIntake = this->get_basal_metabolic_rate() * HEAVY_ACTIVITY_FACTOR;
            this->set_calorie_intake(tempCalorieIntake);
            break;
    }

}
