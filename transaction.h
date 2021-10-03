#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QString>
#include <QDateTime>

class Transaction {
  public:
    /*****************
     ** CONSTRUCTOR **
     *****************/
    Transaction();
    explicit Transaction(double cost, QString descrip = "",
                const QDate& date = QDate::currentDate(),
                const QDateTime& time = QDateTime::currentDateTime(),
                QString category = "", QString checkNum = "");

    /***************
     ** ACCESSORS **
     ***************/
    QString getDescription() const;
    QString getCategory() const;
    double getCost() const;
    const QDate& getDate() const;
    const QDateTime& getTimestamp() const;
    QString getCheckNum() const;

    /**************
     ** MUTATORS **
     **************/
    void setDescription(QString description);
    void setCategory(QString category);
    void setCost(double cost);
    void setDate(const QDate& date);
    void setDate(int year, int month, int day);
    void setTimestamp(const QDateTime& time);
    void setTimestamp(int y, int M, int d, int h, int m, int s, int ms = 0);
    void setCheckNum(QString checkNum);

    /*******************************
     ** CONSTANT MEMBER FUNCTIONS **
     *******************************/
    QString costText() const;
    QString dateFullText() const;
    QString dateShortText() const;
    QString timestampText() const;
    QString toString() const;
    bool contains(QString keyword) const;

    /***********************
     ** OPERATOR OVERLOAD **
     ***********************/
    bool operator ==(const Transaction& t) const;
    bool operator !=(const Transaction& t) const;
    bool operator >(const Transaction& t) const;
    bool operator <(const Transaction& t) const;
    bool operator >=(const Transaction& t) const;
    bool operator <=(const Transaction& t) const;

  private:
    double _cost;
    QString _description;
    QDate _date;
    QDateTime _timestamp;
    QString _category;
    QString _checkNum;
};

#endif // TRANSACTION_H

/******************************************************************************
 *  Transaction Class
 *    A transaction containing date, cost, description, added date and time,
 *      and check number
 ******************************************************************************/


/******************************
 ** CONSTRUCTOR & DESTRUCTOR **
 ******************************/

/******************************************************************************
 *  Transaction()
 *    Default Constructor; Initialize all variables, set to current dates and times
 *    Parameters: none
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  Transaction(double cost, QString descrip, const QDate& date,
                         const QDateTime& time, QString category)
 *    Constructor; Initialize all variables with given arguments
 *    Parameters: double, QString, const QDate&, const QDateTime&, QString
 *    Return: void
 ******************************************************************************/


/***************
 ** ACCESSORS **
 ***************/

/******************************************************************************
 *  QString getDescription() const;
 *
 *    Accessor; This method will return _description
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: QString
 ******************************************************************************/

/******************************************************************************
 *  QString getCategory() const;
 *
 *    Accessor; This method will return _category
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: QString
 ******************************************************************************/

/******************************************************************************
 *  double getCost() const;
 *
 *    Accessor; This method will return _cost
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: double
 ******************************************************************************/

/******************************************************************************
 *  const QDate& getDate() const;
 *
 *    Accessor; This method will return _date
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: const QDate&
 ******************************************************************************/

/******************************************************************************
 *  const QDateTime& getTimestamp() const;
 *
 *    Accessor; This method will return _timestamp
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: const QDateTime&
 ******************************************************************************/

/******************************************************************************
 *  QString getCheckNum() const;
 *
 *    Accessor; This method will return _checkNum
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: QString
 ******************************************************************************/


/**************
 ** MUTATORS **
 **************/

/******************************************************************************
 *  void setDescription(QString description);
 *
 *    Mutator; This method will update the _description attribute to the
 *      parameter description value
 * ----------------------------------------------------------------------------
 *    Parameters: QString
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void setCategory(QString category);
 *
 *    Mutator; This method will update the _category attribute to the
 *      parameter category value
 * ----------------------------------------------------------------------------
 *    Parameters: QString
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void setCost(double cost);
 *
 *    Mutator; This method will update the _cost attribute to the
 *      parameter cost value
 * ----------------------------------------------------------------------------
 *    Parameters: double
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void setDate(const QDate& date);
 *
 *    Mutator; This method will update the _date attribute to the
 *      parameter date value
 * ----------------------------------------------------------------------------
 *    Parameters: const QDate&
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void setDate(int year, int month, int day);
 *
 *    Mutator; This method will update the _date attribute with the given year,
 *      month, and day values
 * ----------------------------------------------------------------------------
 *    Parameters: int, int, int
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void setTimestamp(const QDateTime& time);
 *
 *    Mutator; This method will update the _timestamp attribute to the
 *      parameter time value
 * ----------------------------------------------------------------------------
 *    Parameters: const QDateTime&
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void setTimestamp(int y, int M, int d, int h, int m, int s, int ms = 0);
 *
 *    Mutator; This method will update the _timestamp attribute with the given
 *      year, month, day, hour, minute, second, and millisecond values
 * ----------------------------------------------------------------------------
 *    Parameters: int, int, int, int, int, int, int
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void setCheckNum(QString checkNum);
 *
 *    Mutator; This method will update the _checkNum attribute to the
 *      parameter checkNum value
 * ----------------------------------------------------------------------------
 *    Parameters: QString
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/


/*******************************
 ** CONSTANT MEMBER FUNCTIONS **
 *******************************/

/******************************************************************************
 *  QString costText() const;
 *
 *    Return a formatted QString _cost in the form of
 *      $10.50
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: QString
 ******************************************************************************/

/******************************************************************************
 *  QString dateFullText() const;
 *
 *    Return a formatted QString of _date in the form of
 *      January 01, 2000
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: QString
 ******************************************************************************/

/******************************************************************************
 *  QString dateShortText() const;
 *
 *    Return a formatted QString of _date in the form of
 *      01/01/2000
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: QString
 ******************************************************************************/

/******************************************************************************
 *  QString timestampText() const;
 *
 *    Return a formatted QString of _timestamp in the form of
 *      2000:01:01:11:59:59:999
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: QString
 ******************************************************************************/

/******************************************************************************
 *  QString toString() const;
 *
 *    Return the Transaction in a QString in the form of
 *      Category
 *      January 01, 2000 -- $10.50
 *
 *      Description
 *      Description
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: QString
 ******************************************************************************/

/******************************************************************************
 *  bool contains(QString keyword) const;
 *
 *    Search for the keyword in _description
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: bool
 ******************************************************************************/


/***********************
 ** OPERATOR OVERLOAD **
 ***********************/

/******************************************************************************
 *  bool operator ==(const Transaction& t) const;
 *
 *    Check if the given Transaction have the same instance variable values
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: bool
 ******************************************************************************/

/******************************************************************************
 *  bool operator !=(const Transaction& t) const;
 *
 *    Check if the given Transaction have different instance variable values
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: bool
 ******************************************************************************/

/******************************************************************************
 *  bool operator >(const Transaction& t) const;
 *
 *    Check if the current transaction is greater than the given Transaction
 *      First compares dates, then timestamp if the dates are identical
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: bool
 ******************************************************************************/

/******************************************************************************
 *  bool operator <(const Transaction& t) const;
 *
 *    Check if the current transaction is less than the given Transaction
 *      First compares dates, then timestamp if the dates are identical
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: bool
 ******************************************************************************/

/******************************************************************************
 *  bool operator >=(const Transaction& t) const;
 *
 *    Check if the current transaction is greater than or equal to the given
 *    Transaction
 *      First compares dates, then timestamp if the dates are identical
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: bool
 ******************************************************************************/

/******************************************************************************
 *  bool operator <=(const Transaction& t) const;
 *
 *    Check if the current transaction is less than or equal to the given
 *    Transaction
 *      First compares dates, then timestamp if the dates are identical
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: bool
 ******************************************************************************/
