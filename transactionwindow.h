#ifndef TRANSACTIONWINDOW_H
#define TRANSACTIONWINDOW_H

#include <QDialog>
#include <QDate>
#include <QString>

namespace Ui {
    class TransactionWindow;
}

class TransactionWindow : public QDialog {
    Q_OBJECT

  public:
    /*******************************
     ** CONSTRUCTOR & DESCTRUCTOR **
     *******************************/
    explicit TransactionWindow(QWidget *parent = nullptr,
             const std::vector<QString>& categories = std::vector<QString>());
    TransactionWindow(const std::vector<QString>& categories, const QDate& d,
                      double cost, QString descrip, QString checkNum,
                      QWidget *parent = nullptr);
    ~TransactionWindow();

    /***************
     ** ACCESSORS **
     ***************/
    const QDate& date() const;
    double cost() const;
    QString description() const;
    bool save() const;
    QString category() const;
    QString checkNum() const;

    /**************
     ** MUTATORS **
     **************/
    void setCategory(QString cat);

  private slots:
    /*********************
     ** Slots & Signals **
     *********************/
    void on_saveButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::TransactionWindow *ui;
    QDate _date;
    double _cost;
    QString _description;
    QString _checkNum;
    bool _save;
};

#endif // TRANSACTIONWINDOW_H

/******************************************************************************
 *  TransactionWindow Class
 *    A dialog window with widgets to edit date, cost, category, and description
 ******************************************************************************/


/******************************
 ** CONSTRUCTOR & DESTRUCTOR **
 ******************************/

/******************************************************************************
 *  explicit TransactionWindow(QWidget *parent = nullptr,
 *           const std::vector<QString>& categories = std::vector<QString>());
 *    Constructor; Set up ui and window title, and intialize class variables
 *    Parameters: QWidget *, const std::vector<QString>&
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  TransactionWindow(const std::vector<QString>& categories, const QDate& d,
                      double cost, QString descrip, QWidget *parent = nullptr);
 *    Constructor; Set up ui and window title, and intialize class variables
 *      with given parameter values
 *    Parameters: const std::vector<QString>&, const QDate&, double, QString
 *                QWidget *
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  ~TransactionWindow();
 *    Destructor; Deleted the ui
 *    Parameters: none
 *    Return: void
 ******************************************************************************/


/***************
 ** ACCESSORS **
 ***************/

/******************************************************************************
 *  const QDate& date() const;
 *
 *    Accessor; This method will return _date
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: const QDate&
 ******************************************************************************/

/******************************************************************************
 *   double cost() const;
 *
 *    Accessor; This method will return _cost
 * ----------------------------------------------------------------------------
 *    Parameters:none
 * ----------------------------------------------------------------------------
 *    Return: double
 ******************************************************************************/

/******************************************************************************
 *   QString description() const;
 *
 *    Accessor; This method will return _description
 * ----------------------------------------------------------------------------
 *    Parameters:none
 * ----------------------------------------------------------------------------
 *    Return: QString
 ******************************************************************************/

/******************************************************************************
 *   bool save() const;
 *
 *    Accessor; This method will return _save
 * ----------------------------------------------------------------------------
 *    Parameters:none
 * ----------------------------------------------------------------------------
 *    Return: double
 ******************************************************************************/

/******************************************************************************
 *   QString cost() const;
 *
 *    Accessor; This method will return _category
 * ----------------------------------------------------------------------------
 *    Parameters:none
 * ----------------------------------------------------------------------------
 *    Return: QString
 ******************************************************************************/



/**************
 ** MUTATORS **
 **************/

/******************************************************************************
 *  void setCategory(QString cat);
 *
 *    Mutator; This method will update category combo box item
 * ----------------------------------------------------------------------------
 *    Parameters: QString
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/


/*********************
 ** Slots & Signals **
 *********************/

/******************************************************************************
 *  void on_saveButton_clicked();
 *
 *    checks if inputted values are valid, update all class variables
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void on_saveButton_clicked();
 *
 *    clost dialog window
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/
