#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QtCharts>
#include<../include/userinformation.h>
#include<../include/bmipercentilechart.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /* Enumerations and Constants */
    const int BMI_PERCENTILE_CHART_SIZE = 99;
    const int MESSAGE_BOX_FIXED_WIDTH = 500;
    const int MESSAGE_BOX_FIXED_HEIGHT = 200;
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
    void calculate_BMI_percentile();
    void read_bmi_text_file(std::string maleFileName, std::string femaleFileName);
    bool check_user_input();
    void plot_user_point();


private slots:

    void on_back_Button_Tracker_clicked();

    void on_back_Button_Calculator_clicked();

    void calculate_Calories();

    void displayWeightValue();

    void displayAgeValue();

    void displayDaysExerciseValue();

    void on_personalOverviewButton_clicked();

    void on_nutritionTrackerButton_clicked();

    void on_dailyCalendarButton_clicked();

    void on_maleButton_clicked();

    void on_femaleButton_clicked();

    void on_calculateResultsButton_clicked();


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
    double * bmiValuesMale;
    double * bmiValuesFemale;
    QChart * bmiResultsChart;

    userInformation * userInfoObject;
    bmiPercentileChart * bmiPChartObject;

};
#endif // MAINWINDOW_H
