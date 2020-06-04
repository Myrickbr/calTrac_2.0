#include "../include/userinformation.h"
#include <iostream>
#include <cmath>
#include <array>

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
std::map<std::string,std::map<int,double>> & userInformation::get_exercise_calories_map(){
    return this->exercise_calories_map;
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
double userInformation::calculate_calorie_deficit(int & poundLossPerMonth, const double & exerciseCoefficient){
    double tempCalorieDeficit = 0;
    if(poundLossPerMonth == 0){
        tempCalorieDeficit = this->get_basal_metabolic_rate() * exerciseCoefficient;
    }else if (poundLossPerMonth == 5){
        tempCalorieDeficit = this->get_basal_metabolic_rate() * exerciseCoefficient - FIVE_POUND_LOSS_END_TERM;
    }else if (poundLossPerMonth == 10){
        tempCalorieDeficit = this->get_basal_metabolic_rate() * exerciseCoefficient - TEN_POUND_LOSS_END_TERM;
    }
    return tempCalorieDeficit;

}
void userInformation::configure_calorie_map(){
    std::string temp_exercise_type_arr[] = {"Sedentary", "Mild", "Moderate", "Heavy"};
    int temp_pounds_loss_arr[] = {0,5,10};
    double tempCalorieDeficit = 0;
    double tempCalorieDeficitArr[(sizeof(temp_pounds_loss_arr)/sizeof(*temp_pounds_loss_arr))];

    for(int exerciseIndex = 0; exerciseIndex < (sizeof(temp_exercise_type_arr)/sizeof(*temp_exercise_type_arr));++exerciseIndex){
        std::map<int,double> tempInnerMap;

        for(int poundsIndex = 0; poundsIndex < (sizeof(temp_pounds_loss_arr)/sizeof(*temp_pounds_loss_arr)); ++poundsIndex){
            switch(exerciseIndex){
                case 0:
                    tempCalorieDeficit = calculate_calorie_deficit(temp_pounds_loss_arr[poundsIndex], SEDENTARY_ACTIVITY_FACTOR);
                    break;
                case 1:
                    tempCalorieDeficit = calculate_calorie_deficit(temp_pounds_loss_arr[poundsIndex], MILD_ACTIVITY_FACTOR);
                    break;
                case 2:
                    tempCalorieDeficit = calculate_calorie_deficit(temp_pounds_loss_arr[poundsIndex], MODERATE_ACTIVITY_FACTOR);
                    break;
                case 3:
                    tempCalorieDeficit = calculate_calorie_deficit(temp_pounds_loss_arr[poundsIndex], HEAVY_ACTIVITY_FACTOR);
                    break;
            }

            /* First initialize inner map (lbs/month as key, calories deficit as value) */
            tempCalorieDeficitArr[poundsIndex] = tempCalorieDeficit;
            tempInnerMap.insert({temp_pounds_loss_arr[poundsIndex],tempCalorieDeficit});

        }
            /* Now take inner map and use it to insert element into exercise calorie map */

            std::map<std::string, std::map<int,double>>::iterator it = this->exercise_calories_map.find(temp_exercise_type_arr[exerciseIndex]);
            if(it != this->exercise_calories_map.end()){
                for(int i = 0; i < (sizeof(temp_pounds_loss_arr)/sizeof(*temp_pounds_loss_arr)); ++i){
                    (this->exercise_calories_map[temp_exercise_type_arr[exerciseIndex]]).find(temp_pounds_loss_arr[i])->second = tempCalorieDeficitArr[i];

                }

            }else{
                this->exercise_calories_map.insert({temp_exercise_type_arr[exerciseIndex], tempInnerMap});
            }

    }
}
