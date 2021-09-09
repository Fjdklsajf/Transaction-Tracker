#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tracker.h"
#include "transactionwindow.h"
#include "userswindow.h"
#include <QMainWindow>
#include <QString>
#include <QTableWidget>
#include <QFile>
#include <vector>
#include <map>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr,
                      const std::map<QString, QString>& users = std::map<QString, QString>(),
                      bool admin = false);
    ~MainWindow();

    void readFile(QFile& file, Tracker& tracker);
    void updateInCat();
    void updateExCat();
    void updateInTrans();
    void updateExTrans();
    void updateInTransTable();
    void updateExTransTable();
    void updateInDescrip(int index);
    void updateExDescrip(int index);
    std::vector<Transaction> filterKeyword(const std::vector<Transaction>& t,
                                         QString keyword);
    std::vector<Transaction> filterDate(const std::vector<Transaction>& t,
                                         const QDate& start, const QDate& end);
    void reverse(std::vector<Transaction>& t);
    const Tracker& getInTracker() const;
    const Tracker& getExTracker() const;
    const std::map<QString, QString>& getUsers() const;

  private slots:
    void on_inCat_comboBox_activated(int index);
    void on_inCatAdd_pushButton_clicked();
    void on_inCatRemove_pushButton_clicked();
    void on_inCatRename_pushButton_clicked();
    void on_inTrans_tableWidget_cellClicked(int row, int column);
    void on_inTransAdd_pushButton_clicked();
    void on_inTransRemove_pushButton_clicked();
    void on_inTransEdit_pushButton_clicked();
    void on_inDateUpdate_pushButton_clicked();
    void on_inDateClear_pushButton_clicked();
    void on_inSearchKey_pushButton_clicked();
    void on_inClearKey_pushButton_clicked();
    void on_inKey_lineEdit_returnPressed();
    void inTable_headerClick(int col);

    void on_exCat_comboBox_activated(int index);
    void on_exCatAdd_pushButton_clicked();
    void on_exCatRemove_pushButton_clicked();
    void on_exCatRename_pushButton_clicked();
    void on_exTrans_tableWidget_cellClicked(int row, int column);
    void on_exTransAdd_pushButton_clicked();
    void on_exTransRemove_pushButton_clicked();
    void on_exTransEdit_pushButton_clicked();
    void on_exDateUpdate_pushButton_clicked();
    void on_exDateClear_pushButton_clicked();
    void on_exSearchKey_pushButton_clicked();
    void on_exClearKey_pushButton_clicked();
    void on_exKey_lineEdit_returnPressed();
    void exTable_headerClick(int col);

    void on_tabWidget_currentChanged(int index);
    void on_inReadFile_pushButton_clicked();
    void on_exReadFile_pushButton_clicked();
    void on_inGetFile_pushButton_clicked();
    void on_exGetFile_pushButton_clicked();
    void on_fontUpdate_pushButton_clicked();
    void on_accountsEdit_pushButton_clicked();
    void on_exit_pushButton_clicked();
    void on_inReport_pushButton_clicked();
    void on_exReport_pushButton_clicked();

private:
    const QString ALL_TRANS = "-- All --";
    const int SORT_CAT = 0, SORT_DATE = 1, SORT_AMOUNT = 2;

    Ui::MainWindow *ui;
    TransactionWindow *transWindow;
    UsersWindow *usersWindow;
    Tracker _income, _expense;
    bool _admin;
    std::vector<Transaction> inTrans, exTrans;
    std::vector<Transaction> inFiltered, exFiltered;
    // 0 - cat, 1 - date, 2 - amount
    int inSorted, exSorted;
    bool inDateFilter, exDateFilter;
    bool inKeyword, exKeyword;
    std::map<QString, QString> _users;
};

#endif // MAINWINDOW_H
