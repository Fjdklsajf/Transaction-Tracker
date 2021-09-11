#include "transactionwindow.h"
#include "ui_transactionwindow.h"
#include <QString>
#include <QMessageBox>

/******************************************************************************
 *
 *  Constructor TransactionWindow: Class TransactionWindow
 *_____________________________________________________________________________
 *  Set up ui and window title, and intialize class variables
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    the dialog window is set up
 ******************************************************************************/
TransactionWindow::TransactionWindow(QWidget *parent,
                                     const std::vector<QString>& categories) :
    QDialog(parent), ui(new Ui::TransactionWindow) {

    // set up the dialog
    ui->setupUi(this);
    this->setWindowTitle("Transaction");
    ui->date->setDate(QDate::currentDate());

    // add categories to the combo box
    for(QString c : categories) {
        ui->categories->addItem(c);
    }

    _save = false;
}

/******************************************************************************
 *
 *  Constructor TransactionWindow: Class TransactionWindow
 *_____________________________________________________________________________
 *  Set up ui and window title, and intialize class variables
 *      with given parameter values
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    the dialog window is set up with given parameter values
 ******************************************************************************/
TransactionWindow::TransactionWindow(const std::vector<QString>& categories,
                                     const QDate& d, double cost,
                                     QString descrip, QWidget *parent) :
    QDialog(parent), ui(new Ui::TransactionWindow) {

    // set up the dialog
    ui->setupUi(this);
    ui->date->setDate(d);
    ui->amount->setText(QString().asprintf("%0.2f", cost));
    ui->description->setText(descrip);

    // add categories to the combo box
    for(QString c : categories) {
        ui->categories->addItem(c);
    }

    _save = false;

}

/******************************************************************************
 *
 *  Destructor ~TransactionWindow: Class TransactionWindow
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
TransactionWindow::~TransactionWindow() {
    delete ui;
}

/******************************************************************************
 *
 *  Accessor date: Class TransactionWindow
 *_____________________________________________________________________________
 *  This method will return the date
 *  - returns const QDate&
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _date is returned
 ******************************************************************************/
const QDate& TransactionWindow::date() const {
    return _date;
}

/******************************************************************************
 *
 *  Accessor cost: Class TransactionWindow
 *_____________________________________________________________________________
 *  This method will return the amount
 *  - returns double
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _cost is returned
 ******************************************************************************/
double TransactionWindow::cost() const {
    return _cost;
}

/******************************************************************************
 *
 *  Accessor description: Class TransactionWindow
 *_____________________________________________________________________________
 *  This method will return the description
 *  - returns double
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _description is returned
 ******************************************************************************/
QString TransactionWindow::description() const {
    return _description;
}

/******************************************************************************
 *
 *  Accessor save: Class TransactionWindow
 *_____________________________________________________________________________
 *  This method will return the save state of the dialog window
 *  - returns bool
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _save is returned
 ******************************************************************************/
bool TransactionWindow::save() const {
    return _save;
}

/******************************************************************************
 *
 *  Accessor category: Class TransactionWindow
 *_____________________________________________________________________________
 *  This method will return the category displayed in the combo box
 *  - returns QString
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    current item in the combo box is returned
 ******************************************************************************/
QString TransactionWindow::category() const {
    return ui->categories->currentText();
}

/******************************************************************************
 *
 *  Mutator setCategory: Class TransactionWindow
 *_____________________________________________________________________________
 *  This method will update category combo box item
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    cat is found in the combo box
 *
 *  POST-CONDITIONS
 *    Category combo box selected item is changed
 ******************************************************************************/
void TransactionWindow::setCategory(QString cat) {
    ui->categories->setCurrentText(cat);
}

/******************************************************************************
 *
 *  Method on_saveButton_clicked: Class TransactionWindow
 *_____________________________________________________________________________
 *  Checks if inputed values are valid and update all class variables when
 *      the save button is clicked. Display a Message box if invalid inputs
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    input values are valid
 *
 *  POST-CONDITIONS
 *    class variables are updated, _save = true
 ******************************************************************************/
void TransactionWindow::on_saveButton_clicked() {
    bool valid;

    _date = ui->date->date();
    _cost = ui->amount->text().toDouble(&valid);
    _description = ui->description->toPlainText();

    // if amount and date are valid
    if(valid && _date.isValid()) {
        _save = true;
        this->close();
    } else { // otherwise display message box
        QMessageBox::critical(this, "Error",
                              "Invalid input(s).");
    }
}

/******************************************************************************
 *
 *  Method on_cancelButton_clicked: Class TransactionWindow
 *_____________________________________________________________________________
 *  Close the dialog window
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    dialog is closed
 ******************************************************************************/
void TransactionWindow::on_cancelButton_clicked() {
    this->close();
}

