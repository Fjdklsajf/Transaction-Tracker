/******************************************************************************
 *  AUTHOR          : Zhongming Su
 *  DATE CREATED    : August 16, 2021
 ******************************************************************************/
#include "loginwindow.h"
#include <QApplication>
#include <QDebug>
/******************************************************************************
 *
 * Transaction Tracker
 *_____________________________________________________________________________
 * A program with friendly user interface to keep tracker of all income and
 *   expense transactions.
 *_____________________________________________________________________________
 * Input:
 *  General input from mouse and keyboard
 *
 * Output:
 *  LoginWindow: Login dialog for the application
 *  MainWindow: Main window to add, edit, and remove transactions and other services
 *  TransactionWindow: A dialog that allows user to add or edit a transaction
 *  UsersWindow: A dialog that can be used to add or remove users for login
 ******************************************************************************/

int main(int argc, char *argv[]) {
    qDebug() << "/********************************************************";
    qDebug() << " Programmed by: Zhongming Su";
    qDebug() << " Program title: Transaction Tracker";
    qDebug() << " Date created : August 16, 2021";
    qDebug() << " ********************************************************/\n";

    QApplication a(argc, argv);
    LoginWindow w;
    w.show();

    return a.exec();
}
