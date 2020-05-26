#ifndef BMIPERCENTILECHART_H
#define BMIPERCENTILECHART_H

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

using namespace QtCharts;

class bmiPercentileChart
{
public:
    /* Enumerations and Constants */
    const double HEIGHT_PIXELS = 120.0;
    const double WIDTH_PIXELS = 150.0;

    /* Constructors */
    bmiPercentileChart();

    /* Getters and Setters */
    const double & get_height_pixels();
    const double & get_width_pixels();
    QChart * get_chart();
    void set_height_pixels(const double & heightPX);
    void set_width_pixels(const double & widthPX);

    /* Other Functions */
    void init_chart();
    void display_chart();
    void update_chart();

private:
    double heightPixels;
    double widthPixels;

    QChart * chart;
    QPieSeries * series;


};

#endif // BMIPERCENTILECHART_H
