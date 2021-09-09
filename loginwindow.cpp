#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>
#include <QDir>
#include <QFile>
#include <vector>

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent), ui(new Ui::LoginWindow) {
    ui->setupUi(this);
    this->setWindowTitle("Login");
    readUsersFile();
}

LoginWindow::~LoginWindow() {
    delete ui;
}

void LoginWindow::readUsersFile() {
    QFile file(qApp->applicationDirPath() + "/users.txt");

    if(file.open(QIODevice::ReadOnly)) {
        //get each user info
        while(!file.atEnd()) {
            QString user = file.readLine().trimmed();
            QStringList info = user.split(" ");

            if(info.size() != 2) {
                continue;
            }
            QString username = info[0];
            QString password = info[1];

            //add new user
            if(_users.find(username) == _users.end()) {
                _users[username] = password;
            }
        }

        file.close();
    }
}

void LoginWindow::saveUsersFile(const std::map<QString, QString> &users) {
    QFile file(qApp->applicationDirPath() + "/users.txt");

    if(file.open(QIODevice::WriteOnly)) {
        //save each user info
        for(const auto& user : users) {
            file.write((user.first + " ").toUtf8());
            file.write((user.second + "\n").toUtf8());
        }

        file.close();
    }
}

void LoginWindow::saveToFiles(const Tracker& tracker, QString path) {
    QDir dir(path);
    QString filename, category;

    // remove no longer exist categories
    foreach(QFileInfo info, dir.entryInfoList()) {
        if(!info.isFile()) {
            continue;
        }

        filename = info.fileName();

        category = filename;
        category.chop(4);

        if(tracker.find(category) == -1) {
            dir.remove(filename);
        }
    }

    //add transactions to each file
    for(auto cat : tracker.getCategories()) {
        category = cat.getCategory();
        if(category == "-- All --") {
            continue;
        }

        std::vector<Transaction> trans = cat.getTransDate();

        QFile file(path + category + ".txt");
        file.open(QIODevice::WriteOnly);
        // add each transaction:
        /*
         * yyyy/MM/dd (Date)
         * yyyy:MM:ddhh:mm:ss:zzz (Timestamp)
         * 0.00 (Amount)
         * description (new line replaced by "\\n")
         */

        file.write((category + "\n").toUtf8());
        for(const Transaction& t : trans) {
            QString date = t.getDate().toString("yyyy/MM/dd") + "\n";
            QString timestamp = t.timestampText() + "\n";
            QString amount = QString::number(t.getCost()) + "\n";
            QString description = t.getDescription();
            description.replace("\n", "\\\\n");
            description += "\n";

            file.write(date.toUtf8());
            file.write(timestamp.toUtf8());
            file.write(amount.toUtf8());
            file.write(description.toUtf8());
        }
        file.close();
    }

}

void LoginWindow::on_login_pushButton_clicked() {
    QString username = ui->username_lineEdit->text();
    QString password = ui->password_lineEdit->text();

    if(username == "" && password == "") {
        hide();
        mainWindow = new MainWindow(this, _users);
    } else if (username == "Admin" && password == "P@ssw0rd"){
        hide();
        mainWindow = new MainWindow(this, _users, true);
    } else if (_users.find(username) != _users.end()) {
        if(_users[username] == password) {
            hide();
            mainWindow = new MainWindow(this, _users, true);
        } else {
            QMessageBox::critical(this, "Error", "Invalid login information");
            return;
        }
    } else {
        QMessageBox::critical(this, "Error", "Invalid login information");
        return;
    }

    // execute main window
    mainWindow->show();
    QEventLoop loop;
    connect(mainWindow, SIGNAL(destroyed()), &loop, SLOT(quit()));
    loop.exec();

    // update files
    QString inPath = qApp->applicationDirPath() + "/Income/";
    QString exPath = qApp->applicationDirPath() + "/Expense/";
    saveToFiles(mainWindow->getInTracker(), inPath);
    saveToFiles(mainWindow->getExTracker(), exPath);
    saveUsersFile(mainWindow->getUsers());
}
