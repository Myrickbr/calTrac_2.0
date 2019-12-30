#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_instructions_Button_clicked();

    void on_tracker_Button_clicked();

    void on_calorie_Calculator_Button_clicked();

    void on_back_Button_Instructions_clicked();

    void on_back_Button_Tracker_clicked();

    void on_back_Button_Calculator_clicked();

    void calculate_Calories();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
