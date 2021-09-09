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

MainWindow::MainWindow(QWidget *parent, const std::map<QString, QString>& users, bool admin) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
    // set up default variables
    ui->setupUi(this);
    this->setWindowTitle("Transaction Tracker");

    _users = users;
    _admin = admin;
    inSorted = SORT_CAT;
    exSorted = SORT_CAT;
    inDateFilter = false;
    exDateFilter = false;
    inKeyword = false;
    exKeyword = false;

    // create file directories
    if(!QDir("Income").exists()) {
        QDir().mkdir("Income");
    }
    if(!QDir("Expense").exists()) {
        QDir().mkdir("Expense");
    }



//    QString inPath = qApp->applicationDirPath() + "/Income/";
//    QString exPath = qApp->applicationDirPath() + "/Expense/";

//    QDir inDir(inPath);
//    QDir exDir(exPath);

//    foreach(QFileInfo info, inDir.entryInfoList()) {
//        if(!info.isFile()) {
//            continue;
//        }

//        inDir.remove(info.fileName());
//    }
//    foreach(QFileInfo info, exDir.entryInfoList()) {
//        if(!info.isFile()) {
//            continue;
//        }

//        exDir.remove(info.fileName());
//    }

//    for(int i = 1; i < 6; i++) {
//        QFile temp(inPath + "test" + QString::number(i) + ".txt");
//        temp.open(QIODevice::WriteOnly);
//        QString datetime = "2021:05:" + QString::number(i) + ":3:54:10:34\n";
//        temp.write(datetime.toUtf8());
//        QString s = QString::number(i) + "\n";
//        temp.write(s.toUtf8());
//        temp.write("testtest\\\\ntest\n");
//        temp.close();
//    }

//    for(int i = 1; i < 6; i++) {
//        QFile temp(exPath + "test" + QString::number(i) + ".txt");
//        temp.open(QIODevice::WriteOnly);
//        QString datetime = "2021:05:" + QString::number(i) + ":3:54:10:34\n";
//        temp.write(datetime.toUtf8());
//        QString s = QString::number(i) + "\n";
//        temp.write(s.toUtf8());
//        temp.write("test2\\\\ntest\\\\nok\n");
//        temp.close();
//    }

//    foreach(QFileInfo info, inDir.entryInfoList()) {
//        if(info.isFile()) {
//            QString name = info.fileName();
//            QFile file(inPath + name);
//            name.chop(4);

//            file.open(QIODevice::ReadOnly);
//            file.close();
//        }
//    }

//    QFileInfoList list = inDir.entryInfoList();
//    qDebug() << "     Bytes Filename";
//    for (int i = 0; i < list.size(); ++i) {
//        QFileInfo fileInfo = list.at(i);

//        if(!fileInfo.isFile()) {
//            continue;
//        }
//        qDebug() << qPrintable(QString("%1 %2").arg(fileInfo.size(), 10)
//                                                .arg(fileInfo.fileName()));
//        QFile file(inPath + fileInfo.fileName());
//        file.open(QIODevice::ReadOnly);
//        file.close();
//    }

    // read income files
    QString inPath = qApp->applicationDirPath() + "/Income/";
    QDir inDir(inPath);
    foreach(QFileInfo info, inDir.entryInfoList(QDir::Files | QDir::Hidden)) {
        if(!info.isFile()) {
            continue;
        }
        QFile file(inPath + info.fileName());
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
        readFile(file, _expense);
    }

//    _income.addCategory("Income 1");
//    _income.addCategory("Income 2");
//    _income.addCategory("Income 3");
//    _income.addCategory("Income 4");
//    _expense.addCategory("Expense 1");
//    _expense.addCategory("Expense 2");
//    _expense.addCategory("Expense 3");
//    _expense.addCategory("Expense 4");
//    int y = 2021, m = 7, d = 1;
//    for(d = 1; d < 31; d++) {
//        double amount = y;
//        amount /= m * d;

//        QString description;
//        if(d % 3 == 0) {
//            description = "abc";
//        } else if(d % 3 == 1) {
//            description = "bcd";
//        } else {
//            description = "def";
//        }

//        if(d%5 == 0) {
//            description += "\n" + description;
//        }

//        QDate date(y, m, d);

//        Transaction t(amount, description, date);
//        _income.addTransaction("Income 1", t);
//        _expense.addTransaction("Expense 1", t);

//        if(d % 4 == 1) {
//            _income.addTransaction("Income 2", t);
//            _expense.addTransaction("Expense 2", t);
//        }
//        if(d % 5 == 1) {
//            _income.addTransaction("Income 3", t);
//            _expense.addTransaction("Expense 3", t);
//        }
//    }
//    qDebug() << _income.size();

    // set up combo boxes
    updateInCat();
    updateExCat();

    // set up tables
    ui->inTrans_tableWidget->setColumnCount(3);
    ui->exTrans_tableWidget->setColumnCount(3);
    QStringList labels;
    labels << "Category" << "Date" << "Amount";
    ui->inTrans_tableWidget->setHorizontalHeaderLabels(labels);
    ui->inTrans_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->inTrans_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->exTrans_tableWidget->setHorizontalHeaderLabels(labels);
    ui->exTrans_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->exTrans_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    updateInTrans();
    updateInTransTable();
    updateExTrans();
    updateExTransTable();

    connect(ui->inTrans_tableWidget->horizontalHeader(), SIGNAL(sectionClicked(int)), SLOT(inTable_headerClick(int)));
    connect(ui->exTrans_tableWidget->horizontalHeader(), SIGNAL(sectionClicked(int)), SLOT(exTable_headerClick(int)));


    // set up default calendar dates
    ui->inStartDate_dateEdit->setDate(QDate::currentDate());
    ui->inEndDate_dateEdit->setDate(QDate::currentDate());
    ui->exStartDate_dateEdit->setDate(QDate::currentDate());
    ui->exEndDate_dateEdit->setDate(QDate::currentDate());

    // set default button
    ui->inTransAdd_pushButton->setDefault(true);

    // set combobox defaults
    ui->fontComboBox->setCurrentFont(QFont("Arial"));
    ui->fontSize_comboBox->setCurrentText("10");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::readFile(QFile& file, Tracker& tracker) {
    QString category;

    // open file
    if(file.open(QIODevice::ReadOnly)) {
        if(!file.atEnd()) {
            category = file.readLine().trimmed();
            tracker.addCategory(category);
        }

        // add each item from file
        while(!file.atEnd()) {
            QString date = file.readLine().trimmed();
            QString timestamp = file.readLine().trimmed();
            QString cost = file.readLine().trimmed();
            QString description = file.readLine().trimmed();
            description.replace("\\\\n", "\n");

            QStringList list = date.split("/");
            QDate d(list[0].toInt(), list[1].toInt(), list[2].toInt());

            list = timestamp.split(":");
            QDate timestampD(list[0].toInt(), list[1].toInt(), list[2].toInt());
            QTime timestampT(list[3].toInt(), list[4].toInt(), list[5].toInt(), list[6].toInt());
            QDateTime t(timestampD, timestampT);


            tracker.addTransaction(category, cost.toDouble(), description, d, t);
        }

        file.close();
    } else {
        qDebug() << category + "Failed to open";
    }
}

void MainWindow::updateInCat() {
    ui->inCat_comboBox->clear();
    ui->inCat_comboBox->addItem(ALL_TRANS);

    for(const QString& cat : _income.getCategoryNames()) {
        ui->inCat_comboBox->addItem(cat);
    }
}

void MainWindow::updateExCat() {
    ui->exCat_comboBox->clear();
    ui->exCat_comboBox->addItem(ALL_TRANS);

    for(const QString& cat : _expense.getCategoryNames()) {
        ui->exCat_comboBox->addItem(cat);
    }
}

void MainWindow::updateInTrans() {
    QString cat = ui->inCat_comboBox->currentText();
    if(cat == "") {
        inTrans.clear();
        return;
    }

    if(cat == ALL_TRANS) {
        if(inSorted == SORT_CAT) {
            inTrans = _income.getAllTransactions();
        } else if (inSorted == SORT_AMOUNT) {
            inTrans = _income.getTransAmountSorted();
        } else {
            inTrans = _income.getTransDateSorted();
            inSorted = SORT_DATE;
        }
    } else {
        if(inSorted == SORT_AMOUNT) {
            inTrans = _income.getTransAmount(cat);
        } else {
            inTrans = _income.getTransDate(cat);
            inSorted = SORT_DATE;
        }
    }

}

void MainWindow::updateExTrans() {
    QString cat = ui->exCat_comboBox->currentText();
    if(cat == "") {
        exTrans.clear();
        return;
    }

    if(cat == ALL_TRANS) {
        if(exSorted == SORT_CAT) {
            exTrans = _expense.getAllTransactions();
        } else if (exSorted == SORT_AMOUNT) {
            exTrans = _expense.getTransAmountSorted();
        } else {
            exTrans = _expense.getTransDateSorted();
            exSorted = SORT_DATE;
        }
    } else {
        if(exSorted == SORT_AMOUNT) {
            exTrans = _expense.getTransAmount(cat);
        } else {
            exTrans = _expense.getTransDate(cat);
            exSorted = SORT_DATE;
        }
    }
}

void MainWindow::updateInTransTable() {
    // clear table
    ui->inTrans_tableWidget->setRowCount(0);

    // Apply filters
    inFiltered = inTrans;
    if(inKeyword) {
        inFiltered = filterKeyword(inFiltered, ui->inKey_lineEdit->text());
    }

    if(inDateFilter) {
        QDate start = ui->inStartDate_dateEdit->date();
        QDate end = ui->inEndDate_dateEdit->date();
        inFiltered = filterDate(inFiltered, start, end);
    }

    // Add to table
    for(unsigned i = 0; i < inFiltered.size(); i++) {
        ui->inTrans_tableWidget->insertRow(i);
        QTableWidgetItem *category = new QTableWidgetItem;
        QTableWidgetItem *date = new QTableWidgetItem;
        QTableWidgetItem *cost = new QTableWidgetItem;

        category->setText(inFiltered[i].getCategory());
        date->setText(inFiltered[i].dateShortText());
        cost->setText(inFiltered[i].costText());

        ui->inTrans_tableWidget->setItem(i, 0, category);
        ui->inTrans_tableWidget->setItem(i, 1, date);
        ui->inTrans_tableWidget->setItem(i, 2, cost);
    }

    // set up description
    if(inFiltered.size() > 0) {
        updateInDescrip(0);
        ui->inTrans_tableWidget->selectRow(0);
    } else {
        ui->inDescrip_textEdit->clear();
    }
}

void MainWindow::updateExTransTable() {
    // clear table
    ui->exTrans_tableWidget->setRowCount(0);

    // Apply filters
    exFiltered = exTrans;
    if(exKeyword) {
        exFiltered = filterKeyword(exFiltered, ui->exKey_lineEdit->text());
    }

    if(exDateFilter) {
        QDate start = ui->exStartDate_dateEdit->date();
        QDate end = ui->exEndDate_dateEdit->date();
        exFiltered = filterDate(exFiltered, start, end);
    }

    // Add to table
    for(unsigned i = 0; i < exFiltered.size(); i++) {
        ui->exTrans_tableWidget->insertRow(i);
        QTableWidgetItem *category = new QTableWidgetItem;
        QTableWidgetItem *date = new QTableWidgetItem;
        QTableWidgetItem *cost = new QTableWidgetItem;

        category->setText(exFiltered[i].getCategory());
        date->setText(exFiltered[i].dateShortText());
        cost->setText(exFiltered[i].costText());

        ui->exTrans_tableWidget->setItem(i, 0, category);
        ui->exTrans_tableWidget->setItem(i, 1, date);
        ui->exTrans_tableWidget->setItem(i, 2, cost);
    }

    // set up description
    if(exFiltered.size() > 0) {
        updateExDescrip(0);
        ui->exTrans_tableWidget->selectRow(0);
    } else {
        ui->exDescrip_textEdit->clear();
    }
}

void MainWindow::updateInDescrip(int index) {
    ui->inDescrip_textEdit->clear();
    ui->inDescrip_textEdit->setText(inFiltered[index].toString());
}

void MainWindow::updateExDescrip(int index) {
    ui->exDescrip_textEdit->clear();
    ui->exDescrip_textEdit->setText(exFiltered[index].toString());
}

std::vector<Transaction> MainWindow::filterKeyword(const std::vector<Transaction>& t,
                                                   QString keyword) {
    std::vector<Transaction> transactions;

    for(const Transaction& trans : t) {
        if(trans.contains(keyword)) {
            transactions.push_back(trans);
        }
    }

    return transactions;
}

std::vector<Transaction> MainWindow::filterDate(const std::vector<Transaction>& t,
                                                const QDate& start, const QDate& end) {
    std::vector<Transaction> transactions;

    for(const Transaction& trans : t) {
        if(trans.getDate() >= start && trans.getDate() <= end) {
            transactions.push_back(trans);
        }
    }

    return transactions;
}

void MainWindow::reverse(std::vector<Transaction>& t) {
    std::reverse(t.begin(), t.end());
}


const Tracker& MainWindow::getInTracker() const {
    return _income;
}

const Tracker& MainWindow::getExTracker() const {
    return _expense;
}

const std::map<QString, QString>& MainWindow::getUsers() const {
    return _users;
}

void MainWindow::on_inCat_comboBox_activated(int index) {
    updateInTrans();
    updateInTransTable();
}

void MainWindow::on_inCatAdd_pushButton_clicked() {
    bool ok;
    QString category = QInputDialog::getText(this, "New Income Category",
                                             "Enter the category name:", QLineEdit::Normal,
                                             QDir::home().dirName(), &ok);

    if(ok && !category.isEmpty()) {
        if(!_income.exist(category)) {
            _income.addCategory(category);
            updateInCat();
            ui->inCat_comboBox->setCurrentText(category);
            updateInTrans();
            updateInTransTable();
        } else {
            QMessageBox::critical(this, "Error", "Category already exists");
            on_inCatAdd_pushButton_clicked();
        }
    }
}

void MainWindow::on_inCatRemove_pushButton_clicked() {
    if(!_admin) {
        QMessageBox::critical(this, "Error", "No access");
        return;
    }

    QString category = ui->inCat_comboBox->currentText();
    if(category == ALL_TRANS) {
        return;
    }

    auto confirmed = QMessageBox::question(this, "Confirmation", "Do you really want to remove " + category,
                          QMessageBox::Yes | QMessageBox::No);

    if(confirmed == QMessageBox::Yes) {
        _income.removeCategory(category);
        updateInCat();
        updateInTrans();
        updateInTransTable();
    }
}

void MainWindow::on_inCatRename_pushButton_clicked() {
    if(!_admin) {
        QMessageBox::critical(this, "Error", "No access");
        return;
    }

    QString current = ui->inCat_comboBox->currentText();
    if(current == ALL_TRANS) {
        return;
    }

    bool ok;
    QString category = QInputDialog::getText(this, current,
                                             "New name:", QLineEdit::Normal,
                                             QDir::home().dirName(), &ok);
    if(ok && !category.isEmpty()) {
        int index = _income.find(category);
        if(index == -1) {
            Category temp = _income.getCategory(current);
            temp.setCategoryName(category);
            _income.removeCategory(current);
            _income.addCategory(temp);

            updateInCat();
            ui->inCat_comboBox->setCurrentText(category);
            updateInTrans();
            updateInTransTable();
        } else {
            QMessageBox::critical(this, "Error", "Category already exists");
            on_inCatRename_pushButton_clicked();
        }
    }
}

void MainWindow::on_inTrans_tableWidget_cellClicked(int row, int column) {
    updateInDescrip(row);
}

void MainWindow::on_inTransAdd_pushButton_clicked() {
    if(_income.getCategoryNames().size() <= 0) {
        return;
    }

    transWindow = new TransactionWindow(this, _income.getCategoryNames());

    if(ui->inCat_comboBox->currentText() != ALL_TRANS) {
        transWindow->setCategory(ui->inCat_comboBox->currentText());
    }
    transWindow->exec();

    if(transWindow->save()) {
        QString category = transWindow->category();
        _income.addTransaction(category, transWindow->cost(),
                               transWindow->description(), transWindow->date());

        updateInTrans();
        updateInTransTable();
    }
}

void MainWindow::on_inTransRemove_pushButton_clicked() {
    if(!_admin) {
        QMessageBox::critical(this, "Error", "No access");
        return;
    }

    if(!ui->inTrans_tableWidget->currentIndex().isValid()) {
        return;
    }

    int index = ui->inTrans_tableWidget->currentRow();
    Transaction t = inFiltered[index];
    QString category = t.getCategory();

    auto confirmed = QMessageBox::question(this, "Confirmation", "Remove this transaction?\n" +
                                           t.dateFullText() + " -- " + t.costText(),
                                           QMessageBox::Yes | QMessageBox::No);

    if(confirmed == QMessageBox::Yes) {
        _income.removeTransaction(category, t);
        if(ui->inCat_comboBox->currentText() == ALL_TRANS) {
            inTrans = _income.getAllTransactions();
        } else {
            inTrans = _income.getTransDate(category);
        }

        updateInTrans();
        updateInTransTable();
    }
}

void MainWindow::on_inTransEdit_pushButton_clicked() {
    if(!_admin) {
        QMessageBox::critical(this, "Error", "No access");
        return;
    }

    if(!ui->inTrans_tableWidget->currentIndex().isValid()) {
        return;
    }

    int i = ui->inTrans_tableWidget->currentRow();
    Transaction t = inFiltered[i];
    QString category = t.getCategory();

    transWindow = new TransactionWindow(_income.getCategoryNames(), inTrans[i].getDate(),
                                        inTrans[i].getCost(), inTrans[i].getDescription(), this);
    transWindow->setCategory(category);
    transWindow->exec();

    if(transWindow->save()) {
        QString newCat = transWindow->category();
        _income.removeTransaction(category, t);
        _income.addTransaction(newCat, transWindow->cost(),
                               transWindow->description(), transWindow->date());

        ui->inCat_comboBox->setCurrentText(newCat);
        updateInTrans();
        updateInTransTable();
    }
}

void MainWindow::on_inDateUpdate_pushButton_clicked() {
    inDateFilter = true;
    updateInTransTable();
}


void MainWindow::on_inDateClear_pushButton_clicked() {
    inDateFilter = false;
    updateInTransTable();
}


void MainWindow::on_inSearchKey_pushButton_clicked() {
    if(ui->inKey_lineEdit->text() == "") {
        on_inClearKey_pushButton_clicked();
        return;
    }
    inKeyword = true;
    updateInTransTable();
}


void MainWindow::on_inClearKey_pushButton_clicked() {
    if(!inKeyword) {
        return;
    }

    inKeyword = false;
    ui->inKey_lineEdit->clear();
    updateInTransTable();

    ui->inTransAdd_pushButton->setDefault(true);
}


void MainWindow::on_inKey_lineEdit_returnPressed() {
    ui->inTransAdd_pushButton->setDefault(false);
    on_inSearchKey_pushButton_clicked();
}

void MainWindow::inTable_headerClick(int col) {
    QString cat = ui->inCat_comboBox->currentText();
    if(inTrans.size() == 0 || (col == SORT_CAT && cat != ALL_TRANS)) {
        return;
    }

    if(col == inSorted) {
        // reverse the table if already sorted
        reverse(inTrans);
    } else {
        inSorted = col;
        updateInTrans();
    }

    updateInTransTable();
}


void MainWindow::on_exCat_comboBox_activated(int index) {
    updateExTrans();
    updateExTransTable();
}

void MainWindow::on_exCatAdd_pushButton_clicked() {
    bool ok;
    QString category = QInputDialog::getText(this, "New Expense Category",
                                             "Enter the category name:", QLineEdit::Normal,
                                             QDir::home().dirName(), &ok);

    if(ok && !category.isEmpty()) {
        if(!_expense.exist(category)) {
            _expense.addCategory(category);
            updateExCat();
            ui->exCat_comboBox->setCurrentText(category);
            updateExTrans();
            updateExTransTable();
        } else {
            QMessageBox::critical(this, "Error", "Category already exists");
            on_exCatAdd_pushButton_clicked();
        }
    }
}

void MainWindow::on_exCatRemove_pushButton_clicked() {
    if(!_admin) {
        QMessageBox::critical(this, "Error", "No access");
        return;
    }

    QString category = ui->exCat_comboBox->currentText();
    if(category == ALL_TRANS) {
        return;
    }

    auto confirmed = QMessageBox::question(this, "Confirmation", "Remove " + category + "?",
                                           QMessageBox::Yes | QMessageBox::No);

    if(confirmed == QMessageBox::Yes) {
        _expense.removeCategory(category);
        updateExCat();
        updateExTrans();
        updateExTransTable();
    }
}

void MainWindow::on_exCatRename_pushButton_clicked() {
    if(!_admin) {
        QMessageBox::critical(this, "Error", "No access");
        return;
    }

    QString current = ui->exCat_comboBox->currentText();
    if(current == ALL_TRANS) {
        return;
    }

    bool ok;
    QString category = QInputDialog::getText(this, current,
                                             "New name:", QLineEdit::Normal,
                                             QDir::home().dirName(), &ok);
    if(ok && !category.isEmpty()) {
        int index = _expense.find(category);
        if(index == -1) {
            Category temp = _expense.getCategory(current);
            temp.setCategoryName(category);
            _expense.removeCategory(current);
            _expense.addCategory(temp);

            updateExCat();
            ui->exCat_comboBox->setCurrentText(category);
            updateExTrans();
            updateExTransTable();
        } else {
            QMessageBox::critical(this, "Error", "Category already exists");
            on_exCatRename_pushButton_clicked();
        }
    }
}

void MainWindow::on_exTrans_tableWidget_cellClicked(int row, int column) {
    updateExDescrip(row);
}

void MainWindow::on_exTransAdd_pushButton_clicked() {
    if(_expense.getCategoryNames().size() <= 0) {
        return;
    }

    transWindow = new TransactionWindow(this, _expense.getCategoryNames());

    if(ui->exCat_comboBox->currentText() != ALL_TRANS) {
        transWindow->setCategory(ui->exCat_comboBox->currentText());
    }
    transWindow->exec();

    if(transWindow->save()) {
        QString category = transWindow->category();
        _expense.addTransaction(category, transWindow->cost(),
                               transWindow->description(), transWindow->date());

        updateExTrans();
        updateExTransTable();
    }
}

void MainWindow::on_exTransRemove_pushButton_clicked() {
    if(!_admin) {
        QMessageBox::critical(this, "Error", "No access");
        return;
    }

    if(!ui->exTrans_tableWidget->currentIndex().isValid()) {
        return;
    }

    int index = ui->exTrans_tableWidget->currentRow();
    Transaction t = exFiltered[index];
    QString category = t.getCategory();

    auto confirmed = QMessageBox::question(this, "Confirmation", "Remove this transaction?\n" +
                                           t.dateFullText() + " -- " + t.costText(),
                                           QMessageBox::Yes | QMessageBox::No);

    if(confirmed == QMessageBox::Yes) {
        _expense.removeTransaction(category, t);
        if(ui->exCat_comboBox->currentText() == ALL_TRANS) {
            exTrans = _expense.getAllTransactions();
        } else {
            exTrans = _expense.getTransDate(category);
        }

        updateExTrans();
        updateExTransTable();
    }
}

void MainWindow::on_exTransEdit_pushButton_clicked() {
    if(!_admin) {
        QMessageBox::critical(this, "Error", "No access");
        return;
    }

    if(!ui->exTrans_tableWidget->currentIndex().isValid()) {
        return;
    }

    int i = ui->exTrans_tableWidget->currentRow();
    Transaction t = exFiltered[i];
    QString category = t.getCategory();

    transWindow = new TransactionWindow(_expense.getCategoryNames(), exTrans[i].getDate(),
                                        exTrans[i].getCost(), exTrans[i].getDescription(), this);
    transWindow->setCategory(category);
    transWindow->exec();

    if(transWindow->save()) {
        QString newCat = transWindow->category();
        _expense.removeTransaction(category, t);
        _expense.addTransaction(transWindow->category(), transWindow->cost(),
                               transWindow->description(), transWindow->date());

        ui->exCat_comboBox->setCurrentText(newCat);
        updateExTrans();
        updateExTransTable();
    }
}

void MainWindow::on_exDateUpdate_pushButton_clicked() {
    exDateFilter = true;
    updateExTransTable();
}

void MainWindow::on_exDateClear_pushButton_clicked() {
    exDateFilter = false;
    updateExTransTable();
}

void MainWindow::on_exSearchKey_pushButton_clicked() {
    if(ui->exKey_lineEdit->text() == "") {
        on_exClearKey_pushButton_clicked();
        return;
    }
    exKeyword = true;
    updateExTransTable();
}

void MainWindow::on_exClearKey_pushButton_clicked() {
    if(!exKeyword) {
        return;
    }

    exKeyword = false;
    ui->exKey_lineEdit->clear();
    updateExTransTable();

    ui->exTransAdd_pushButton->setDefault(true);
}

void MainWindow::on_exKey_lineEdit_returnPressed() {
    ui->exTransAdd_pushButton->setDefault(false);
    on_exSearchKey_pushButton_clicked();
}

void MainWindow::exTable_headerClick(int col) {
    QString cat = ui->exCat_comboBox->currentText();
    if(exTrans.size() == 0 || (col == SORT_CAT && cat != ALL_TRANS)) {
        return;
    }

    if(col == exSorted) {
        // reverse the table if already sorted
        reverse(exTrans);
    } else {
        exSorted = col;
        updateExTrans();
    }

    updateExTransTable();
}


void MainWindow::on_tabWidget_currentChanged(int index) {
    if(index == 0) {
        ui->inTransAdd_pushButton->setDefault(true);
    } else if(index == 1) {
        ui->exTransAdd_pushButton->setDefault(true);
    } else if(index == 2) {
        ui->fontUpdate_pushButton->setDefault(true);
    }
}

void MainWindow::on_inReadFile_pushButton_clicked() {
    if(!_admin) {
        QMessageBox::critical(this, "Error", "No access");
        return;
    }

    //get files
    QStringList files = QFileDialog::getOpenFileNames(this, "Open files", "/Users/", "Text files (*.txt)");
    //QStringList files = QFileDialog::getOpenFileNames(this, "Open files", "C://", "Text files (*.txt)");

    if(files.size() < 1) {
        return;
    }

    //read files
    for(QString path : files) {
        QFile file(path);
        QFileInfo info(file);

        if(!info.isFile() || !path.endsWith(".txt")) {
            continue;
        }

        readFile(file, _income);
    }

    //update
    ui->inCat_comboBox->setCurrentText(ALL_TRANS);
    inSorted = SORT_CAT;
    updateInCat();
    updateInTrans();
    updateInTransTable();
}

void MainWindow::on_exReadFile_pushButton_clicked() {
    if(!_admin) {
        QMessageBox::critical(this, "Error", "No access");
        return;
    }

    //get files
    QStringList files = QFileDialog::getOpenFileNames(this, "Open files", "/Users/", "Text files (*.txt)");
    //QStringList files = QFileDialog::getOpenFileNames(this, "Open files", "C://", "Text files (*.txt)");

    if(files.size() < 1) {
        return;
    }

    //read files
    for(QString path : files) {
        QFile file(path);
        QFileInfo info(file);

        if(!info.isFile() || !path.endsWith(".txt")) {
            continue;
        }

        readFile(file, _expense);
    }

    //update
    ui->inCat_comboBox->setCurrentText(ALL_TRANS);
    exSorted = SORT_CAT;
    updateExCat();
    updateExTrans();
    updateExTransTable();
}

void MainWindow::on_inGetFile_pushButton_clicked() {
    if(!_admin) {
        QMessageBox::critical(this, "Error", "No access");
        return;
    }

    QString inPath = qApp->applicationDirPath() + "/Income/";
    QDir inDir(inPath);

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

    foreach(QFileInfo info, inDir.entryInfoList()) {
        if(!info.isFile()) {
            continue;
        }
        QFile file(inPath + info.fileName());

        file.copy(destination + "/" + folderName + "/" + info.fileName());
    }

    QMessageBox::information(this, "Success", "Files added to Downloads folder");
}

void MainWindow::on_exGetFile_pushButton_clicked() {
    if(!_admin) {
        QMessageBox::critical(this, "Error", "No access");
        return;
    }

    QString exPath = qApp->applicationDirPath() + "/Expense/";
    QDir exDir(exPath);

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

    foreach(QFileInfo info, exDir.entryInfoList()) {
        if(!info.isFile()) {
            continue;
        }
        QFile file(exPath + info.fileName());

        file.copy(destination + "/" + folderName + "/" + info.fileName());
    }
    QMessageBox::information(this, "Success", "Files added to Downloads folder");
}

void MainWindow::on_fontUpdate_pushButton_clicked() {
    QFont font = ui->fontComboBox->currentFont();
    font.setPointSize(ui->fontSize_comboBox->currentText().toInt());
    QApplication::setFont(font);
}

void MainWindow::on_accountsEdit_pushButton_clicked() {
    if(!_admin) {
        QMessageBox::critical(this, "Error", "No access");
        return;
    }

    usersWindow = new UsersWindow(this, _users);
    usersWindow->exec();

    _users = usersWindow->getUsers();
}

void MainWindow::on_exit_pushButton_clicked() {
    this->close();
}

void MainWindow::on_inReport_pushButton_clicked() {
    if(!_admin) {
        QMessageBox::critical(this, "Error", "No access");
        return;
    }

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

    //Heading
    QString html = "";
    if(inDateFilter) {
        html = "<div align=right>";

        QDate start = ui->inStartDate_dateEdit->date();
        QDate end = ui->inEndDate_dateEdit->date();

        html += start.toString("MM/dd/yyyy") + " - " +
                end.toString("MM/dd/yyyy") + "</div>";
    }

    html += "<div align=left>Category: " +
                cat +
            "</div>";

    if(inKeyword) {
        QString keyword = ui->inKey_lineEdit->text();
        html += "<div align=left>Keyword: " +
                    keyword +
                "</div>";
    }

    //Title
    html += "<h1 align=center> Income Report</h1>";

    //Body
    cat = ui->inCat_comboBox->currentText();
    html += "<p align=left>";
    for(unsigned i = 0; i < inFiltered.size(); i++) {
        if(cat == ALL_TRANS) {
            html += inFiltered[i].getCategory() + "<br>";
        }
        html += inFiltered[i].dateShortText() + " -- " + inFiltered[i].costText() + "<br>";

        QString description = inFiltered[i].getDescription();
        if(description != "") {
            description = description.trimmed();
            description.replace("\n", "<br>");
            html += description + "<br>";
        }

        if(i != inFiltered.size()-1) {
            html += "<br>";
        }
    }
    html += "</p>";

    //Print
    QTextDocument document;
    document.setHtml(html);
    document.print(printer);
}

void MainWindow::on_exReport_pushButton_clicked() {
    if(!_admin) {
        QMessageBox::critical(this, "Error", "No access");
        return;
    }

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

    //Heading
    QString html = "";
    if(exDateFilter) {
        html = "<div align=right>";

        QDate start = ui->exStartDate_dateEdit->date();
        QDate end = ui->exEndDate_dateEdit->date();

        html += start.toString("MM/dd/yyyy") + " - " +
                end.toString("MM/dd/yyyy") + "</div>";
    }

    html += "<div align=left>Category: " +
                cat +
            "</div>";

    if(exKeyword) {
        QString keyword = ui->exKey_lineEdit->text();
        html += "<div align=left>Keyword: " +
                    keyword +
                "</div>";
    }

    //Title
    html += "<h2 align=center> Expense Report</h2>";

    //Body
    cat = ui->exCat_comboBox->currentText();
    html += "<p align=left>";
    for(unsigned i = 0; i < exFiltered.size(); i++) {
        if(cat == ALL_TRANS) {
            html += exFiltered[i].getCategory() + "<br>";
        }
        html += exFiltered[i].dateShortText() + " -- " + exFiltered[i].costText() + "<br>";

        QString description = exFiltered[i].getDescription();
        if(description != "") {
            description = description.trimmed();
            description.replace("\n", "<br>");
            html += description + "<br>";
        }

        if(i != exFiltered.size()-1) {
            html += "<br>";
        }
    }
    html += "</p>";

    //Print
    QTextDocument document;
    document.setHtml(html);
    document.print(printer);
}

