#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>
#include <QDir>
#include <QFile>
#include <vector>

/******************************************************************************
 *
 *  Constructor LoginWindow: Class LoginWindow
 *_____________________________________________________________________________
 *  Set up ui and window title, and reads users file
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    the dialog window is set up
 ******************************************************************************/
LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent), ui(new Ui::LoginWindow) {
    // sets up the dialog window
    ui->setupUi(this);
    this->setWindowTitle("Login");

    // get users information
    readUsersFile();
}

/******************************************************************************
 *
 *  Destructor ~LoginWindow: Class LoginWindow
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
LoginWindow::~LoginWindow() {
    delete ui;
}

/******************************************************************************
 *
 *  Method readUsersFile: Class LoginWindow
 *_____________________________________________________________________________
 *  This method will read each usernames and passwords from uers.txt file
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    users.txt exists
 *
 *  POST-CONDITIONS
 *    Usernames and passwords are added to _users
 ******************************************************************************/
void LoginWindow::readUsersFile() {
    QFile file(qApp->applicationDirPath() + "/users.txt");

    //open file
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

/******************************************************************************
 *
 *  Method saveUsersFile: Class LoginWindow
 *_____________________________________________________________________________
 *  This method will write users information to the users.txt file
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    users.txt is updated
 ******************************************************************************/
void LoginWindow::saveUsersFile(const std::map<QString, QString> &users) {
    QFile file(qApp->applicationDirPath() + "/users.txt");

    // open file
    if(file.open(QIODevice::WriteOnly)) {
        //save each user info
        for(const auto& user : users) {
            file.write((user.first + " ").toUtf8());
            file.write((user.second + "\n").toUtf8());
        }

        file.close();
    }
}

/******************************************************************************
 *
 *  Method saveUsersFile: Class LoginWindow
 *_____________________________________________________________________________
 *  This method will write Tracker information into files in the given path
 *  Transasctions of different Categories are stored in different files
 *  Transactions are stored in the format:
 *      yyyy/MM/dd (Date)
 *      yyyy:MM:ddhh:mm:ss:zzz (Timestamp)
 *      0.00 (Amount)
 *      description (new line replaced by "\\n")
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    the path is valid
 *
 *  POST-CONDITIONS
 *    Tracker information are saved
 ******************************************************************************/
void LoginWindow::saveToFiles(const Tracker& tracker, QString path) {
    QDir dir(path);
    QString filename, category;

    // erase category files that were removed by the user
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

    // find each category in Tracker
    for(auto cat : tracker.getCategories()) {
        category = cat.getCategory();
        if(category == "-- All --") {
            continue;
        }

        // save transactions by date
        std::vector<Transaction> trans = cat.getTransDate();

        // open file for category
        QFile file(path + category + ".txt");
        file.open(QIODevice::WriteOnly);

        // write transaction information in file
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

/******************************************************************************
 *
 *  Method on_login_pushButton_clicked: Class LoginWindow
 *_____________________________________________________________________________
 *  checks inputted login information, go to main window if valid
 *      no username and password grants restricted access
 *      correct login info grants administrative access
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    Login winodw is hidden and main window is shown
 ******************************************************************************/
void LoginWindow::on_login_pushButton_clicked() {
    QString username = ui->username_lineEdit->text();
    QString password = ui->password_lineEdit->text();

    if(username == "" && password == "") {
        // restricted access
        hide();
        mainWindow = new MainWindow(this, _users);
    } else if (username == "Admin" && password == "P@ssw0rd"){
        // administrative access
        hide();
        mainWindow = new MainWindow(this, _users, true);
    } else if (_users.find(username) != _users.end()) {
        // check login info
        if(_users[username] == password) {
            // administrative access
            hide();
            mainWindow = new MainWindow(this, _users, true);
        } else {
            // incorrect password
            QMessageBox::critical(this, "Error", "Incorrect password");
            return;
        }
    } else {
        // user not found
        QMessageBox::critical(this, "Error", "Username not found");
        return;
    }

    // execute main window
    mainWindow->show();
    QEventLoop loop;
    connect(mainWindow, SIGNAL(destroyed()), &loop, SLOT(quit()));
    loop.exec();

    // update files upon application exit
    QString inPath = qApp->applicationDirPath() + "/Income/";
    QString exPath = qApp->applicationDirPath() + "/Expense/";
    saveToFiles(mainWindow->getInTracker(), inPath);
    saveToFiles(mainWindow->getExTracker(), exPath);
    saveUsersFile(mainWindow->getUsers());
}
