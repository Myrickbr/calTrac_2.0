#include <QtCore>
#include<QtGui>
#include<QMessageBox>
#include<QVariant>
#include <map>
#include <string>
#include "include/mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    /* Initialize instance variables */
    this->femaleChecked = false;
    this->maleChecked = false;

    /* Set up sliders */

    ui->setupUi(this);
    connect(ui->calculator_Weight_Slider, SIGNAL(valueChanged(int)), this, SLOT(calculate_Calories()));
    connect(ui->calculator_Height_Slider, SIGNAL(valueChanged(int)), this, SLOT(calculate_Calories()));
    connect(ui->calculator_Age_Slider, SIGNAL(valueChanged(int)), this, SLOT(calculate_Calories()));
    connect(ui->calculator_Exercise_Slider, SIGNAL(valueChanged(int)), this, SLOT(calculate_Calories()));
    connect(ui->male_Radio_Button, SIGNAL(clicked()), this, SLOT(calculate_Calories()));
    connect(ui->female_Radio_Button, SIGNAL(clicked()), this, SLOT(calculate_Calories()));

    connect(ui->weightSlider, SIGNAL(valueChanged(int)), this, SLOT(displayWeightValue()));
    connect(ui->ageSlider, SIGNAL(valueChanged(int)), this, SLOT(displayAgeValue()));
}
MainWindow::~MainWindow()
{
    delete ui;
}

//Getters and Setters
double MainWindow::getBMR()
{
    return this->BMR;
}
double MainWindow::getCalories(){
    return this->calories;
}
double MainWindow::getBodyWeightPounds()
{
    return this->body_Weight_Pounds;
}
double MainWindow::getHeightInInches()
{
    return this->height_In_Inches;
}
int MainWindow::getAgeInYears()
{
    return this->age_In_Years;
}
int MainWindow::getExerciseDays()
{
    return this->exercise_Days_Per_Week;
}

bool MainWindow::getIsFemale()
{
    return this->femaleChecked;
}

bool MainWindow::getIsMale()
{
    return this->maleChecked;
}
double MainWindow::getExerciseMapValue(int num)
{
    return this->exercise_Map[num];
}

void MainWindow::setBMR(double num)
{
    this->BMR = num;
}
void MainWindow::setCalories(double num)
{
    this->calories = num;
}
void MainWindow::setBodyWeightPounds(double num)
{
    this->body_Weight_Pounds = num;
}
void MainWindow::setHeightInches(double num)
{
    this->height_In_Inches = num;
}
void MainWindow::setAgeInYears(double num)
{
    this->age_In_Years = num;
}
void MainWindow::setExerciseDays(double num)
{
    this->exercise_Days_Per_Week = num;
}

void MainWindow::setExerciseMapValue(int num, double val)
{
    this->exercise_Map[num] = val;
}
void MainWindow::setMaleCheck(bool tOf){
    this->maleChecked = tOf;
}
void MainWindow::setFemaleCheck(bool tOf){
    this->femaleChecked = tOf;
}
// Here are the button click events...
// The stacked widget contains all the scenes for the application,
// we are resetting the index after pressing the corresponding button.
void MainWindow::on_dailyCalendarButton_clicked()
{
   ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_nutritionTrackerButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_personalOverviewButton_clicked()
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

void MainWindow::on_maleButton_clicked(){

    /* When male button is clicked, we will update the stylesheets for
       the male button and the female button (set back to grey)
    */

    QString maleButtonStyleSheet = "border-color: #5EA0EB; background-color: #D8EEFF";
    ui->maleButton->setStyleSheet(maleButtonStyleSheet);

    QString femaleButtonStyleSheet = "background-color: #F6F6F6;border: 1px solid rgba(112,112,112,0.5);";
    ui->femaleButton->setStyleSheet(femaleButtonStyleSheet);

    /* Set maleChecked to true and femaleChecked to false */

    this->setMaleCheck(true);
    this->setFemaleCheck(false);

}

void MainWindow::on_femaleButton_clicked(){

    /*When the female button is clicked, we will update the stylesheets for
      the female button and the male button (set back to grey)
    */

    QString femaleButtonStyleSheet = "border-color: #5EA0EB; background-color: #D8EEFF";
    ui->femaleButton->setStyleSheet(femaleButtonStyleSheet);

    QString maleButtonStyleSheet = "background-color: #F6F6F6;border: 1px solid rgba(112,112,112,0.5);";
    ui->maleButton->setStyleSheet(maleButtonStyleSheet);

    /* Set femaleChecked to true and maleChecked to false */

    this->setFemaleCheck(true);
    this->setFemaleCheck(false);

}


void MainWindow::displayWeightValue(){
    //Retrieve value from slider, convert to qstring
    int sliderValue = ui->weightSlider->value();

    QVariant var(sliderValue);
    QString valueAsString = var.toString();

    ui->weightShowBox->setText(valueAsString);
    ui->weightShowBox->repaint();
}
void MainWindow::displayAgeValue(){
    //Retrieve value from slider, convert to qstring
    int sliderValue = ui->ageSlider->value();

    QVariant var(sliderValue);
    QString valueAsString = var.toString();

    ui->ageShowBox->setText(valueAsString);
    ui->ageShowBox->repaint();

}

void MainWindow::calculate_Calories()
{
    //Collect metrics from the sliders

    setBodyWeightPounds(ui->calculator_Weight_Slider->value());
    setHeightInches(ui->calculator_Height_Slider->value());
    setAgeInYears(ui->calculator_Age_Slider->value());
    setExerciseDays(ui->calculator_Exercise_Slider->value());

    //Default to male is checked, but if female is checked set to true

    //setMale(true);
    //setFemale(false);

    if(ui->female_Radio_Button->isChecked())
    {
        //setFemale(true);
        //setMale(false);
    }

    if(1 == 1)
    {
        setBMR(66 + (6.3 * getBodyWeightPounds()) + (12.9 * getHeightInInches()) - (6.8 * getAgeInYears()));
    }else{
        setBMR(655 + (4.3 * getBodyWeightPounds()) + (4.7 * getHeightInInches()) - (4.7 * getAgeInYears()));
    }

    //Initialize exercise map values

    setExerciseMapValue(0,1.2);
    setExerciseMapValue(1,1.375);
    setExerciseMapValue(2,1.375);
    setExerciseMapValue(3,1.375);
    setExerciseMapValue(4,1.55);
    setExerciseMapValue(5,1.55);
    setExerciseMapValue(6,1.725);
    setExerciseMapValue(7,1.725);

    setCalories(getBMR() * getExerciseMapValue(getExerciseDays()));

    ui->calories_Per_Day_Label->display(getCalories());
}





