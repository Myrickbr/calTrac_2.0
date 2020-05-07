#include "include/mainwindow.h"
#include<QStackedWidget>
#include <iostream>
#include <string>

#include <QApplication>
#include <QDir>
#include <QDebug>
#include <QFile>
#include <QTextStream>

void initStyleSheet()
{
    QFile file("stylesheets/stylesheets.css");

    if(!file.open(QIODevice::ReadOnly)){
        exit(0);
    }

    QTextStream in(&file);
    QString css = in.readAll();
    qApp->setStyleSheet(css);
    qApp->setFont(QFont("Times", 9));

    return;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QString blah =  QDir::currentPath();
    //qDebug() << blah;
    //std::cout << "current directory   " << blah.toStdString();
    initStyleSheet();

    MainWindow w;
    w.show();
    return a.exec();
}
