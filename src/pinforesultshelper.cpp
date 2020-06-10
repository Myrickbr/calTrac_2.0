#include "../include/pinforesultshelper.h"
#include<string>
#include<cmath>

pInfoResultsHelper::pInfoResultsHelper()
{
    this->weightStatus = WeightStatus::Null;
}
const pInfoResultsHelper::WeightStatus & pInfoResultsHelper::getWeightStatus(){
    return this->weightStatus;
}
void pInfoResultsHelper::setWeightStatus(const pInfoResultsHelper::WeightStatus & ws){
    this->weightStatus = ws;
}
std::string pInfoResultsHelper::is_threshold(const double & bmi){

    if(bmi < UNDERWEIGHT_BMI_THRESHOLD){
        setWeightStatus(pInfoResultsHelper::WeightStatus::Underweight);
        return "UNDERWEIGHT";
    }else if(bmi < HEALTHY_WEIGHT_BMI_THRESHOLD){
        setWeightStatus(pInfoResultsHelper::WeightStatus::Healthy);
        return "HEALTHY WEIGHT";
    }else if(bmi < OVERWEIGHT_BMI_THRESHOLD){
        setWeightStatus(pInfoResultsHelper::WeightStatus::Overweight);
        return "OVERWEIGHT";
    }else{
        setWeightStatus(pInfoResultsHelper::WeightStatus::Obese);
        return "OBESE";
    }
}
std::string pInfoResultsHelper::get_healthy_weight_statement(double & currentWeightLbs, double & currentHeightfeet){
    double currentWeightKG = currentWeightLbs * KILOGRAMS_PER_POUND;
    double currentHeightMeters = currentHeightfeet * METERS_PER_FOOT;

    std::string healthyWeightStatement = "";

    switch(this->weightStatus){
        case WeightStatus::Underweight:{
            double weightInKGAfterWeightLoss = UNDERWEIGHT_BMI_THRESHOLD * pow(currentHeightMeters,2.0);
            double weightInLbsAfterWeightLoss = weightInKGAfterWeightLoss * POUNDS_PER_KILOGRAM;
            double totalWeightGainPounds = weightInLbsAfterWeightLoss - currentWeightLbs;
            healthyWeightStatement = "Gain " + std::to_string(totalWeightGainPounds) + "pounds";
            break;
        }
        case WeightStatus::Healthy:{
            healthyWeightStatement = "Do nothing, you are a healthy weight!";
            break;
        }
        case WeightStatus::Overweight:{
            double weightInKGAfterWeightLoss = HEALTHY_WEIGHT_BMI_THRESHOLD * pow(currentHeightMeters,2.0);
            double weightInLbsAfterWeightLoss = weightInKGAfterWeightLoss * POUNDS_PER_KILOGRAM;
            double totalWeightLossPounds = currentWeightLbs - weightInLbsAfterWeightLoss;
            healthyWeightStatement = "Lose " + std::to_string(totalWeightLossPounds) + "pounds";
            break;
        }
        case WeightStatus::Obese:{
            double weightInKGAfterWeightLoss = HEALTHY_WEIGHT_BMI_THRESHOLD * pow(currentHeightMeters,2.0);
            double weightInLbsAfterWeightLoss = weightInKGAfterWeightLoss * POUNDS_PER_KILOGRAM;
            double totalWeightLossPounds = currentWeightLbs - weightInLbsAfterWeightLoss;
            healthyWeightStatement = "Lose " + std::to_string(totalWeightLossPounds) + "pounds";
            break;
        }
        case WeightStatus::Null:{
            healthyWeightStatement = "ERROR: DATA NOT COLLECTED PROPERLY";
            break;
        }

    }

    return healthyWeightStatement;

}
