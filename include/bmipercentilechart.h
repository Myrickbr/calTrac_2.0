#ifndef BMIPERCENTILECHART_H
#define BMIPERCENTILECHART_H


class bmiPercentileChart
{
public:
    /* Enumerations and Constants */

    /* Constructors */
    bmiPercentileChart();

    /* Getters and Setters */
    const double & get_height_pixels();
    const double & get_width_pixels();
    void set_height_pixels(double & heightPX);
    void set_width_pixels(double & widthPX);

    /* Other Functions */
    void init_chart();
    void display_chart();
    void update_chart();

private:
    double heightPixels;
    double widthPixels;

};

#endif // BMIPERCENTILECHART_H
