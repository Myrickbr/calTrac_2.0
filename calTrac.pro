QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    libs/src/circularprogress.cpp \
    libs/src/circularprogressplugin.cpp \
    libs/src/progresscircle.cpp \
    src/bmipercentilechart.cpp \
    src/calorieexercisechart.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/nutritiontracker.cpp \
    src/pinforesultshelper.cpp \
    src/userinformation.cpp

HEADERS += \
    include/bmipercentilechart.h \
    include/calorieexercisechart.h \
    include/mainwindow.h \
    include/nutritiontracker.h \
    include/pinforesultshelper.h \
    include/userinformation.h \
    libs/include/circularprogress.h \
    libs/include/circularprogressplugin.h \
    libs/include/progresscircle.h

FORMS += \
    forms/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/Resources.qrc

DISTFILES += \
    data/bmiPercentileDataFemale.txt \
    data/bmiPercentileDataMale.txt \
    data/testFile.csv \
    screenshots/personalInfo.gif \
    screenshots/projectClick.gif \
    screenshots/shadowBuildClick.gif \
    stylesheets/stylesheets.css
