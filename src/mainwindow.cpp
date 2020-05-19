#include <QtCore>
#include<QtGui>
#include<QMessageBox>
#include<QVariant>
#include<QtCharts>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include "include/mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    /* Initialize instance variables */
    this->femaleChecked = false;
    this->maleChecked = false;
    this->bmiValues = NULL;

    this->userInfoObject;

    /* Set up sliders and chart */

    ui->setupUi(this);

    QChart * bmiChart = configureBMIChart();

    ui->bmiPercentileChart->setRenderHint(QPainter::Antialiasing);
    ui->bmiPercentileChart->setChart(bmiChart);



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

QChart * MainWindow::configureBMIChart(){

    /* Retrieve bmi percentile data from text file */

    this->bmiValues = read_bmi_text_file();
    QLineSeries *series = new QLineSeries();

    for(int i = 0; i < (BMI_PERCENTILE_CHART_SIZE); ++i){
        series->append(i+1, *(this->bmiValues + i));
    }

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->layout()->setContentsMargins(0, 0, 0, 0);
    chart->setBackgroundRoundness(0);
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Simple line chart example");

    return chart;
}

void MainWindow::calculate_BMI_percentile(){
    if(this->bmiValues == NULL){
        perror("BMI Values have not been read in yet!");
        this->bmiValues = read_bmi_text_file();
    }

    /* Iterate through bmi value array, once you hit a percentile/index
       that contains a value lower than the user's bmi, exit loop */

    for(int i = 0; i < (BMI_PERCENTILE_CHART_SIZE);++i){
        if(*(this->userInfoObject->get_bmi()) > *(this->bmiValues + i)){
            this->userInfoObject->set_bmi_percentile(i+1);
            break;
        }
    }

    /* If you reach this point, you have a bmi value above the 99th percentile */

    perror("The user's bmi is above 99th percentile!");
    this->userInfoObject->set_bmi_percentile(99);
    return;
}

double * MainWindow::read_bmi_text_file(){

    static double bmiValues [99];
    std::string currentLine;
    std::ifstream infile;
    infile.open("data/bmiPercentileData.txt");
    if(!infile)
    {
        perror("Text file for bmi data could not be opened!");
    }

    int index = 0;
    while(!infile.eof())
    {
        getline(infile,currentLine);
        bmiValues[index] = atof(currentLine.c_str());
        ++index;
    }
    infile.close();

    return bmiValues;
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





