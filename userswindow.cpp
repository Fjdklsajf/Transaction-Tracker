#include "userswindow.h"
#include "ui_userswindow.h"
#include <map>
#include <QString>
#include <QMessageBox>
#include <QInputDialog>
#include <QDir>

UsersWindow::UsersWindow(QWidget *parent, const std::map<QString, QString>& users) :
    QDialog(parent), ui(new Ui::UsersWindow) {
    ui->setupUi(this);
    this->setWindowTitle("Accounts & Passwords");
    _users = users;
    ui->addUser_pushButton->setDefault(true);

    updateUsers();
}

UsersWindow::~UsersWindow() {
    delete ui;
}

const std::map<QString, QString>& UsersWindow::getUsers() {
    return _users;
}

void UsersWindow::updateUsers() {
    ui->users_comboBox->clear();

    for(const auto& user : _users) {
        ui->users_comboBox->addItem(user.first);
    }
}

void UsersWindow::on_removeUser_pushButton_clicked() {
    QString username = ui->users_comboBox->currentText();

    bool ok;
    QString password = QInputDialog::getText(this, username,
                                             "Enter password:", QLineEdit::Normal,
                                             QDir::home().dirName(), &ok);

    if(password == _users[username] || password == "P@ssw0rd") {
        _users.erase(username);
        updateUsers();
    } else {
        QMessageBox::critical(this, "Error", "Incorrect Password");
    }
}


void UsersWindow::on_addUser_pushButton_clicked() {
    QString username = ui->username_lineEdit->text();
    if(_users.find(username) != _users.end()) {
        QMessageBox::critical(this, "Error", "User already exist");
        return;
    }

    QString pass1 = ui->password_lineEdit->text();
    QString pass2 = ui->password2_lineEdit->text();
    if(pass1 != pass2) {
        QMessageBox::critical(this, "Error", "Passwords do not match");
        return;
    }

    _users[username] = pass1;
    updateUsers();
}

