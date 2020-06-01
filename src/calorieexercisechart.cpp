#include "../include/calorieexercisechart.h"
#include <QtCharts>
#include <QtCore>
#include<QtGui>
#include<QMessageBox>
#include<QVariant>
#include<QBarSet>

using namespace QtCharts;

calorieExerciseChart::calorieExerciseChart()
{
    this->set_width_pixels(WIDTH_PIXELS);
    this->set_height_pixels(HEIGHT_PIXELS);
    this->chart = new QChart();
    this->series = new QBarSeries();
    this->sedentarySet= new QBarSet("Sedentary");
    this->mildSet = new QBarSet("Mild");
    this->moderateSet = new QBarSet("Moderate");
    this->moderateSet = new QBarSet("Heavy");

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
void calorieExerciseChart::init_chart(){

}
