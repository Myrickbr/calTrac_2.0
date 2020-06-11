#include "../include/pinforesultshelper.h"
#include<string>
#include<cmath>
#include <iomanip>
#include <sstream>

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
        return "HEALTHY";
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

            std::ostringstream streamObj3;
            streamObj3 << std::fixed;

            // Set precision to 2 digits
            streamObj3 << std::setprecision(2);
            streamObj3 << totalWeightGainPounds;
            std::string weightGainString = streamObj3.str();

            healthyWeightStatement = "Gain " + weightGainString + " pounds";
            break;
        }
        case WeightStatus::Healthy:{
            healthyWeightStatement = "Stay the same!";
            break;
        }
        case WeightStatus::Overweight:{
            double weightInKGAfterWeightLoss = HEALTHY_WEIGHT_BMI_THRESHOLD * pow(currentHeightMeters,2.0);
            double weightInLbsAfterWeightLoss = weightInKGAfterWeightLoss * POUNDS_PER_KILOGRAM;
            double totalWeightLossPounds = currentWeightLbs - weightInLbsAfterWeightLoss;

            std::ostringstream streamObj3;
            streamObj3 << std::fixed;

            // Set precision to 2 digits
            streamObj3 << std::setprecision(2);
            streamObj3 << totalWeightLossPounds;
            std::string weightLossString = streamObj3.str();

            healthyWeightStatement = "Lose " + weightLossString + " pounds";
            break;
        }
        case WeightStatus::Obese:{
            double weightInKGAfterWeightLoss = HEALTHY_WEIGHT_BMI_THRESHOLD * pow(currentHeightMeters,2.0);
            double weightInLbsAfterWeightLoss = weightInKGAfterWeightLoss * POUNDS_PER_KILOGRAM;
            double totalWeightLossPounds = currentWeightLbs - weightInLbsAfterWeightLoss;

            std::ostringstream streamObj3;
            streamObj3 << std::fixed;

            // Set precision to 2 digits
            streamObj3 << std::setprecision(2);
            streamObj3 << totalWeightLossPounds;
            std::string weightLossString = streamObj3.str();

            healthyWeightStatement = "Lose " + weightLossString + " pounds";
            break;
        }
        case WeightStatus::Null:{
            healthyWeightStatement = "ERROR: DATA NOT COLLECTED PROPERLY";
            break;
        }

    }

    return healthyWeightStatement;

}

