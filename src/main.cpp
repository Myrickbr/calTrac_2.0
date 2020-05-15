#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include <QStackedWidget>
#include <iostream>
#include <string>
#include <QApplication>
#include <QDir>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QtCharts>
#include<QBrush>

QT_CHARTS_USE_NAMESPACE

void initStyleSheet()
{
    QFile file("stylesheets/stylesheets.css");

    if(!file.open(QIODevice::ReadOnly)){
        exit(0);
    }

    QTextStream in(&file);
    QString css = in.readAll();
    qApp->setStyleSheet(css);

    return;
}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    initStyleSheet();

    MainWindow w;
    w.show();
    return a.exec();
}
