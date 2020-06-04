#include <QtCore>
#include<QtGui>
#include<QMessageBox>
#include<QVariant>
#include<QtCharts>
#include<QPen>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include "include/mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    /* TODO: Move all initialization to their own functions */

    /* Initialize instance variables */
    this->bmiValuesMale = NULL;
    this->bmiValuesFemale = NULL;
    this->userInfoObject = new userInformation();
    this->bmiPChartObject = new bmiPercentileChart();
    this->calorieExerciseObject = new calorieExerciseChart();
    this->bmiResultsChart = new QChart();
    QWidget * circWidget = new QWidget();
    this->circularProgressObject = new CircularProgress(circWidget);
    /* Set up BMI Results Chart, BMI Percentile Chart, and Calorie Exercise Chart */

    ui->setupUi(this);

    this->configure_BMI_chart();
    ui->bmiResultsChart->setRenderHint(QPainter::Antialiasing);
    ui->bmiResultsChart->setChart(this->bmiResultsChart);

    this->bmiPChartObject->init_chart();
    QChart * bmiPercentileChart = bmiPChartObject->get_chart();

    ui->bmiPercentileChartView->setChart(bmiPercentileChart);

    configure_calorie_exercise_chart();

    /* Set weight loss button visibility to false */
    ui->sedentaryButton->setVisible(false);
    ui->mildButton->setVisible(false);
    ui->moderateButton->setVisible(false);
    ui->heavyButton->setVisible(false);

    /* Connect sliders to slots to display and update values from user info object */

    connect(ui->weightSlider, SIGNAL(valueChanged(int)), this, SLOT(displayWeightValue()));
    connect(ui->ageSlider, SIGNAL(valueChanged(int)), this, SLOT(displayAgeValue()));
    connect(ui->daysExerciseSlider, SIGNAL(valueChanged(int)), this, SLOT(displayDaysExerciseValue()));
    connect(ui->heightFeetBox, SIGNAL(currentTextChanged(QString)), this, SLOT(updateHeightValue()));
    connect(ui->heightInchesBox, SIGNAL(currentTextChanged(QString)), this, SLOT(updateHeightValue()));
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

/* Main Window Buttons/Sliders Events */

void MainWindow::on_maleButton_clicked(){

    /* When male button is clicked, we will update the stylesheets for
       the male button and the female button (set back to grey)
    */

    QString maleButtonStyleSheet = "border-color: #5EA0EB; background-color: #D8EEFF";
    ui->maleButton->setStyleSheet(maleButtonStyleSheet);

    QString femaleButtonStyleSheet = "background-color: #F6F6F6;border: 1px solid rgba(112,112,112,0.5);";
    ui->femaleButton->setStyleSheet(femaleButtonStyleSheet);

    /* Update male status in user info object */
    this->userInfoObject->set_gender(userInformation::Gender::Male);
}

void MainWindow::on_femaleButton_clicked(){

    /*When the female button is clicked, we will update the stylesheets for
      the female button and the male button (set back to grey)
    */

    QString femaleButtonStyleSheet = "border-color: #5EA0EB; background-color: #D8EEFF";
    ui->femaleButton->setStyleSheet(femaleButtonStyleSheet);

    QString maleButtonStyleSheet = "background-color: #F6F6F6;border: 1px solid rgba(112,112,112,0.5);";
    ui->maleButton->setStyleSheet(maleButtonStyleSheet);

    /* Update female status in user info object */
    this->userInfoObject->set_gender(userInformation::Gender::Female);
}

void MainWindow::on_calculateResultsButton_clicked()
{
    /* This function needs to calculate BMI/BMI percentile
       then update graphs and views. First check to make sure
       user info instance variables are not null */
    if(!check_user_input()){
        return;
    }

    /* Now that user has entered proper input, perform calculation.
       Then update graphs and other applicable views */

    calculate_BMI_percentile();
    ui->bmiValueLabel->setText(QString::number(this->userInfoObject->get_bmi()));
    ui->bmiPercentileLabel->setText(QString::number(this->userInfoObject->get_bmi_percentile()));
    plot_user_point();
    update_bmi_tags();

    /* Update Calorie Intake tab functions */

    this->userInfoObject->calculate_basal_metabolic_rate();
    this->userInfoObject->calculate_current_calorie_intake();
    update_circular_calorie_charts();

    /* Update Calorie/Exercise/Weight Loss Chart */
    /* Need to create new chart object to update chart */
    this->calorieExerciseObject = new calorieExerciseChart();
    this->userInfoObject->configure_calorie_map();
    this->calorieExerciseObject->update_chart(this->userInfoObject->get_exercise_calories_map());
    configure_calorie_exercise_chart();

    /* Set Weight Loss Buttons to Visible */
    ui->sedentaryButton->setVisible(true);
    ui->mildButton->setVisible(true);
    ui->moderateButton->setVisible(true);
    ui->heavyButton->setVisible(true);

}

/* Non Event Functions */

void MainWindow::displayWeightValue(){
    //Retrieve value from slider, convert to qstring
    int weightFromSlider = ui->weightSlider->value();

    QVariant var(weightFromSlider);
    QString valueAsString = var.toString();

    ui->weightShowBox->setText(valueAsString);
    ui->weightShowBox->repaint();

    /* Update weight value in user info object */
    this->userInfoObject->set_weight_pounds(&weightFromSlider);

}
void MainWindow::displayAgeValue(){
    /* Retrieve value from slider, convert to qstring */
    int ageFromSlider = ui->ageSlider->value();

    QVariant var(ageFromSlider);
    QString valueAsString = var.toString();

    ui->ageShowBox->setText(valueAsString);
    ui->ageShowBox->repaint();

    /* Update age value in user info object */
    this->userInfoObject->set_age_years(&ageFromSlider);
}

void MainWindow::displayDaysExerciseValue(){

    int daysExerciseFromSlider = ui->daysExerciseSlider->value();
    this->userInfoObject->set_days_exercise_per_week(&daysExerciseFromSlider);

}
void MainWindow::updateHeightValue(){

    this->userInfoObject->set_height_inches(ui->heightInchesBox->currentIndex());
    this->userInfoObject->set_height_feet((ui->heightFeetBox->currentIndex()+1));
}
void MainWindow::update_bmi_tags(){
    /* First update percentile tag based on the selected gender */
    switch(this->userInfoObject->get_gender()){
        case userInformation::Gender::Male: {
            QString maleStyleSheet = "margin-left: 10px; border-radius: 25px; background: #D8EEFF; color: #4A0C46;";
            ui->bmiPercentileGenderIndicator->setStyleSheet(maleStyleSheet);
            break;
        }
        case userInformation::Gender::Female: {
            QString femaleStyleSheet = "margin-left: 10px; border-radius: 25px; background: #FED8FF; color: #4A0C46;";
            ui->bmiPercentileGenderIndicator->setStyleSheet(femaleStyleSheet);
            break;
        }
        case userInformation::Gender::Null: {
            perror("No Gender was selected when button was pressed!");
            break;
        }
    }

    /* Next update bmi value symbol (indicates low, average, or high) */


}
void MainWindow::update_circular_calorie_charts(){

    this->circularProgressObject->setValue(1000);
}
void MainWindow::update_weight_loss_labels(){

}
void MainWindow::configure_BMI_chart(){

    /* Retrieve bmi percentile data from text file */

    read_bmi_text_file(MALE_BMI_DATA_FILENAME, FEMALE_BMI_DATA_FILENAME);
    double valMale = *(this->bmiValuesMale + 10);
    double valFemale = *(this->bmiValuesFemale + 10);

    QLineSeries *seriesMale = new QLineSeries();
    QLineSeries *seriesFemale = new QLineSeries();

    for(int i = 0; i < (BMI_PERCENTILE_CHART_SIZE); ++i){
        seriesMale->append(i+1, *(this->bmiValuesMale + i));
    }    
    for(int i = 0; i < (BMI_PERCENTILE_CHART_SIZE); ++i){
        seriesFemale->append(i+1, *(this->bmiValuesFemale + i));
    }

    // Customize chart title
    QFont font("Candara", 12, QFont::Bold);
    this->bmiResultsChart->setTitleFont(font);
    this->bmiResultsChart->setTitle("Customchart example");

    /* Custom grid line */
    QCategoryAxis *axisX = new QCategoryAxis();
    QCategoryAxis *axisY = new QCategoryAxis();

    // Customize axis label font
    QFont labelsFont;
    labelsFont.setPixelSize(12);
    axisX->setLabelsFont(labelsFont);
    axisY->setLabelsFont(labelsFont);

    // Customize axis colors
    QPen axisPen(QRgb(0xd18952));
    axisPen.setWidth(2);
    axisX->setLinePen(axisPen);
    axisY->setLinePen(axisPen);

    // Customize axis label colors
    QBrush axisBrush(Qt::white);
    axisX->setLabelsBrush(axisBrush);
    axisY->setLabelsBrush(axisBrush);

    // Customize grid lines and shades
    axisX->setGridLineVisible(false);
    axisY->setGridLineVisible(false);
    axisY->setShadesPen(Qt::NoPen);
    axisY->setShadesBrush(QBrush(QColor(0x99, 0xcc, 0xcc, 0x55)));
    axisY->setShadesVisible(true);

    axisY->setMin(0);
    axisY->setMax(40);
    axisX->setMin(0);
    axisX->setMax(100);

    QFont serifFont("Candara", 16, QFont::Bold);
    //axisX->setLabelsFont(serifFont);
    //axisY->setLabelsFont(serifFont);

    this->bmiResultsChart->setAnimationOptions(QChart::AllAnimations);
    this->bmiResultsChart->addAxis(axisX, Qt::AlignBottom);
    this->bmiResultsChart->addAxis(axisY, Qt::AlignLeft);
    this->bmiResultsChart->legend()->hide();
    this->bmiResultsChart->layout()->setContentsMargins(0, 0, 0, 0);
    this->bmiResultsChart->setBackgroundRoundness(0);
    this->bmiResultsChart->addSeries(seriesMale);
    this->bmiResultsChart->addSeries(seriesFemale);
    this->bmiResultsChart->createDefaultAxes();
    this->bmiResultsChart->setTitle("BMI Percentile Chart");
}
void MainWindow::configure_calorie_exercise_chart(){

    ui->calorieExerciseChart->setChart(this->calorieExerciseObject->get_chart());
    ui->calorieExerciseChart->setRenderHint(QPainter::Antialiasing);
    QPalette pal = qApp->palette();
    pal.setColor(QPalette::Window, QRgb(0xffffff));
    pal.setColor(QPalette::WindowText, QRgb(0x404040));
    qApp->setPalette(pal);

}

void MainWindow::calculate_BMI_percentile(){
    if(this->bmiValuesMale == NULL || this->bmiValuesFemale == NULL){
        perror("BMI Values have not been read in yet!");
        read_bmi_text_file(MALE_BMI_DATA_FILENAME, FEMALE_BMI_DATA_FILENAME);
    }

    /* Iterate through bmi value array, once you hit a percentile/index
       that contains a value lower than the user's bmi, exit loop */

    double calculatedBMI = this->userInfoObject->calculate_BMI();
    this->userInfoObject->set_bmi(calculatedBMI);

    for(int i = 0; i < (BMI_PERCENTILE_CHART_SIZE);++i){

        switch(this->userInfoObject->get_gender()){
            case userInformation::Gender::Male:
                if(this->userInfoObject->get_bmi() < *(this->bmiValuesMale + i)){
                    double valMale = *(this->bmiValuesMale + i);
                    this->userInfoObject->set_bmi_percentile(i+1);
                    return;
                }
                break;
            case userInformation::Gender::Female:
                if(this->userInfoObject->get_bmi() < *(this->bmiValuesFemale + i)){
                    double valfemale = *(this->bmiValuesFemale + i);
                    this->userInfoObject->set_bmi_percentile(i+1);
                    return;
                }
                break;
        }
    }

    /* If you reach this point, you have a bmi value above the 99th percentile */

    perror("The user's bmi is above 99th percentile!");
    this->userInfoObject->set_bmi_percentile(99);
    return;
}

void MainWindow::read_bmi_text_file(std::string maleFileName, std::string femaleFileName){

    static double bmiValuesFemaleArr [99];
    static double bmiValuesMaleArr [99];
    std::string currentLine;
    std::ifstream infile;
    infile.open(maleFileName);
    if(!infile)
    {
        perror("Text file for bmi data could not be opened!");
    }

    int index = 0;
    while(!infile.eof())
    {
        getline(infile,currentLine);
        bmiValuesMaleArr[index] = atof(currentLine.c_str());
        ++index;
    }
    infile.close();

    infile.open(femaleFileName);
    if(!infile)
    {
        perror("Text file for bmi data could not be opened!");
    }

    int indexFemale = 0;
    while(!infile.eof())
    {
        getline(infile,currentLine);
        bmiValuesFemaleArr[indexFemale] = atof(currentLine.c_str());
        ++indexFemale;
    }
    infile.close();

    /* Now assign male and female pointers to corresponding arrays */
    this->bmiValuesMale = bmiValuesMaleArr;
    this->bmiValuesFemale = bmiValuesFemaleArr;
}

bool MainWindow::check_user_input(){
    /* Goal of this function is to make sure user input is a legitimate value.
       If not, send a message to the user telling them to add corresponding info. */
    QMessageBox messageBox;

    if(this->userInfoObject->get_weight_pounds() < 0){
        messageBox.critical(0,"Error","You must enter a valid weight!");
        messageBox.setFixedSize(MESSAGE_BOX_FIXED_WIDTH,MESSAGE_BOX_FIXED_HEIGHT);
        return false;
    }else if(this->userInfoObject->get_age_years() < 0){
        messageBox.critical(0,"Error","You must enter a valid age!");
        messageBox.setFixedSize(MESSAGE_BOX_FIXED_WIDTH,MESSAGE_BOX_FIXED_HEIGHT);
        return false;
    }else if(this->userInfoObject->get_gender() == userInformation::Gender::Null){
        messageBox.critical(0,"Error","You must enter a valid gender!");
        messageBox.setFixedSize(MESSAGE_BOX_FIXED_WIDTH,MESSAGE_BOX_FIXED_HEIGHT);
        return false;
    }

    return true;
}
void MainWindow::plot_user_point(){
    /* This function plots the user bmi point on the bmi results chart */

    QScatterSeries * userPoint = new QScatterSeries();
    double xCoord = this->userInfoObject->get_bmi_percentile();
    double yCoord = this->userInfoObject->get_bmi();
    userPoint->append(20,20);
    //userPoint->append(20,30);
    //userPoint->append(20,10);
    userPoint->append(15,15);
    userPoint->setColor(Qt::darkBlue);
    QPen pen(Qt::darkBlue,2);
    userPoint->setPen(pen);

    this->bmiResultsChart->addSeries(userPoint);
}
void MainWindow::calculate_current_calorie_intake()
{
    /* Calculate estimated calorie intake for individual */
    /* To perform this calculation, use Harris-Benedict Equation */

    this->userInfoObject->calculate_basal_metabolic_rate();
}









