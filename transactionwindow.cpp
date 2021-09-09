#include "transactionwindow.h"
#include "ui_transactionwindow.h"
#include <QString>
#include <QMessageBox>

TransactionWindow::TransactionWindow(QWidget *parent, const std::vector<QString>& categories) :
    QDialog(parent), ui(new Ui::TransactionWindow) {
    ui->setupUi(this);
    this->setWindowTitle("Transaction");
    ui->date->setDate(QDate::currentDate());

    for(QString c : categories) {
        ui->categories->addItem(c);
    }
    _save = false;
}

TransactionWindow::TransactionWindow(const std::vector<QString>& categories, const QDate& d,
                                     double cost, QString descrip, QWidget *parent) :
    QDialog(parent), ui(new Ui::TransactionWindow) {
    ui->setupUi(this);

    ui->date->setDate(d);
    ui->amount->setText(QString().asprintf("%0.2f", cost));
    ui->description->setText(descrip);

    for(QString c : categories) {
        ui->categories->addItem(c);
    }
    _save = false;

}

TransactionWindow::~TransactionWindow() {
    delete ui;
}

const QDate& TransactionWindow::date() const {
    return _date;
}

double TransactionWindow::cost() const {
    return _cost;
}

QString TransactionWindow::description() const {
    return _description;
}

bool TransactionWindow::save() const {
    return _save;
}

QString TransactionWindow::category() const {
    return ui->categories->currentText();
}

void TransactionWindow::setCategory(QString cat) {
    ui->categories->setCurrentText(cat);
}

void TransactionWindow::on_saveButton_clicked() {
    _date = ui->date->date();

    bool valid;
    _cost = ui->amount->text().toDouble(&valid);
    _description = ui->description->toPlainText();

    if(valid) {
        _save = true;
        this->close();
    } else {
        QMessageBox::critical(this, "Error",
                              "Invalid input(s).");
    }
}


void TransactionWindow::on_cancelButton_clicked() {
    this->close();
}

