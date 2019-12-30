#include <QtCore>
#include<QtGui>
#include<QMessageBox>
#include <map>
#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->calculator_Weight_Slider, SIGNAL(valueChanged(int)), this, SLOT(calculate_Calories()));
    connect(ui->calculator_Height_Slider, SIGNAL(valueChanged(int)), this, SLOT(calculate_Calories()));
    connect(ui->calculator_Age_Slider, SIGNAL(valueChanged(int)), this, SLOT(calculate_Calories()));
    connect(ui->calculator_Exercise_Slider, SIGNAL(valueChanged(int)), this, SLOT(calculate_Calories()));
    connect(ui->male_Radio__Button, SIGNAL(isPressed()), this, SLOT(calculate_Calories()));
    connect(ui->female_Radio_Button, SIGNAL(isPressed()), this, SLOT(calculate_Calories()));
}
MainWindow::~MainWindow()
{
    delete ui;
}

// Here are the button click events...
// The stacked widget contains all the scenes for the application,
// we are resetting the index after pressing the corresponding button.
void MainWindow::on_instructions_Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_tracker_Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_calorie_Calculator_Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_back_Button_Instructions_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_back_Button_Tracker_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_back_Button_Calculator_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::calculate_Calories()
{
    double BMR = 0.0;
    double calories = 0;
    std::map<int, double> exercise_Map;
    double body_Weight_Pounds = ui->calculator_Weight_Slider->value();
    double height_In_Inches = ui->calculator_Height_Slider->value();
    double age_In_Years = ui->calculator_Age_Slider->value();
    double exercise_Days_Per_Week = ui->calculator_Exercise_Slider->value();

    bool is_Male = true;
    bool is_Female = false;

    if(ui->female_Radio_Button->isChecked())
    {
        is_Female = true;
        is_Male = false;
    }

    if(is_Male)
    {
        BMR = 66 + (6.3 * body_Weight_Pounds) + (12.9 * height_In_Inches) - (6.8 * age_In_Years);
    }else{
        BMR = 655 + (4.3 * body_Weight_Pounds) + (4.7 * height_In_Inches) - (4.7 * age_In_Years);
    }

    exercise_Map[0] = 1.2;
    exercise_Map[1] = 1.375;
    exercise_Map[2] = 1.375;
    exercise_Map[3] = 1.375;
    exercise_Map[4] = 1.55;
    exercise_Map[5] = 1.55;
    exercise_Map[6] = 1.725;
    exercise_Map[7] = 1.725;

    calories = BMR * exercise_Map[exercise_Days_Per_Week];

    ui->calories_Per_Day_Label->display(calories);
}
