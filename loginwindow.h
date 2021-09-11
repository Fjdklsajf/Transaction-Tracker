#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "mainwindow.h"
#include "tracker.h"
#include <QString>
#include <QDialog>
#include <map>

namespace Ui {
    class LoginWindow;
}

class LoginWindow : public QDialog {
    Q_OBJECT

  public:
    /*******************************
     ** CONSTRUCTOR & DESCTRUCTOR **
     *******************************/
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

    /*************
     ** METHODS **
     *************/
    void readUsersFile();
    void saveUsersFile(const std::map<QString, QString>& users);
    void saveToFiles(const Tracker& tracker, QString path);

  private slots:
    /*********************
     ** Slots & Signals **
     *********************/
    void on_login_pushButton_clicked();

  private:
    Ui::LoginWindow *ui;
    MainWindow *mainWindow;
    std::map<QString, QString> _users;
};

#endif // LOGINWINDOW_H

/******************************************************************************
 *  LoginWindow Class
 *    A dialog window with widgets that asks for Username and Passwords
 ******************************************************************************/


/******************************
 ** CONSTRUCTOR & DESTRUCTOR **
 ******************************/

/******************************************************************************
 *  explicit LoginWindow(QWidget *parent = nullptr);
 *    Constructor; Set up ui and window title, and reads users file
 *    Parameters: QWidget *
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  ~LoginWindow();
 *    Destructor; Deleted the ui
 *    Parameters: none
 *    Return: void
 ******************************************************************************/


/*************
 ** METHODS **
 *************/

/******************************************************************************
 *  void readUsersFile();
 *
 *    This method will read each usernames and passwords from uers.txt file
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void saveUsersFile(const std::map<QString, QString>& users);
 *
 *    This method will write users information to the users.txt file
 * ----------------------------------------------------------------------------
 *    Parameters: const std::map<QString, QString>&
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void saveToFiles(const Tracker& tracker, QString path);
 *
 *    This method will write Tracker information into files in the given path
 *      Transasctions of different Categories are stored in different files
 * ----------------------------------------------------------------------------
 *    Parameters: const Tracker&, QString
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/


/*********************
 ** Slots & Signals **
 *********************/

/******************************************************************************
 *  void on_login_pushButton_clicked();
 *
 *    checks inputted login information, go to main window if valid
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/
