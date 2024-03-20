QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    fin_deposit.cpp \
    finances.cpp \
    main.cpp \
    mainmenu.cpp \
    qcustomplot.cpp \
    smartcalc.cpp \
    ../s21_smartcalc.c \
    ../s21_stack.c \
    ../s21_finance.c \
    ../s21_additional.c

HEADERS += \
    fin_deposit.h \
    finances.h \
    mainmenu.h \
    qcustomplot.h \
    smartcalc.h \
    ../s21_smartcalc.h \
    ../s21_finance.h \
    ../s21_additional.h

FORMS += \
    fin_deposit.ui \
    finances.ui \
    mainmenu.ui \
    smartcalc.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
