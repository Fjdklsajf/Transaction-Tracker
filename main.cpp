#include "loginwindow.h"
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QFile>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    LoginWindow w;
    w.show();

    return a.exec();
}
