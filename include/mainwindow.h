#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QtCharts>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

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
    QChart * configureBMIChart();


private slots:

    void on_back_Button_Tracker_clicked();

    void on_back_Button_Calculator_clicked();

    void calculate_Calories();

    void displayWeightValue();

    void displayAgeValue();

    void on_personalOverviewButton_clicked();

    void on_nutritionTrackerButton_clicked();

    void on_dailyCalendarButton_clicked();

    void on_maleButton_clicked();

    void on_femaleButton_clicked();


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

};
#endif // MAINWINDOW_H
