#ifndef CALORIEEXERCISECHART_H
#define CALORIEEXERCISECHART_H

#include <QtCharts>

using namespace QtCharts;

class calorieExerciseChart
{
public:
    /* Enumerations and Constants */
    const double HEIGHT_PIXELS = 250.0;
    const double WIDTH_PIXELS = 450.0;

    /* Constructors */
    calorieExerciseChart();

    /* Getters and Setters */
    const double & get_height_pixels();
    const double & get_width_pixels();
    QChart * get_chart();
    void set_height_pixels(const double & heightPX);
    void set_width_pixels(const double & widthPX);

    /* Other Functions */
    void update_chart(std::map<std::string,std::map<int,double>> &);

private:
    double heightPixels;
    double widthPixels;
    QChart * chart;
    QBarSeries * series;
    QStringList * categories;
    QBarSet * noPoundLossSet;
    QBarSet * fivePoundLossSet;
    QBarSet * tenPoundLossSet;

};

#endif // CALORIEEXERCISECHART_H
