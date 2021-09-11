#ifndef USERSWINDOW_H
#define USERSWINDOW_H

#include <QDialog>
#include <QString>
#include <map>

namespace Ui {
    class UsersWindow;
}

class UsersWindow : public QDialog {
    Q_OBJECT

  public:
    /*******************************
     ** CONSTRUCTOR & DESCTRUCTOR **
     *******************************/
    explicit UsersWindow(QWidget *parent = nullptr,
             const std::map<QString, QString>& users = std::map<QString, QString>());
    ~UsersWindow();

    /***************
     ** ACCESSORS **
     ***************/
    const std::map<QString, QString>& getUsers() const;

    /*************
     ** METHODS **
     *************/
    void updateUsers();

  private slots:
    /*********************
     ** Slots & Signals **
     *********************/
    void on_removeUser_pushButton_clicked();
    void on_addUser_pushButton_clicked();

private:
    Ui::UsersWindow *ui;
    std::map<QString, QString> _users;
};

#endif // USERSWINDOW_H

/******************************************************************************
 *  UsersWindow Class
 *    A dialog window with widgets to add or remvoe users by username and password
 ******************************************************************************/


/******************************
 ** CONSTRUCTOR & DESTRUCTOR **
 ******************************/

/******************************************************************************
 *  explicit UsersWindow(QWidget *parent = nullptr,
 *           const std::map<QString, QString>& users = std::map<QString, QString>());
 *    Constructor; Set up ui and window title, and intialize class variables
 *    Parameters: QWidget *, const std::map<QString, QString>&
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  ~UsersWindow();
 *    Destructor; Deleted the ui
 *    Parameters: none
 *    Return: void
 ******************************************************************************/


/***************
 ** ACCESSORS **
 ***************/

/******************************************************************************
 *  const std::map<QString, QString>& getUsers() const;
 *
 *    Accessor; This method will return _users
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: const std::map<QString, QString>&
 ******************************************************************************/


/*************
 ** METHODS **
 *************/

/******************************************************************************
 *  void updateUsers();
 *
 *    The method will update the users combo box
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/


/*********************
 ** Slots & Signals **
 *********************/

/******************************************************************************
 *  void on_removeUser_pushButton_clicked();
 *
 *    prompts the user for password and remove the user if valid.
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void on_addUser_pushButton_clicked();
 *
 *    add a new user with the input info
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/
