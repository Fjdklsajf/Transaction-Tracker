#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QStringList>
#include <QInputDialog>
#include <QDir>
#include <QDebug>
#include <QFileDialog>
#include <QFont>
#include <QPrinter>
#include <QPrintDialog>

/******************************************************************************
 *
 *  Constructor MainWindow: Class MainWindow
 *_____________________________________________________________________________
 *  Set up ui and window title, read input files, and intialize class variables
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    the main window and widgets are set up
 ******************************************************************************/
MainWindow::MainWindow(QWidget *parent, const std::map<QString, QString>& users, bool admin) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
    // set up window
    ui->setupUi(this);
    this->setWindowTitle("Transaction Tracker");

    // initialize variables
    _users = users;
    _admin = admin;
    _inSorted = SORT_CAT;
    _exSorted = SORT_CAT;
    _inDateFilter = false;
    _exDateFilter = false;
    _inKeyword = false;
    _exKeyword = false;

    // create file directories
    if(!QDir("Income").exists()) {
        QDir().mkdir("Income");
    }
    if(!QDir("Expense").exists()) {
        QDir().mkdir("Expense");
    }

    // read income files
    QString inPath = qApp->applicationDirPath() + "/Income/";
    QDir inDir(inPath);
    foreach(QFileInfo info, inDir.entryInfoList(QDir::Files | QDir::Hidden)) {
        if(!info.isFile()) {
            continue;
        }
        QFile file(inPath + info.fileName());
        // add Transactions to income Tracker
        readFile(file, _income);
    }

    // read expense files
    QString exPath = qApp->applicationDirPath() + "/Expense/";
    QDir exDir(exPath);
    foreach(QFileInfo info, exDir.entryInfoList(QDir::Files | QDir::Hidden)) {
        if(!info.isFile()) {
            continue;
        }
        QFile file(exPath + info.fileName());
        // add Transactions to expense Tracker
        readFile(file, _expense);
    }

    // set up combo box widgets
    updateInCat();
    updateExCat();

    // set up transaction tables
    ui->inTrans_tableWidget->setColumnCount(3);
    ui->exTrans_tableWidget->setColumnCount(4);
    QStringList labels;
    labels << "Category" << "Date" << "Amount";
    ui->inTrans_tableWidget->setHorizontalHeaderLabels(labels);
    ui->inTrans_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->inTrans_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    labels << "Check #";
    ui->exTrans_tableWidget->setHorizontalHeaderLabels(labels);
    ui->exTrans_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->exTrans_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    // update items on transaction tables
    updateInTrans();
    updateInTransTable();
    updateExTrans();
    updateExTransTable();

    // connect table header signals
    connect(ui->inTrans_tableWidget->horizontalHeader(),
            SIGNAL(sectionClicked(int)), SLOT(inTable_headerClick(int)));
    connect(ui->exTrans_tableWidget->horizontalHeader(),
            SIGNAL(sectionClicked(int)), SLOT(exTable_headerClick(int)));

    // set up default calendar dates
    ui->inStartDate_dateEdit->setDate(QDate::currentDate());
    ui->inEndDate_dateEdit->setDate(QDate::currentDate());
    ui->exStartDate_dateEdit->setDate(QDate::currentDate());
    ui->exEndDate_dateEdit->setDate(QDate::currentDate());

    // set default button and user preference
    ui->inTransAdd_pushButton->setDefault(true);
    QString font = "Arial";
    QString size = "10";
    QFile settings = qApp->applicationDirPath() + "/settings.txt";
    if(settings.open(QIODevice::ReadOnly)) {
        font = settings.readLine().trimmed();
        size = settings.readLine().trimmed();
        settings.close();
    }
    ui->fontComboBox->setCurrentFont(QFont(font));
    ui->fontSize_comboBox->setCurrentText(size);

    QFont f = font;
    f.setPointSize(size.toInt());
    QApplication::setFont(f);
}

/******************************************************************************
 *
 *  Destructor ~MainWindow: Class MainWindow
 *_____________________________________________________________________________
 *  Deletes the ui and saves setting preferences in a file
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    ui is deleted and settings file updated
 ******************************************************************************/
MainWindow::~MainWindow() {
    QFile settings = qApp->applicationDirPath() + "/settings.txt";
    if(settings.open(QIODevice::WriteOnly)) {
        settings.write((ui->fontComboBox->currentText() + "\n").toUtf8());
        settings.write((ui->fontSize_comboBox->currentText() + "\n").toUtf8());
        settings.close();
    }

    delete ui;
}

/******************************************************************************
 *
 *  Accessor getInTracker: Class MainWindow
 *_____________________________________________________________________________
 *  This method will return the income tracker
 *  - returns const Tracker&
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _income is returned
 ******************************************************************************/
const Tracker& MainWindow::getInTracker() const {
    return _income;
}

/******************************************************************************
 *
 *  Accessor getExTracker: Class MainWindow
 *_____________________________________________________________________________
 *  This method will return the expense tracker
 *  - returns const Tracker&
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _expense is returned
 ******************************************************************************/
const Tracker& MainWindow::getExTracker() const {
    return _expense;
}

/******************************************************************************
 *
 *  Accessor getUsers: Class MainWindow
 *_____________________________________________________________________________
 *  This method will return _users
 *  - returns const Tracker&
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _users is returned
 ******************************************************************************/
const std::map<QString, QString>& MainWindow::getUsers() const {
    return _users;
}

/******************************************************************************
 *
 *  Method readFile: Class MainWindow
 *_____________________________________________________________________________
 *  Read each transaction in the given file and store in tracker
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    files is valid
 *
 *  POST-CONDITIONS
 *    A Category and Transactions are added to tracker
 ******************************************************************************/
void MainWindow::readFile(QFile& file, Tracker& tracker) {
    QString category;

    // open file
    if(file.open(QIODevice::ReadOnly)) {
        // add Category to Tracker
        if(!file.atEnd()) {
            category = file.readLine().trimmed();
            tracker.addCategory(category);
        }

        // add each Transaction to Category
        while(!file.atEnd()) {
            QString date = file.readLine().trimmed();
            QString timestamp = file.readLine().trimmed();
            QString cost = file.readLine().trimmed();
            QString description = file.readLine().trimmed();
            QString checkNum = file.readLine().trimmed();
            description.replace("\\\\n", "\n");

            QStringList list = date.split("/");
            QDate d(list[0].toInt(), list[1].toInt(), list[2].toInt());

            list = timestamp.split(":");
            QDate timestampD(list[0].toInt(), list[1].toInt(), list[2].toInt());
            QTime timestampT(list[3].toInt(), list[4].toInt(), list[5].toInt(), list[6].toInt());
            QDateTime t(timestampD, timestampT);

            tracker.addTransaction(category, cost.toDouble(), description, d, checkNum, t);
        }

        file.close();
    } else {
        qDebug() << category + "Failed to open";
    }
}

/******************************************************************************
 *
 *  Method updateInCat: Class MainWindow
 *_____________________________________________________________________________
 *  Updates the income Category combo box
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    ui->inCat_comboBox is updated
 ******************************************************************************/
void MainWindow::updateInCat() {
    ui->inCat_comboBox->clear();
    ui->inCat_comboBox->addItem(ALL_TRANS);

    for(const QString& cat : _income.getCategoryNames()) {
        ui->inCat_comboBox->addItem(cat);
    }
}

/******************************************************************************
 *
 *  Method updateExCat: Class MainWindow
 *_____________________________________________________________________________
 *  Updates the expense Category combo box
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    ui->exCat_comboBox is updated
 ******************************************************************************/
void MainWindow::updateExCat() {
    ui->exCat_comboBox->clear();
    ui->exCat_comboBox->addItem(ALL_TRANS);

    for(const QString& cat : _expense.getCategoryNames()) {
        ui->exCat_comboBox->addItem(cat);
    }
}

/******************************************************************************
 *
 *  Method updateInTrans: Class MainWindow
 *_____________________________________________________________________________
 *  Updates the list of income Transactions to be displayed based on the
 *      selected sorting preference
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _inTrans is updated
 ******************************************************************************/
void MainWindow::updateInTrans() {
    QString cat = ui->inCat_comboBox->currentText();

    if(cat == ALL_TRANS) { // all categories
        if(_inSorted == SORT_CAT) {
            _inTrans = _income.getAllTransactions();
        } else if (_inSorted == SORT_AMOUNT) {
            _inTrans = _income.getTransAmountSorted();
        } else {
            _inTrans = _income.getTransDateSorted();
            _inSorted = SORT_DATE;
        }
    } else { // selected category
        if(_inSorted == SORT_AMOUNT) {
            _inTrans = _income.getTransAmount(cat);
        } else {
            _inTrans = _income.getTransDate(cat);
            _inSorted = SORT_DATE;
        }
    }

}

/******************************************************************************
 *
 *  Method updateExTrans: Class MainWindow
 *_____________________________________________________________________________
 *  Updates the list of expense Transactions to be displayed based on the
 *      selected sorting preference
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _exTrans is updated
 ******************************************************************************/
void MainWindow::updateExTrans() {
    QString cat = ui->exCat_comboBox->currentText();

    if(cat == ALL_TRANS) { // all categories
        if(_exSorted == SORT_CAT) {
            _exTrans = _expense.getAllTransactions();
        } else if (_exSorted == SORT_AMOUNT) {
            _exTrans = _expense.getTransAmountSorted();
        } else if (_exSorted == SORT_CHECK) {
            _exTrans = _expense.getTransCheckNumSorted();
        } else {
            _exTrans = _expense.getTransDateSorted();
            _exSorted = SORT_DATE;
        }
    } else { // selected category
        if(_exSorted == SORT_AMOUNT) {
            _exTrans = _expense.getTransAmount(cat);
        } else if (_exSorted == SORT_CHECK) {
            _exTrans = _expense.getTransCheckNumSorted(cat);
        } else {
            _exTrans = _expense.getTransDate(cat);
            _exSorted = SORT_DATE;
        }
    }
}

/******************************************************************************
 *
 *  Method updateInTransTable: Class MainWindow
 *_____________________________________________________________________________
 *  Updates the income Transactions table with filtered Transactions list
 *    Updates the income description text edit with the first item
 *    Updates the total amount
 *    Each transaction is displayed with the form:
 *      CateogryName mm/dd/yyyy $10.00
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    ui->inTrans_tableWidget and ui->inDescrip_textEdit are updated
 ******************************************************************************/
void MainWindow::updateInTransTable() {
    // clear table
    ui->inTrans_tableWidget->setRowCount(0);

    // apply keyword filter
    _inFiltered = _inTrans;
    if(_inKeyword) {
        _inFiltered = filterKeyword(_inFiltered, ui->inKey_lineEdit->text());
    }

    // apply date filter
    if(_inDateFilter) {
        QDate start = ui->inStartDate_dateEdit->date();
        QDate end = ui->inEndDate_dateEdit->date();
        _inFiltered = filterDate(_inFiltered, start, end);
    }

    // Add Transaction to table
    for(unsigned i = 0; i < _inFiltered.size(); i++) {
        ui->inTrans_tableWidget->insertRow(i);
        QTableWidgetItem *category = new QTableWidgetItem;
        QTableWidgetItem *date = new QTableWidgetItem;
        QTableWidgetItem *cost = new QTableWidgetItem;

        category->setText(_inFiltered[i].getCategory());
        date->setText(_inFiltered[i].dateShortText());
        cost->setText(_inFiltered[i].costText());

        ui->inTrans_tableWidget->setItem(i, 0, category);
        ui->inTrans_tableWidget->setItem(i, 1, date);
        ui->inTrans_tableWidget->setItem(i, 2, cost);
    }

    // set up description
    if(_inFiltered.size() > 0) {
        updateInDescrip(0);
        ui->inTrans_tableWidget->selectRow(0);
    } else {
        ui->inDescrip_textEdit->clear();
    }

    // Update total amount text
    double total = 0;
    for(const Transaction& t : _inFiltered) {
        total += t.getCost();
    }
    ui->inTotal_lineEdit->setText(QString().asprintf("$%0.2f", total));
}

/******************************************************************************
 *
 *  Method updateExTransTable: Class MainWindow
 *_____________________________________________________________________________
 *  Updates the expense Transactions table with filtered Transactions list
 *    Updates the expense description text edit with the first item
 *    Updates the total amount
 *    Each transaction is displayed with the form:
 *      CateogryName mm/dd/yyyy $10.00
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    ui->exTrans_tableWidget and ui->exDescrip_textEdit are updated
 ******************************************************************************/
void MainWindow::updateExTransTable() {
    // clear table
    ui->exTrans_tableWidget->setRowCount(0);

    // apply keyword filter
    _exFiltered = _exTrans;
    if(_exKeyword) {
        _exFiltered = filterKeyword(_exFiltered, ui->exKey_lineEdit->text());
    }

    // apply date filter
    if(_exDateFilter) {
        QDate start = ui->exStartDate_dateEdit->date();
        QDate end = ui->exEndDate_dateEdit->date();
        _exFiltered = filterDate(_exFiltered, start, end);
    }

    // Add to table
    for(unsigned i = 0; i < _exFiltered.size(); i++) {
        ui->exTrans_tableWidget->insertRow(i);
        QTableWidgetItem *category = new QTableWidgetItem;
        QTableWidgetItem *date = new QTableWidgetItem;
        QTableWidgetItem *cost = new QTableWidgetItem;
        QTableWidgetItem *checkNum = new QTableWidgetItem;

        category->setText(_exFiltered[i].getCategory());
        date->setText(_exFiltered[i].dateShortText());
        cost->setText(_exFiltered[i].costText());
        checkNum->setText(_exFiltered[i].getCheckNum());

        ui->exTrans_tableWidget->setItem(i, 0, category);
        ui->exTrans_tableWidget->setItem(i, 1, date);
        ui->exTrans_tableWidget->setItem(i, 2, cost);
        ui->exTrans_tableWidget->setItem(i, 3, checkNum);
    }

    // set up description
    if(_exFiltered.size() > 0) {
        updateExDescrip(0);
        ui->exTrans_tableWidget->selectRow(0);
    } else {
        ui->exDescrip_textEdit->clear();
    }

    // Update total amount text
    double total = 0;
    for(const Transaction& t : _exFiltered) {
        total += t.getCost();
    }
    ui->exTotal_lineEdit->setText(QString().asprintf("$%0.2f", total));
}

/******************************************************************************
 *
 *  Method updateInDescrip: Class MainWindow
 *_____________________________________________________________________________
 *  Updates the income description text edit with the description of the
 *      Transaction at given index
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    ui->inDescrip_textEdit is updated
 ******************************************************************************/
void MainWindow::updateInDescrip(int index) {
    ui->inDescrip_textEdit->clear();
    ui->inDescrip_textEdit->setText(_inFiltered[index].toString());
}

/******************************************************************************
 *
 *  Method updateExDescrip: Class MainWindow
 *_____________________________________________________________________________
 *  Updates the expense description text edit with the description of the
 *      Transaction at given index
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    ui->exDescrip_textEdit is updated
 ******************************************************************************/
void MainWindow::updateExDescrip(int index) {
    ui->exDescrip_textEdit->clear();
    ui->exDescrip_textEdit->setText(_exFiltered[index].toString());
}

/******************************************************************************
 *
 *  Method filterKeyword: Class MainWindow
 *_____________________________________________________________________________
 *  Returns a sub-list of the given Transactions that contains the keyword
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    a list of Transaction containing the keyword is returned
 ******************************************************************************/
std::vector<Transaction> MainWindow::filterKeyword(const std::vector<Transaction>& t,
                                                   QString keyword) {
    std::vector<Transaction> transactions;

    for(const Transaction& trans : t) {
        // add Transactions containing keyword
        if(trans.contains(keyword)) {
            transactions.push_back(trans);
        }
    }

    return transactions;
}

/******************************************************************************
 *
 *  Method filterDate: Class MainWindow
 *_____________________________________________________________________________
 *  Returns a sub-list of the given Transactions that is within the given
 *      date range
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    a list of Transaction within the given dates inclusively is returned
 ******************************************************************************/
std::vector<Transaction> MainWindow::filterDate(const std::vector<Transaction>& t,
                                                const QDate& start, const QDate& end) {
    std::vector<Transaction> transactions;

    for(const Transaction& trans : t) {
        // add Transactions within the given dates inclusively
        if(trans.getDate() >= start && trans.getDate() <= end) {
            transactions.push_back(trans);
        }
    }

    return transactions;
}

/******************************************************************************
 *
 *  Method reverse: Class MainWindow
 *_____________________________________________________________________________
 *  Revese the given list of Transactions
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    parameter t is reveresed
 ******************************************************************************/
void MainWindow::reverse(std::vector<Transaction>& t) {
    std::reverse(t.begin(), t.end());
}

/******************************************************************************
 *
 *  Method on_inCat_comboBox_activated: Class MainWindow
 *_____________________________________________________________________________
 *  Update the Transaction Table when the income Category combo box is changed
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    income tab widgets display are updated
 ******************************************************************************/
void MainWindow::on_inCat_comboBox_activated(int index) {
    updateInTrans();
    updateInTransTable();
}

/******************************************************************************
 *
 *  Method on_inCatAdd_pushButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  Prompts user for a new income Category name and add it if valid
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    new Category is added to _income
 ******************************************************************************/
void MainWindow::on_inCatAdd_pushButton_clicked() {
    // prompt for new category name
    bool ok;
    QString category = QInputDialog::getText(this, "New Income Category",
                                             "Enter the category name:", QLineEdit::Normal,
                                             QDir::home().dirName(), &ok);

    if(ok && !category.isEmpty()) {
        if(!_income.exist(category)) {
            // add valid category name
            _income.addCategory(category);

            // update display
            updateInCat();
            ui->inCat_comboBox->setCurrentText(category);
            updateInTrans();
            updateInTransTable();
        } else {
            // invalid name
            QMessageBox::critical(this, "Error", "Category already exists");
            on_inCatAdd_pushButton_clicked();
        }
    }
}

/******************************************************************************
 *
 *  Method on_inCatRemove_pushButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  ** Requires administrative access **
 *  Removes the selected income Category after a confirmation from the user
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    selected Category is removed from _income
 ******************************************************************************/
void MainWindow::on_inCatRemove_pushButton_clicked() {
    if(!_admin) {
        QMessageBox::critical(this, "No Access", "Please login");
        return;
    }

    QString category = ui->inCat_comboBox->currentText();
    if(category == ALL_TRANS) {
        return;
    }

    // confirm removal with user
    auto confirmed = QMessageBox::question(this, "Confirmation",
                                  "Do you really want to remove " + category,
                                  QMessageBox::Yes | QMessageBox::No);

    if(confirmed == QMessageBox::Yes) {
        _income.removeCategory(category);
        updateInCat();
        updateInTrans();
        updateInTransTable();
    }
}

/******************************************************************************
 *
 *  Method on_inCatRename_pushButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  ** Requires administrative access **
 *  Prompts user for a new income Category name and rename the selected income
 *      Category if valid
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    selected Category is renamed
 ******************************************************************************/
void MainWindow::on_inCatRename_pushButton_clicked() {
    if(!_admin) {
        QMessageBox::critical(this, "No Access", "Please login");
        return;
    }

    QString current = ui->inCat_comboBox->currentText();
    if(current == ALL_TRANS) {
        return;
    }

    // prompt user for new name
    bool ok;
    QString category = QInputDialog::getText(this, current,
                                             "New name:", QLineEdit::Normal,
                                             QDir::home().dirName(), &ok);

    if(ok && !category.isEmpty()) {
        int index = _income.find(category);
        if(index == -1) {
            // valid name, change to new name
            Category temp = _income.getCategory(current);
            temp.setCategoryName(category);
            _income.removeCategory(current);
            _income.addCategory(temp);

            // update display
            updateInCat();
            ui->inCat_comboBox->setCurrentText(category);
            updateInTrans();
            updateInTransTable();
        } else {
            // invalid name
            QMessageBox::critical(this, "Error", "Category already exists");
            on_inCatRename_pushButton_clicked();
        }
    }
}

/******************************************************************************
 *
 *  Method on_inTrans_tableWidget_cellClicked: Class MainWindow
 *_____________________________________________________________________________
 *  Updates the income description text edit based on the row selected on
 *      the income transaction table
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    income description display is updated
 ******************************************************************************/
void MainWindow::on_inTrans_tableWidget_cellClicked(int row, int column) {
    updateInDescrip(row);
}

/******************************************************************************
 *
 *  Method on_inTransAdd_pushButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  Opens a TransactionWindow dialog and add a new Transaction based on user
 *      input
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    new Transaction is added to _income
 ******************************************************************************/
void MainWindow::on_inTransAdd_pushButton_clicked() {
    if(_income.getCategoryNames().size() <= 0) {
        return;
    }

    // set up and display TransactionWindow dialog
    transWindow = new TransactionWindow(this, _income.getCategoryNames());
    if(ui->inCat_comboBox->currentText() != ALL_TRANS) {
        transWindow->setCategory(ui->inCat_comboBox->currentText());
    }
    transWindow->exec();

    // save button clicked
    if(transWindow->save()) {
        // add new Transaction
        QString category = transWindow->category();
        _income.addTransaction(category, transWindow->cost(),
                               transWindow->description(), transWindow->date(),
                               transWindow->checkNum());

        // Update display
        updateInTrans();
        updateInTransTable();
    }
}

/******************************************************************************
 *
 *  Method on_inTransRemove_pushButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  ** Requires administrative access **
 *  Removes the selected Transaction after a user confirmation
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    selected Transaction is removed from _income
 ******************************************************************************/
void MainWindow::on_inTransRemove_pushButton_clicked() {
    if(!_admin) {
        QMessageBox::critical(this, "No Access", "Please login");
        return;
    }

    if(!ui->inTrans_tableWidget->currentIndex().isValid()) {
        return;
    }

    int index = ui->inTrans_tableWidget->currentRow();
    Transaction t = _inFiltered[index];
    QString category = t.getCategory();

    // confirm removal
    auto confirmed = QMessageBox::question(this, "Confirmation", "Remove this transaction?\n" +
                                           t.dateFullText() + " -- " + t.costText(),
                                           QMessageBox::Yes | QMessageBox::No);

    if(confirmed == QMessageBox::Yes) {
        // remove Transaction
        _income.removeTransaction(category, t);
        if(ui->inCat_comboBox->currentText() == ALL_TRANS) {
            _inTrans = _income.getAllTransactions();
        } else {
            _inTrans = _income.getTransDate(category);
        }

        // update display
        updateInTrans();
        updateInTransTable();
    }
}

/******************************************************************************
 *
 *  Method on_inTransEdit_pushButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  ** Requires administrative access **
 *  Opens a TransactionWindow dialog and edits the Transaction based on user
 *      input
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    selected Tranasction is modified
 ******************************************************************************/
void MainWindow::on_inTransEdit_pushButton_clicked() {
    if(!_admin) {
        QMessageBox::critical(this, "No Access", "Please login");
        return;
    }

    if(!ui->inTrans_tableWidget->currentIndex().isValid()) {
        return;
    }

    int i = ui->inTrans_tableWidget->currentRow();
    Transaction t = _inFiltered[i];
    QString category = t.getCategory();

    // set up and display TransactionWindow dialog
    transWindow = new TransactionWindow(_income.getCategoryNames(), t.getDate(),
                                        t.getCost(), t.getDescription(),
                                        t.getCheckNum(), this);
    transWindow->setCategory(category);
    transWindow->exec();

    // save button clicked
    if(transWindow->save()) {
        // modify selected Transaction
        QString newCat = transWindow->category();
        _income.removeTransaction(category, t);
        _income.addTransaction(newCat, transWindow->cost(),
                               transWindow->description(), transWindow->date(),
                               transWindow->checkNum());

        // update display
        updateInTrans();
        updateInTransTable();
    }
}

/******************************************************************************
 *
 *  Method on_inDateUpdate_pushButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  Filters the income Transactions table with user selected date range
 *      and updates the income Transaction table
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    date filter is applied
 ******************************************************************************/
void MainWindow::on_inDateUpdate_pushButton_clicked() {
    _inDateFilter = true;
    updateInTransTable();
}

/******************************************************************************
 *
 *  Method on_inDateClear_pushButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  Clears the date filter and updates the income Transaction table
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    date filter is removed
 ******************************************************************************/
void MainWindow::on_inDateClear_pushButton_clicked() {
    _inDateFilter = false;
    updateInTransTable();
}

/******************************************************************************
 *
 *  Method on_inSearchKey_pushButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  Filters the income Transactions table with user inputted key phrase
 *      and updates the income Transaction table
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    keyword filter is applied
 ******************************************************************************/
void MainWindow::on_inSearchKey_pushButton_clicked() {
    if(ui->inKey_lineEdit->text() == "") {
        on_inClearKey_pushButton_clicked();
        return;
    }
    _inKeyword = true;

    updateInTransTable();
}

/******************************************************************************
 *
 *  Method on_inClearKey_pushButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  Clears the keyword filter and updates the income Transaction table
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    keyword filter is removed
 ******************************************************************************/
void MainWindow::on_inClearKey_pushButton_clicked() {
    if(!_inKeyword) {
        return;
    }

    _inKeyword = false;

    ui->inKey_lineEdit->clear();
    updateInTransTable();
    ui->inTransAdd_pushButton->setDefault(true);
}

/******************************************************************************
 *
 *  Method on_inKey_lineEdit_returnPressed: Class MainWindow
 *_____________________________________________________________________________
 *  Filters the income Transactions table with user inputted key phrase
 *      and updates the income Transaction table
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    keyword filter is applied
 ******************************************************************************/
void MainWindow::on_inKey_lineEdit_returnPressed() {
    ui->inTransAdd_pushButton->setDefault(false);
    on_inSearchKey_pushButton_clicked();
}

/******************************************************************************
 *
 *  Method on_inReport_pushButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  ** Requires administrative access **
 *  Generates a pdf report based on user selected income category, sorting
 *      method, and date and key phrase filters
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    A pdf report to print is generated
 ******************************************************************************/
void MainWindow::on_inReport_pushButton_clicked() {
    if(!_admin) {
        QMessageBox::critical(this, "No Access", "Please login");
        return;
    }

    // set up printer and dialog
    QPrinter *printer = new QPrinter(QPrinter::HighResolution);
    printer->setPageSize(QPageSize::A4);

    QPrintDialog dialog(printer, this);
    dialog.setWindowTitle("Print Document");
    if(dialog.exec() == QDialog::Rejected) {
        return;
    }

    QString cat = ui->inCat_comboBox->currentText();
    if(cat == ALL_TRANS) {
        cat = "All";
    }

    // Create pdf with html format
    QString html = "";

    // Add Header
    if(_inDateFilter) {
        html = "<div align=right>";

        QDate start = ui->inStartDate_dateEdit->date();
        QDate end = ui->inEndDate_dateEdit->date();

        html += start.toString("MM/dd/yyyy") + " - " +
                end.toString("MM/dd/yyyy") + "</div>";
    }

    html += "<div align=left>Category: " +
                cat +
            "</div>";

    if(_inKeyword) {
        QString keyword = ui->inKey_lineEdit->text();
        html += "<div align=left>Keyword: " +
                    keyword +
                "</div>";
    }

    // Add Title
    html += "<h1 align=center> Income Report</h1>";

    // Add Transactions
    cat = ui->inCat_comboBox->currentText();
    html += "<p align=left>";
    for(unsigned i = 0; i < _inFiltered.size(); i++) {
        if(cat == ALL_TRANS) {
            html += _inFiltered[i].getCategory() + "<br>";
        }
        html += _inFiltered[i].dateShortText() + " -- " + _inFiltered[i].costText() + "<br>";

        QString checkNum = _inFiltered[i].getCheckNum();
        if(checkNum != "") {
            html += "Check #: " + checkNum + "<br>";
        }

        QString description = _inFiltered[i].getDescription();
        if(description != "") {
            description = description.trimmed();
            description.replace("\n", "<br>");
            html += "&nbsp;&nbsp;&nbsp;&nbsp;" + description + "<br>";
        }

        if(i != _inFiltered.size()-1) {
            html += "<br>";
        }
    }
    html += "</p>";

    // Add total cost
    double total = 0;
    for(const Transaction& t : _inFiltered) {
        total += t.getCost();
    }
    html += "<br>";
    html += "<div align=left>Total amount: " +
                QString().asprintf("$%0.2f", total) +
            "</div>";

    // Create and print PDF
    QTextDocument document;
    document.setHtml(html);
    document.print(printer);
}

/******************************************************************************
 *
 *  Method inTable_headerClick: Class MainWindow
 *_____________________________________________________________________________
 *  Sorts the income Transaction table display order based the clicked column
 *      column 0: sort by category
 *      column 1: sort by date
 *      column 2: sort by amount
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    income transction table is updated
 ******************************************************************************/
void MainWindow::inTable_headerClick(int col) {
    QString cat = ui->inCat_comboBox->currentText();
    if(_inTrans.size() == 0 || (col == SORT_CAT && cat != ALL_TRANS)) {
        return;
    }

    if(col == _inSorted) {
        // reverse the table if already sorted
        reverse(_inTrans);
    } else {
        // sort the table
        _inSorted = col;
        updateInTrans();
    }

    // update display
    updateInTransTable();
}

/******************************************************************************
 *
 *  Method on_exCat_comboBox_activated: Class MainWindow
 *_____________________________________________________________________________
 *  Update the Transaction Table when the expense Category combo box is changed
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    expense tab widgets display are updated
 ******************************************************************************/
void MainWindow::on_exCat_comboBox_activated(int index) {
    updateExTrans();
    updateExTransTable();
}

/******************************************************************************
 *
 *  Method on_exCatAdd_pushButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  Prompts user for a new expense Category name and add it if valid
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    new Category is added to _expense
 ******************************************************************************/
void MainWindow::on_exCatAdd_pushButton_clicked() {
    // prompt for new category name
    bool ok;
    QString category = QInputDialog::getText(this, "New Expense Category",
                                             "Enter the category name:", QLineEdit::Normal,
                                             QDir::home().dirName(), &ok);

    if(ok && !category.isEmpty()) {
        if(!_expense.exist(category)) {
            // add valid category name
            _expense.addCategory(category);

            // update display
            updateExCat();
            ui->exCat_comboBox->setCurrentText(category);
            updateExTrans();
            updateExTransTable();
        } else {
            // invalid name
            QMessageBox::critical(this, "Error", "Category already exists");
            on_exCatAdd_pushButton_clicked();
        }
    }
}

/******************************************************************************
 *
 *  Method on_exCatRemove_pushButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  ** Requires administrative access **
 *  Removes the selected expense Category after a confirmation from the user
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    selected Category is removed from _expense
 ******************************************************************************/
void MainWindow::on_exCatRemove_pushButton_clicked() {
    if(!_admin) {
        QMessageBox::critical(this, "No Access", "Please login");
        return;
    }

    QString category = ui->exCat_comboBox->currentText();
    if(category == ALL_TRANS) {
        return;
    }

    // confirm removal with user
    auto confirmed = QMessageBox::question(this, "Confirmation", "Remove " + category + "?",
                                           QMessageBox::Yes | QMessageBox::No);

    if(confirmed == QMessageBox::Yes) {
        _expense.removeCategory(category);
        updateExCat();
        updateExTrans();
        updateExTransTable();
    }
}

/******************************************************************************
 *
 *  Method on_exCatRename_pushButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  ** Requires administrative access **
 *  Prompts user for a new expense Category name and rename the selected expense
 *      Category if valid
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    selected Category is renamed
 ******************************************************************************/
void MainWindow::on_exCatRename_pushButton_clicked() {
    if(!_admin) {
        QMessageBox::critical(this, "No Access", "Please login");
        return;
    }

    QString current = ui->exCat_comboBox->currentText();
    if(current == ALL_TRANS) {
        return;
    }

    // prompt user for new name
    bool ok;
    QString category = QInputDialog::getText(this, current,
                                             "New name:", QLineEdit::Normal,
                                             QDir::home().dirName(), &ok);

    if(ok && !category.isEmpty()) {
        int index = _expense.find(category);
        if(index == -1) {
            // valid name, change to new name
            Category temp = _expense.getCategory(current);
            temp.setCategoryName(category);
            _expense.removeCategory(current);
            _expense.addCategory(temp);

            // update display
            updateExCat();
            ui->exCat_comboBox->setCurrentText(category);
            updateExTrans();
            updateExTransTable();
        } else {
            // invalid name
            QMessageBox::critical(this, "Error", "Category already exists");
            on_exCatRename_pushButton_clicked();
        }
    }
}

/******************************************************************************
 *
 *  Method on_exTrans_tableWidget_cellClicked: Class MainWindow
 *_____________________________________________________________________________
 *  Updates the expense description text edit based on the row selected on
 *      the expense transaction table
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    expense description display is updated
 ******************************************************************************/
void MainWindow::on_exTrans_tableWidget_cellClicked(int row, int column) {
    updateExDescrip(row);
}

/******************************************************************************
 *
 *  Method on_exTransAdd_pushButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  Opens a TransactionWindow dialog and add a new Transaction based on user
 *      input
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    new Transaction is added to _expense
 ******************************************************************************/
void MainWindow::on_exTransAdd_pushButton_clicked() {
    if(_expense.getCategoryNames().size() <= 0) {
        return;
    }

    // set up and display TransactionWindow dialog
    transWindow = new TransactionWindow(this, _expense.getCategoryNames());

    if(ui->exCat_comboBox->currentText() != ALL_TRANS) {
        transWindow->setCategory(ui->exCat_comboBox->currentText());
    }
    transWindow->exec();

    // save button clicked
    if(transWindow->save()) {
        // add new Transaction
        QString category = transWindow->category();
        _expense.addTransaction(category, transWindow->cost(),
                               transWindow->description(), transWindow->date(),
                               transWindow->checkNum());

        // Update display
        updateExTrans();
        updateExTransTable();
    }
}

/******************************************************************************
 *
 *  Method on_exTransRemove_pushButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  ** Requires administrative access **
 *  Removes the selected Transaction after a user confirmation
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    selected Transaction is removed from _expense
 ******************************************************************************/
void MainWindow::on_exTransRemove_pushButton_clicked() {
    if(!_admin) {
        QMessageBox::critical(this, "No Access", "Please login");
        return;
    }

    if(!ui->exTrans_tableWidget->currentIndex().isValid()) {
        return;
    }

    int index = ui->exTrans_tableWidget->currentRow();
    Transaction t = _exFiltered[index];
    QString category = t.getCategory();

    // confirm removal
    auto confirmed = QMessageBox::question(this, "Confirmation", "Remove this transaction?\n" +
                                           t.dateFullText() + " -- " + t.costText(),
                                           QMessageBox::Yes | QMessageBox::No);

    if(confirmed == QMessageBox::Yes) {
                // remove Transaction
        _expense.removeTransaction(category, t);
        if(ui->exCat_comboBox->currentText() == ALL_TRANS) {
            _exTrans = _expense.getAllTransactions();
        } else {
            _exTrans = _expense.getTransDate(category);
        }

        // update display
        updateExTrans();
        updateExTransTable();
    }
}

/******************************************************************************
 *
 *  Method on_exTransEdit_pushButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  ** Requires administrative access **
 *  Opens a TransactionWindow dialog and edits the Transaction based on user
 *      input
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    selected Tranasction is modified
 ******************************************************************************/
void MainWindow::on_exTransEdit_pushButton_clicked() {
    if(!_admin) {
        QMessageBox::critical(this, "No Access", "Please login");
        return;
    }

    if(!ui->exTrans_tableWidget->currentIndex().isValid()) {
        return;
    }

    int i = ui->exTrans_tableWidget->currentRow();
    Transaction t = _exFiltered[i];
    QString category = t.getCategory();

    // set up and display TransactionWindow dialog
    transWindow = new TransactionWindow(_expense.getCategoryNames(), t.getDate(),
                                        t.getCost(), t.getDescription(),
                                        t.getCheckNum(), this);
    transWindow->setCategory(category);
    transWindow->exec();

    // save button clicked
    if(transWindow->save()) {
        // modify selected Transaction
        QString newCat = transWindow->category();
        _expense.removeTransaction(category, t);
        _expense.addTransaction(newCat, transWindow->cost(),
                                transWindow->description(), transWindow->date(),
                                transWindow->checkNum());

        // update display
        updateExTrans();
        updateExTransTable();
    }
}

/******************************************************************************
 *
 *  Method on_exDateUpdate_pushButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  Filters the expense Transactions table with user selected date range
 *      and updates the expense Transaction table
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    date filter is applied
 ******************************************************************************/
void MainWindow::on_exDateUpdate_pushButton_clicked() {
    _exDateFilter = true;
    updateExTransTable();
}

/******************************************************************************
 *
 *  Method on_exDateClear_pushButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  Clears the date filter and updates the expense Transaction table
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    date filter is removed
 ******************************************************************************/
void MainWindow::on_exDateClear_pushButton_clicked() {
    _exDateFilter = false;
    updateExTransTable();
}

/******************************************************************************
 *
 *  Method on_exSearchKey_pushButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  Filters the expense Transactions table with user inputted key phrase
 *      and updates the expense Transaction table
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    keyword filter is applied
 ******************************************************************************/
void MainWindow::on_exSearchKey_pushButton_clicked() {
    if(ui->exKey_lineEdit->text() == "") {
        on_exClearKey_pushButton_clicked();
        return;
    }
    _exKeyword = true;
    updateExTransTable();
}

/******************************************************************************
 *
 *  Method on_exClearKey_pushButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  Clears the keyword filter and updates the expense Transaction table
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    keyword filter is removed
 ******************************************************************************/
void MainWindow::on_exClearKey_pushButton_clicked() {
    if(!_exKeyword) {
        return;
    }

    _exKeyword = false;
    ui->exKey_lineEdit->clear();
    updateExTransTable();

    ui->exTransAdd_pushButton->setDefault(true);
}

/******************************************************************************
 *
 *  Method on_exKey_lineEdit_returnPressed: Class MainWindow
 *_____________________________________________________________________________
 *  Filters the expense Transactions table with user inputted key phrase
 *      and updates the expense Transaction table
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    keyword filter is applied
 ******************************************************************************/
void MainWindow::on_exKey_lineEdit_returnPressed() {
    ui->exTransAdd_pushButton->setDefault(false);
    on_exSearchKey_pushButton_clicked();
}

/******************************************************************************
 *
 *  Method on_exReport_pushButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  ** Requires administrative access **
 *  Generates a pdf report based on user selected expense category, sorting
 *      method, and date and key phrase filters
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    A pdf report to print is generated
 ******************************************************************************/
void MainWindow::on_exReport_pushButton_clicked() {
    if(!_admin) {
        QMessageBox::critical(this, "No Access", "Please login");
        return;
    }

    // set up printer and dialog
    QPrinter *printer = new QPrinter(QPrinter::HighResolution);
    printer->setPageSize(QPageSize::A4);

    QPrintDialog dialog(printer, this);
    dialog.setWindowTitle("Print Document");
    if(dialog.exec() == QDialog::Rejected) {
        return;
    }

    QString cat = ui->exCat_comboBox->currentText();
    if(cat == ALL_TRANS) {
        cat = "All";
    }

    // Create pdf with html format
    QString html = "";

    // Add Header
    if(_exDateFilter) {
        html = "<div align=right>";

        QDate start = ui->exStartDate_dateEdit->date();
        QDate end = ui->exEndDate_dateEdit->date();

        html += start.toString("MM/dd/yyyy") + " - " +
                end.toString("MM/dd/yyyy") + "</div>";
    }

    html += "<div align=left>Category: " +
                cat +
            "</div>";

    if(_exKeyword) {
        QString keyword = ui->exKey_lineEdit->text();
        html += "<div align=left>Keyword: " +
                    keyword +
                "</div>";
    }

    // Add Title
    html += "<h2 align=center> Expense Report</h2>";

    // Add Transactions
    cat = ui->exCat_comboBox->currentText();
    html += "<p align=left>";
    for(unsigned i = 0; i < _exFiltered.size(); i++) {
        if(cat == ALL_TRANS) {
            html += _exFiltered[i].getCategory() + "<br>";
        }
        html += _exFiltered[i].dateShortText() + " -- " +
                _exFiltered[i].costText() + "<br>";

        QString checkNum = _exFiltered[i].getCheckNum();
        if(checkNum != "") {
            html += "Check #: " + checkNum + "<br>";
        }

        QString description = _exFiltered[i].getDescription();
        if(description != "") {
            description = description.trimmed();
            description.replace("\n", "<br>");
            html += "&nbsp;&nbsp;&nbsp;&nbsp;" + description + "<br>";
        }

        if(i != _exFiltered.size()-1) {
            html += "<br>";
        }
    }
    html += "</p>";

    // Add total cost
    double total = 0;
    for(const Transaction& t : _exFiltered) {
        total += t.getCost();
    }
    html += "<br>";
    html += "<div align=left>Total amount: " +
                QString().asprintf("$%0.2f", total) +
            "</div>";

    // Create and print PDF
    QTextDocument document;
    document.setHtml(html);
    document.print(printer);
}

/******************************************************************************
 *
 *  Method exTable_headerClick: Class MainWindow
 *_____________________________________________________________________________
 *  Sorts the expense Transaction table display order based the clicked column
 *      column 0: sort by category
 *      column 1: sort by date
 *      column 2: sort by amount
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    expense transction table is updated
 ******************************************************************************/
void MainWindow::exTable_headerClick(int col) {
    QString cat = ui->exCat_comboBox->currentText();
    if(_exTrans.size() == 0 || (col == SORT_CAT && cat != ALL_TRANS)) {
        return;
    }

    if(col == _exSorted) {
        // reverse the table if already sorted
        reverse(_exTrans);
    } else {
        // sort the table
        _exSorted = col;
        updateExTrans();
    }

    // update display
    updateExTransTable();
}

/******************************************************************************
 *
 *  Method on_tabWidget_currentChanged: Class MainWindow
 *_____________________________________________________________________________
 *  Updates the default buttons based the the current tab
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    default buttons of the window are updated
 ******************************************************************************/
void MainWindow::on_tabWidget_currentChanged(int index) {
    if(index == 0) {
        ui->inTransAdd_pushButton->setDefault(true);
    } else if(index == 1) {
        ui->exTransAdd_pushButton->setDefault(true);
    } else if(index == 2) {
        ui->fontUpdate_pushButton->setDefault(true);
    }
}

/******************************************************************************
 *
 *  Method on_inReadFile_pushButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  ** Requires administrative access **
 *  Open a dialog for user to choose files and add income Transactions read
 *      from the files
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    Transactions listed in the file(s) are added to _income
 ******************************************************************************/
void MainWindow::on_inReadFile_pushButton_clicked() {
    if(!_admin) {
        QMessageBox::critical(this, "No Access", "Please login");
        return;
    }

    // get files from user
    QStringList files = QFileDialog::getOpenFileNames(this, "Open files",
                                                      "/Users/",
                                                      "Text files (*.txt)");

    if(files.size() < 1) {
        return;
    }

    // read files
    for(QString path : files) {
        QFile file(path);
        QFileInfo info(file);

        if(!info.isFile() || !path.endsWith(".txt")) {
            continue;
        }

        // add to Tracker
        readFile(file, _income);
    }

    // update display
    ui->inCat_comboBox->setCurrentText(ALL_TRANS);
    _inSorted = SORT_CAT;
    updateInCat();
    updateInTrans();
    updateInTransTable();
}

/******************************************************************************
 *
 *  Method on_exReadFile_pushButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  ** Requires administrative access **
 *  Open a dialog for user to choose files and add expense Transactions read
 *      from the files
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    Transactions listed in the file(s) are added to _expense
 ******************************************************************************/
void MainWindow::on_exReadFile_pushButton_clicked() {
    if(!_admin) {
        QMessageBox::critical(this, "No Access", "Please login");
        return;
    }

    // get files from user
    QStringList files = QFileDialog::getOpenFileNames(this, "Open files",
                                                      "/Users/",
                                                      "Text files (*.txt)");

    if(files.size() < 1) {
        return;
    }

    // read files
    for(QString path : files) {
        QFile file(path);
        QFileInfo info(file);

        if(!info.isFile() || !path.endsWith(".txt")) {
            continue;
        }

        // add to Tracker
        readFile(file, _expense);
    }

    // update display
    ui->inCat_comboBox->setCurrentText(ALL_TRANS);
    _exSorted = SORT_CAT;
    updateExCat();
    updateExTrans();
    updateExTransTable();
}

/******************************************************************************
 *
 *  Method on_inGetFile_pushButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  ** Requires administrative access **
 *  Downloads the income Transaction files to the Downloads folder
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    Income Transactions files are downloaded
 ******************************************************************************/
void MainWindow::on_inGetFile_pushButton_clicked() {
    if(!_admin) {
        QMessageBox::critical(this, "No Access", "Please login");
        return;
    }

    // income files location
    QString inPath = qApp->applicationDirPath() + "/Income/";
    QDir inDir(inPath);

    // files destination
    QString destination = QDir::homePath() + "/Downloads";
    QDir dir(destination);

    // check for valid folder name
    QString folderName = "Income";
    if(dir.exists(folderName)) {
        int i = 1;
        QString temp = folderName + "(" + QString::number(i) + ")";
        while(dir.exists(temp)){
            temp = folderName + "(" + QString::number(++i) + ")";
        }
        folderName = temp;
    }
    dir.mkdir(folderName);

    // copy each file to the destination folder
    foreach(QFileInfo info, inDir.entryInfoList()) {
        if(!info.isFile()) {
            continue;
        }
        QFile file(inPath + info.fileName());

        file.copy(destination + "/" + folderName + "/" + info.fileName());
    }

    // display success message
    QMessageBox::information(this, "Success", "Files added to Downloads folder");
}

/******************************************************************************
 *
 *  Method on_exGetFile_pushButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  ** Requires administrative access **
 *  Downloads the expense Transaction files to the Downloads folder
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    Expense Transactions files are downloaded
 ******************************************************************************/
void MainWindow::on_exGetFile_pushButton_clicked() {
    if(!_admin) {
        QMessageBox::critical(this, "No Access", "Please login");
        return;
    }

    // expense files location
    QString exPath = qApp->applicationDirPath() + "/Expense/";
    QDir exDir(exPath);

    // files destination
    QString destination = QDir::homePath() + "/Downloads";
    QDir dir(destination);

    // check for valid folder name
    QString folderName = "Expense";
    if(dir.exists(folderName)) {
        int i = 1;
        QString temp = folderName + "(" + QString::number(i) + ")";
        while(dir.exists(temp)){
            temp = folderName + "(" + QString::number(++i) + ")";
        }
        folderName = temp;
    }
    dir.mkdir(folderName);

    // copy each file to the destination folder
    foreach(QFileInfo info, exDir.entryInfoList()) {
        if(!info.isFile()) {
            continue;
        }
        QFile file(exPath + info.fileName());

        file.copy(destination + "/" + folderName + "/" + info.fileName());
    }

    // display success message
    QMessageBox::information(this, "Success", "Files added to Downloads folder");
}

/******************************************************************************
 *
 *  Method on_fontUpdate_pushButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  Updates the font family and size of the application based on the selected
 *      font and size combo box texts
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    Application font is updated
 ******************************************************************************/
void MainWindow::on_fontUpdate_pushButton_clicked() {
    QFont font = ui->fontComboBox->currentFont();
    font.setPointSize(ui->fontSize_comboBox->currentText().toInt());
    QApplication::setFont(font);
}

/******************************************************************************
 *
 *  Method on_accountsEdit_pushButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  ** Requires administrative access **
 *  Opens the UsersWindow Dialog and updates _users based on user input
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _users is modified
 ******************************************************************************/
void MainWindow::on_accountsEdit_pushButton_clicked() {
    if(!_admin) {
        QMessageBox::critical(this, "No Access", "Please login");
        return;
    }

    // set up UsersWindow dialog
    usersWindow = new UsersWindow(this, _users);
    usersWindow->exec();

    // update _users
    _users = usersWindow->getUsers();
}

/******************************************************************************
 *
 *  Method on_exit_pushButton_clicked: Class MainWindow
 *_____________________________________________________________________________
 *  Close the main window and exits program
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    MainWindow is closed
 ******************************************************************************/
void MainWindow::on_exit_pushButton_clicked() {
    this->close();
}
