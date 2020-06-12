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
    this->noPoundLossSet= new QBarSet("Maintain");
    this->fivePoundLossSet = new QBarSet("Five Lbs Loss");
    this->tenPoundLossSet = new QBarSet("Ten Lbs Loss");
    this->labelFont = new QFont("Candara");

    /* Set animation styles */

    this->chart->setAnimationOptions(QChart::AllAnimations);
    *this->categories << "Sedentary" << "Mild" << "Moderate" << "Heavy";
    QBarCategoryAxis * axisX = new QBarCategoryAxis();
    QValueAxis * axisY = new QValueAxis();

    labelFont->setPointSize(LABEL_FONT_SIZE);
    axisX->setLabelsFont(*labelFont);
    axisY->setRange(0, 3500);
    axisY->setMin(0);
    axisY->setMax(3500);
    axisY->setTickCount(7);

    axisX->append(*categories);
    this->chart->setAxisX(axisX);
    this->chart->setAxisY(axisY);
    this->chart->legend()->setVisible(true);
    this->chart->legend()->setAlignment(Qt::AlignBottom);
    this->series->attachAxis(axisX);
    this->series->attachAxis(axisY);
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

    *this->noPoundLossSet << (calorieExerciseMap.find("Sedentary")->second).find(0)->second \
                        << (calorieExerciseMap.find("Mild")->second).find(0)->second \
                        << (calorieExerciseMap.find("Moderate")->second).find(0)->second \
                        << (calorieExerciseMap.find("Heavy")->second).find(0)->second;

    *this->fivePoundLossSet << (calorieExerciseMap.find("Sedentary")->second).find(5)->second \
                            << (calorieExerciseMap.find("Mild")->second).find(5)->second \
                            << (calorieExerciseMap.find("Moderate")->second).find(5)->second \
                            << (calorieExerciseMap.find("Heavy")->second).find(5)->second;

    *this->tenPoundLossSet << (calorieExerciseMap.find("Sedentary")->second).find(10)->second \
                           << (calorieExerciseMap.find("Mild")->second).find(10)->second \
                           << (calorieExerciseMap.find("Moderate")->second).find(10)->second \
                           << (calorieExerciseMap.find("Heavy")->second).find(10)->second;

    double calVal0 = (calorieExerciseMap.find("Sedentary")->second).find(0)->second;
    double calVal1 = (calorieExerciseMap.find("Mild")->second).find(0)->second;

    QColor noPoundLossColor(3, 132, 252);
    QColor fivePoundLossColor(52, 153, 247);
    QColor tenPoundLossColor(74, 168, 255);

    this->noPoundLossSet->setColor(noPoundLossColor);
    this->fivePoundLossSet->setColor(fivePoundLossColor);
    this->tenPoundLossSet->setColor(tenPoundLossColor);

    this->series->append(noPoundLossSet);
    this->series->append(fivePoundLossSet);
    this->series->append(tenPoundLossSet);
    this->chart->createDefaultAxes();

    this->chart->addSeries(series);

}
