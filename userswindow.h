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
    explicit UsersWindow(QWidget *parent = nullptr,
                         const std::map<QString, QString>& users = std::map<QString, QString>());
    ~UsersWindow();

    const std::map<QString, QString>& getUsers();
    void updateUsers();

  private slots:
    void on_removeUser_pushButton_clicked();
    void on_addUser_pushButton_clicked();

private:
    Ui::UsersWindow *ui;
    std::map<QString, QString> _users;
};

#endif // USERSWINDOW_H
