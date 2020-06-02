#include "../include/calorieexercisechart.h"
#include <QtCharts>
#include <QtCore>
#include<QtGui>
#include<QMessageBox>
#include<QVariant>
#include<QBarSet>
#include<map>

using namespace QtCharts;

calorieExerciseChart::calorieExerciseChart()
{
    this->set_width_pixels(WIDTH_PIXELS);
    this->set_height_pixels(HEIGHT_PIXELS);
    this->chart = new QChart();
    this->series = new QBarSeries();
    this->categories = new QStringList();
    this->sedentarySet= new QBarSet("Sedentary");
    this->mildSet = new QBarSet("Mild");
    this->moderateSet = new QBarSet("Moderate");
    this->moderateSet = new QBarSet("Heavy");

    this->chart->setTitle("Weight Loss Chart");

    /* Set animation styles */
    this->chart->setAnimationOptions(QChart::AllAnimations);
    *this->categories << "Sedentary" << "Mild" << "Moderate" << "Heavy";
    QBarCategoryAxis * axis = new QBarCategoryAxis();
    axis->append(*categories);
    this->chart->createDefaultAxes();
    this->chart->setAxisX(axis, this->series);
    this->chart->legend()->setVisible(true);
    this->chart->legend()->setAlignment(Qt::AlignBottom);
}
const double & calorieExerciseChart::get_height_pixels(){
    return this->heightPixels;
}
const double & calorieExerciseChart::get_width_pixels(){
    return this->widthPixels;
}
QChart * calorieExerciseChart::get_chart(){
    return this->chart;
}
void calorieExerciseChart::set_height_pixels(const double &heightPX){
    this->heightPixels = heightPX;
}
void calorieExerciseChart::set_width_pixels(const double &widthPX){
    this->widthPixels = widthPX;
}
void calorieExerciseChart::update_chart(std::map<std::string,std::map<int,double>> & calorieExerciseMap){
    /* Use the calorie exercise map that was initialized and derived from user info object to create chart*/

    *this->sedentarySet << (calorieExerciseMap.find("Sedentary")->second).find(0)->second \
                        << (calorieExerciseMap.find("Sedentary")->second).find(1)->second \
                        << (calorieExerciseMap.find("Sedentary")->second).find(2)->second;

    *this->mildSet << (calorieExerciseMap.find("Mild")->second).find(0)->second \
                   << (calorieExerciseMap.find("Mild")->second).find(1)->second \
                   << (calorieExerciseMap.find("Mild")->second).find(2)->second;

    *this->moderateSet << (calorieExerciseMap.find("Moderate")->second).find(0)->second \
                       << (calorieExerciseMap.find("Moderate")->second).find(1)->second \
                       << (calorieExerciseMap.find("Moderate")->second).find(2)->second;

    *this->sedentarySet << (calorieExerciseMap.find("Heavy")->second).find(0)->second \
                        << (calorieExerciseMap.find("Heavy")->second).find(1)->second \
                        << (calorieExerciseMap.find("Heavy")->second).find(2)->second;

    this->series->append(sedentarySet);
    this->series->append(mildSet);
    this->series->append(moderateSet);
    this->series->append(sedentarySet);

    this->chart->addSeries(series);



}
