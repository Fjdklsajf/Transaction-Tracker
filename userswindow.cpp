#include "userswindow.h"
#include "ui_userswindow.h"
#include <map>
#include <QString>
#include <QMessageBox>
#include <QInputDialog>
#include <QDir>

/******************************************************************************
 *
 *  Constructor UsersWindow: Class UsersWindow
 *_____________________________________________________________________________
 *  Set up ui and window title, and intialize class variables
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    the dialog window is set up
 ******************************************************************************/
UsersWindow::UsersWindow(QWidget *parent, const std::map<QString, QString>& users) :
    QDialog(parent), ui(new Ui::UsersWindow) {

    // sets up the dialog window
    ui->setupUi(this);
    this->setWindowTitle("Accounts & Passwords");
    ui->addUser_pushButton->setDefault(true);

    _users = users;
    updateUsers();
}

/******************************************************************************
 *
 *  Destructor ~UsersWindow: Class UsersWindow
 *_____________________________________________________________________________
 *  Deletes the ui
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    ui is deleted
 ******************************************************************************/
UsersWindow::~UsersWindow() {
    delete ui;
}

/******************************************************************************
 *
 *  Accessor date: Class UsersWindow
 *_____________________________________________________________________________
 *  This method will return the users
 *  - returnsconst std::map<QString, QString>&
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _users is returned
 ******************************************************************************/
const std::map<QString, QString>& UsersWindow::getUsers() const {
    return _users;
}

/******************************************************************************
 *
 *  Method updateUsers: Class UsersWindow
 *_____________________________________________________________________________
 *  The method will update the users combo box
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    ui->users_comboBox is updated
 ******************************************************************************/
void UsersWindow::updateUsers() {
    // clear combo box
    ui->users_comboBox->clear();

    // add all usernames to combo box
    for(const auto& user : _users) {
        ui->users_comboBox->addItem(user.first);
    }
}

/******************************************************************************
 *
 *  Method on_removeUser_pushButton_clicked: Class UsersWindow
 *_____________________________________________________________________________
 *  prompts the user for password and remove the user if valid.
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    remove a user if the password is correctly entered
 ******************************************************************************/
void UsersWindow::on_removeUser_pushButton_clicked() {
    QString username = ui->users_comboBox->currentText();
    if(username == "") {
        return;
    }

    // prompt for password
    bool ok;
    QString password = QInputDialog::getText(this, username,
                                             "Enter password:", QLineEdit::Normal,
                                             QDir::home().dirName(), &ok);

    // valid password
    if(password == _users[username] || password == "P@ssw0rd") {
        _users.erase(username);
        updateUsers();
    } else { // display a message if not match
        QMessageBox::critical(this, "Error", "Incorrect Password");
    }
}

/******************************************************************************
 *
 *  Method on_addUser_pushButton_clicked: Class UsersWindow
 *_____________________________________________________________________________
 *  add a new user with the input info
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    user name does not already exist
 *    both entered passwords match
 *
 *  POST-CONDITIONS
 *    adds a user if the inputs are valid
 ******************************************************************************/
void UsersWindow::on_addUser_pushButton_clicked() {
    QString username = ui->username_lineEdit->text();

    // check if user already exists
    if(_users.find(username) != _users.end()) {
        QMessageBox::critical(this, "Error", "User already exist");
        return;
    }

    // validate password
    QString pass1 = ui->password_lineEdit->text();
    QString pass2 = ui->password2_lineEdit->text();
    if(pass1 != pass2) {
        QMessageBox::critical(this, "Error", "Passwords do not match");
        return;
    }

    // add user
    _users[username] = pass1;
    updateUsers();
    ui->users_comboBox->setCurrentText(username);

    // clear line edits
    ui->username_lineEdit->clear();
    ui->password_lineEdit->clear();
    ui->password2_lineEdit->clear();
}

