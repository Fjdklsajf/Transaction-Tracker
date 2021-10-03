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
    /*******************************
     ** CONSTRUCTOR & DESCTRUCTOR **
     *******************************/
    explicit MainWindow(QWidget *parent = nullptr,
                      const std::map<QString, QString>& users = std::map<QString, QString>(),
                      bool admin = false);
    ~MainWindow();

    /***************
     ** ACCESSORS **
     ***************/
    const Tracker& getInTracker() const;
    const Tracker& getExTracker() const;
    const std::map<QString, QString>& getUsers() const;

    /*************
     ** METHODS **
     *************/
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

  private slots:
    /*********************
     ** Slots & Signals **
     *********************/
    // income tab
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
    void on_inReport_pushButton_clicked();
    void inTable_headerClick(int col);

    // expense tab
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
    void on_exReport_pushButton_clicked();
    void exTable_headerClick(int col);

    // more tab
    void on_tabWidget_currentChanged(int index);
    void on_inReadFile_pushButton_clicked();
    void on_exReadFile_pushButton_clicked();
    void on_inGetFile_pushButton_clicked();
    void on_exGetFile_pushButton_clicked();
    void on_fontUpdate_pushButton_clicked();
    void on_accountsEdit_pushButton_clicked();
    void on_exit_pushButton_clicked();

private:
    const QString ALL_TRANS = "-- All --";
    const int SORT_CAT = 0, SORT_DATE = 1, SORT_AMOUNT = 2, SORT_CHECK = 3;

    Ui::MainWindow *ui;
    TransactionWindow *transWindow;
    UsersWindow *usersWindow;
    Tracker _income, _expense;
    bool _admin;
    std::vector<Transaction> _inTrans, _exTrans;
    std::vector<Transaction> _inFiltered, _exFiltered;
    // 0 - cat, 1 - date, 2 - amount, 3 - check number
    int _inSorted, _exSorted;
    bool _inDateFilter, _exDateFilter;
    bool _inKeyword, _exKeyword;
    std::map<QString, QString> _users;
};

#endif // MAINWINDOW_H

/******************************************************************************
 *  MainWindow Class
 *    A main window with widgets that displays income and expense transactions
 *    Includes user friendly widgets to filter, add, edit, or remove items
 ******************************************************************************/


/******************************
 ** CONSTRUCTOR & DESTRUCTOR **
 ******************************/

/******************************************************************************
 *  explicit MainWindow(QWidget *parent = nullptr,
 *           const std::map<QString, QString>& users = std::map<QString, QString>(),
 *           bool admin = false);
 *    Constructor; Set up ui and window title, read input files, and
 *      intialize class variables
 *    Parameters: QWidget *, const std::map<QString, QString>&, bool
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  ~MainWindow();
 *    Destructor; Deletes the ui and saves setting preferences in a file
 *    Parameters: none
 *    Return: void
 ******************************************************************************/


/***************
 ** ACCESSORS **
 ***************/

/******************************************************************************
 *  const Tracker& getInTracker() const;
 *
 *    Accessor; This method will return _income
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: const Tracker&
 ******************************************************************************/

/******************************************************************************
 *  const Tracker& getExTracker() const;
 *
 *    Accessor; This method will return _expense
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: const Tracker&
 ******************************************************************************/

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
 *  void readFile(QFile& file, Tracker& tracker);
 *
 *    Read each transaction in the given file and store in tracker
 * ----------------------------------------------------------------------------
 *    Parameters: QFile&, Tracker&
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void updateInCat();
 *
 *    Updates the income Category combo box
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void updateExCat();
 *
 *    Updates the expense Category combo box
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void updateInTrans();
 *
 *    Updates the list of income Transactions to be displayed based on the
 *      selected sorting preference
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void updateExTrans();
 *
 *    Updates the list of expense Transactions to be displayed based on the
 *      selected sorting preference
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void updateInTransTable();
 *
 *    Updates the income Transactions table with filtered Transactions list
 *    Updates the income description text edit with the first item
 *    Each transaction is displayed with the form:
 *      CateogryName mm/dd/yyyy $10.00
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void updateExTransTable();
 *
 *    Updates the expense Transactions table with filtered Transactions list
 *    Updates the expense description text edit with the first item
 *    Each transaction is displayed with the form:
 *      CateogryName mm/dd/yyyy $10.00
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void updateInDescrip(int index);
 *
 *    Updates the income description text edit with the description of the
 *      Transaction at given index
 * ----------------------------------------------------------------------------
 *    Parameters: int
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void updateExDescrip(int index);
 *
 *    Updates the expense description text edit with the description of the
 *      Transaction at given index
 * ----------------------------------------------------------------------------
 *    Parameters: int
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  std::vector<Transaction> filterKeyword(const std::vector<Transaction>& t,
 *                                         QString keyword);
 *
 *    Returns a sub-list of the given Transactions that contains the keyword
 * ----------------------------------------------------------------------------
 *    Parameters: const std::vector<Transaction>&, QString
 * ----------------------------------------------------------------------------
 *    Return: std::vector<Transaction>
 ******************************************************************************/

/******************************************************************************
 *  std::vector<Transaction> filterDate(const std::vector<Transaction>& t,
                                        const QDate& start, const QDate& end);
 *
 *    Returns a sub-list of the given Transactions that is within the given
 *      date range
 * ----------------------------------------------------------------------------
 *    Parameters: const std::vector<Transaction>&, const QDate&, const QDate&
 * ----------------------------------------------------------------------------
 *    Return: std::vector<Transaction>
 ******************************************************************************/

/******************************************************************************
 *  void reverse(std::vector<Transaction>& t);
 *
 *    Revese the given list of Transactions
 * ----------------------------------------------------------------------------
 *    Parameters: std::vector<Transaction>&
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/


/*********************
 ** Slots & Signals **
 *********************/

/******************************************************************************
 *  void on_inCat_comboBox_activated(int index);
 *
 *    Update the Transaction Table when the income Category combo box is changed
 * ----------------------------------------------------------------------------
 *    Parameters: int
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void on_inCatAdd_pushButton_clicked();
 *
 *    Prompts user for a new income Category name and add it if valid
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void on_inCatRemove_pushButton_clicked();
 *
 *    ** Requires administrative access **
 *    Removes the selected income Category after a confirmation from the user
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void on_inCatRename_pushButton_clicked();
 *
 *    ** Requires administrative access **
 *    Prompts user for a new income Category name and rename the selected income
 *      Category if valid
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void on_inTrans_tableWidget_cellClicked(int row, int column);
 *
 *    Updates the income description text edit based on the row selected on
 *      the income transaction table
 * ----------------------------------------------------------------------------
 *    Parameters: int, int
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void on_inTransAdd_pushButton_clicked();
 *
 *    Opens a TransactionWindow dialog and add a new Transaction based on user
 *      input
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void on_inTransRemove_pushButton_clicked();
 *
 *    ** Requires administrative access **
 *    Removes the selected Transaction after a user confirmation
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void on_inTransEdit_pushButton_clicked();
 *
 *    ** Requires administrative access **
 *    Opens a TransactionWindow dialog and edits the Transaction based on user
 *      input
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void on_inDateUpdate_pushButton_clicked();
 *
 *    Filters the income Transactions table with user selected date range
 *      and updates the income Transaction table
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void on_inDateClear_pushButton_clicked();
 *
 *    Clears the date filter and updates the income Transaction table
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void on_inSearchKey_pushButton_clicked();
 *
 *    Filters the income Transactions table with user inputted key phrase
 *      and updates the income Transaction table
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void on_inClearKey_pushButton_clicked();
 *
 *    Clears the keyword filter and updates the income Transaction table
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void on_inKey_lineEdit_returnPressed();
 *
 *    Filters the income Transactions table with user inputted key phrase
 *      and updates the income Transaction table
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void on_inReport_pushButton_clicked();
 *
 *    ** Requires administrative access **
 *    Generates a pdf report based on user selected income category, sorting
 *      method, and date and key phrase filters
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void Table_headerClick(int col);
 *
 *    Sorts the income Transaction table display order based the clicked column
 *      column 0: sort by category
 *      column 1: sort by date
 *      column 2: sort by amount
 * ----------------------------------------------------------------------------
 *    Parameters: int
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void on_exCat_comboBox_activated(int index);
 *
 *    Update the Transaction Table when the expense Category combo box is changed
 * ----------------------------------------------------------------------------
 *    Parameters: int
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void on_exCatAdd_pushButton_clicked();
 *
 *    Prompts user for a new expense Category name and add it if valid
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void on_exCatRemove_pushButton_clicked();
 *
 *    ** Requires administrative access **
 *    Removes the selected expense Category after a confirmation from the user
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void on_exCatRename_pushButton_clicked();
 *
 *    ** Requires administrative access **
 *    Prompts user for a new expense Category name and rename the selected expense
 *      Category if valid
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void on_exTrans_tableWidget_cellClicked(int row, int column);
 *
 *    Updates the expense description text edit based on the row selected on
 *      the expense transaction table
 * ----------------------------------------------------------------------------
 *    Parameters: int, int
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void on_exTransAdd_pushButton_clicked();
 *
 *    Opens a TransactionWindow dialog and add a new Transaction based on user
 *      input
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void on_exTransRemove_pushButton_clicked();
 *
 *    ** Requires administrative access **
 *    Removes the selected Transaction after a user confirmation
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void on_exTransEdit_pushButton_clicked();
 *
 *    ** Requires administrative access **
 *    Opens a TransactionWindow dialog and edits the Transaction based on user
 *      input
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void on_exDateUpdate_pushButton_clicked();
 *
 *    Filters the expense Transactions table with user selected date range
 *      and updates the expense Transaction table
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void on_exDateClear_pushButton_clicked();
 *
 *    Clears the date filter and updates the expense Transaction table
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void on_exSearchKey_pushButton_clicked();
 *
 *    Filters the expense Transactions table with user inputted key phrase
 *      and updates the expense Transaction table
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void on_exClearKey_pushButton_clicked();
 *
 *    Clears the keyword filter and updates the expense Transaction table
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void on_exKey_lineEdit_returnPressed();
 *
 *    Filters the expense Transactions table with user inputted key phrase
 *      and updates the expense Transaction table
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void on_exReport_pushButton_clicked();
 *
 *    ** Requires administrative access **
 *    Generates a pdf report based on user selected expense category, sorting
 *      method, and date and key phrase filters
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void exTable_headerClick(int col);
 *
 *    Sorts the expense Transaction table display order based the clicked column
 *      column 0: sort by category
 *      column 1: sort by date
 *      column 2: sort by amount
 * ----------------------------------------------------------------------------
 *    Parameters: int
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void on_tabWidget_currentChanged(int index);
 *
 *    Updates the default buttons based the the current tab
 * ----------------------------------------------------------------------------
 *    Parameters: int
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void on_inReadFile_pushButton_clicked();
 *
 *    ** Requires administrative access **
 *    Open a dialog for user to choose files and add income Transactions read
 *      from the files
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void on_exReadFile_pushButton_clicked();
 *
 *    ** Requires administrative access **
 *    Open a dialog for user to choose files and add expense Transactions read
 *      from the files
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void on_inGetFile_pushButton_clicked();
 *
 *    ** Requires administrative access **
 *    Downloads the income Transaction files to the Downloads folder
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void on_exGetFile_pushButton_clicked();
 *
 *    ** Requires administrative access **
 *    Downloads the expense Transaction files to the Downloads folder
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void on_fontUpdate_pushButton_clicked();
 *
 *    Updates the font family and size of the application based on the selected
 *      font and size combo box texts
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void on_accountsEdit_pushButton_clicked();
 *
 *    ** Requires administrative access **
 *    Opens the UsersWindow Dialog and updates _users based on user input
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void on_exit_pushButton_clicked();
 *
 *    Close the main window and exits program
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/
