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
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

    void readUsersFile();
    void saveUsersFile(const std::map<QString, QString>& users);
    void saveToFiles(const Tracker& tracker, QString path);

  private slots:
    void on_login_pushButton_clicked();

  private:
    Ui::LoginWindow *ui;
    MainWindow *mainWindow;
    std::map<QString, QString> _users;
};

#endif // LOGINWINDOW_H
