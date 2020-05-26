#include "../include/bmipercentilechart.h"
#include<QtCharts>
#include <QtCore>
#include<QtGui>
#include<QMessageBox>
#include<QVariant>

using namespace QtCharts;

bmiPercentileChart::bmiPercentileChart()
{
    this->set_width_pixels(WIDTH_PIXELS);
    this->set_height_pixels(HEIGHT_PIXELS);
    this->chart = new QChart();
    this->series = new QPieSeries();

}
const double & bmiPercentileChart::get_height_pixels(){
    return this->heightPixels;
}
const double & bmiPercentileChart::get_width_pixels(){
    return this->widthPixels;
}
QChart * bmiPercentileChart::get_chart(){
    return this->chart;
}
void bmiPercentileChart::set_height_pixels(const double &heightPX){
    this->heightPixels = heightPX;
}
void bmiPercentileChart::set_width_pixels(const double &widthPX){
    this->widthPixels = widthPX;
}
void bmiPercentileChart::init_chart(){
    this->series->setHoleSize(0.35);
    this->series->append("Protein 4.2%", 4.2);

    this->series->append("Fat 15.6%", 15.6);

    this->series->append("Other 23.8%", 23.8);
    this->series->append("Carbs 56.4%", 56.4);

    this->chart->addSeries(series);
    this->chart->legend()->hide();
    this->chart->layout()->setContentsMargins(0, 0, 0, 0);
    this->chart->setBackgroundRoundness(0);
}
void bmiPercentileChart::update_chart(){

}
