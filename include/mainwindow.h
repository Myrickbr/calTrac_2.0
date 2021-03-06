#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QtCharts>
#include <../include/calorieexercisechart.h>
#include<../include/userinformation.h>
#include<../include/bmipercentilechart.h>
#include<../include/pinforesultshelper.h>
#include<../libs/include/circularprogress.h>
#include <../include/nutritiontracker.h>
#include<../libs/include/progresscircle.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /* Enumerations and Constants */
    enum CircularChartType {BmiPercentile, MaintainWeight, LoseFivePounds, loseTenPounds};
    const int BMI_PERCENTILE_CHART_SIZE = 99;
    const int MESSAGE_BOX_FIXED_WIDTH = 500;
    const int MESSAGE_BOX_FIXED_HEIGHT = 200;
    const int BMI_PERCENTILE_CHART_MAXIMUM = 100;
    const int CALORIE_CHARTS_MAXIMUM = 3500;
    const std::string MALE_BMI_DATA_FILENAME = "data/bmiPercentileDataMale.txt";
    const std::string FEMALE_BMI_DATA_FILENAME = "data/bmiPercentileDataFemale.txt";

    /* Constructors */

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /* Getters and Setters */
    double getBMR();
    double getCalories();
    double getBodyWeightPounds();
    double getHeightInInches();
    int getAgeInYears();
    int getExerciseDays();
    bool getIsFemale();
    bool getIsMale();
    double getExerciseMapValue(int);
    void setBMR(double num);
    void setCalories(double num);
    void setBodyWeightPounds(double num);
    void setHeightInches(double num);
    void setAgeInYears(double num);
    void setExerciseDays(double num);
    void setMaleCheck(bool);
    void setFemaleCheck(bool);
    void setExerciseMapValue(int num, double val);

    /* Other Functions */
    void configure_BMI_chart();
    void configure_calorie_exercise_chart();
    void configure_button_stylesheets();
    void calculate_BMI_percentile();
    void read_bmi_text_file(std::string maleFileName, std::string femaleFileName);
    bool check_user_input();
    void plot_user_point();
    void update_bmi_tags();
    void paint_circ_chart(CircularChartType chartType);
    void update_circular_calorie_charts();  
    void update_weight_loss_labels();
    void update_results_section();
    void toggle_weight_loss_view(bool viewFull);

private slots:

    void displayWeightValue();

    void displayAgeValue();

    void displayDaysExerciseValue();

    void updateHeightValue();


    void testUpdateIndex();

    void on_back_Button_Tracker_clicked();

    void on_back_Button_Calculator_clicked();

    void calculate_current_calorie_intake();

    void on_personalOverviewButton_clicked();

    void on_nutritionTrackerButton_clicked();

    void on_dailyCalendarButton_clicked();

    void on_maleButton_clicked();

    void on_femaleButton_clicked();

    void on_calculateResultsButton_clicked();

    void on_sedentaryButton_clicked();

    void on_mildButton_clicked();

    void on_moderateButton_clicked();

    void on_heavyButton_clicked();

    void on_meatButton_clicked();
    void on_dairyButton_clicked();
    void on_carbButton_clicked();
    void on_vegButton_clicked();
    void on_otherButton_clicked();
    void on_addButton_clicked();

    void on_clearButton_clicked();

private:
    Ui::MainWindow *ui;

    /* Instance variables */
    bool maleChecked;
    bool femaleChecked;
    double BMR; //This stands for Basal Metabolic Rate
    double calories;
    std::map<int, double> exercise_Map;
    double body_Weight_Pounds;
    double height_In_Inches;
    double age_In_Years;
    int exercise_Days_Per_Week;
    int totalCals = 0;
    double * bmiValuesMale;
    double * bmiValuesFemale;
    QChart * bmiResultsChart;

    userInformation * userInfoObject;
    bmiPercentileChart * bmiPChartObject;

    nutritionTracker * list;
    calorieExerciseChart * calorieExerciseObject;
    ProgressCircle * progressCircleObject;

};
#endif // MAINWINDOW_H
