QT       += core gui
QT += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    category.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    tracker.cpp \
    transaction.cpp \
    transactionwindow.cpp \
    userswindow.cpp

HEADERS += \
    category.h \
    loginwindow.h \
    mainwindow.h \
    tracker.h \
    transaction.h \
    transactionwindow.h \
    userswindow.h

FORMS += \
    loginwindow.ui \
    mainwindow.ui \
    transactionwindow.ui \
    userswindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
