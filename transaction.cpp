#include "transaction.h"
#include <QDateTime>
#include <QString>

/******************************************************************************
 *
 *  Constructor Transaction: Class Transaction
 *_____________________________________________________________________________
 *  initialize private member variables
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _cost = 0, _description = "", _date = current date,
 *    _timestamp = current date time, _category = ""
 ******************************************************************************/
Transaction::Transaction() : Transaction(0) {
}

/******************************************************************************
 *
 *  Constructor Transaction: Class Transaction
 *_____________________________________________________________________________
 *   initialize private member variables with given parameters
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _cost, _description, _date, _timestamp, _category are initialized
 ******************************************************************************/
Transaction::Transaction(double cost, QString descrip, const QDate& date,
                         const QDateTime& time, QString category, QString checkNum) :
    _cost(cost), _description(descrip), _date(date),
    _timestamp(time), _category(category), _checkNum(checkNum) {
}

/******************************************************************************
 *
 *  Accessor getDescription: Class Transaction
 *_____________________________________________________________________________
 *  This method will return _description
 *  - returns QString
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _description is returned
 ******************************************************************************/
QString Transaction::getDescription() const {
    return _description;
}

/******************************************************************************
 *
 *  Accessor getCategory: Class Transaction
 *_____________________________________________________________________________
 *  This method will return _category
 *  - returns QString
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _category is returned
 ******************************************************************************/
QString Transaction::getCategory() const {
    return _category;
}

/******************************************************************************
 *
 *  Accessor getCost: Class Transaction
 *_____________________________________________________________________________
 *  This method will return _cost
 *  - returns double
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _cost is returned
 ******************************************************************************/
double Transaction::getCost() const {
    return _cost;
}

/******************************************************************************
 *
 *  Accessor getDate: Class Transaction
 *_____________________________________________________________________________
 *  This method will return _date
 *  - returns const QDate&
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _date is returned
 ******************************************************************************/
const QDate& Transaction::getDate() const {
    return _date;
}

/******************************************************************************
 *
 *  Accessor getTimestamp: Class Transaction
 *_____________________________________________________________________________
 *  This method will return _timestamp
 *  - returns const QDateTime&
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _timestamp is returned
 ******************************************************************************/
const QDateTime& Transaction::getTimestamp() const {
    return _timestamp;
}

/******************************************************************************
 *
 *  Accessor getCheckNum: Class Transaction
 *_____________________________________________________________________________
 *  This method will return the check number
 *  - returns const QDateTime&
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _checkNum is returned
 ******************************************************************************/
QString Transaction::getCheckNum() const {
    return _checkNum;
}

/******************************************************************************
 *
 *  Mutator setDescription: Class Transaction
 *_____________________________________________________________________________
 *  This method will update the _description attribute to the parameter
 *      description value
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _description is updated
 ******************************************************************************/
void Transaction::setDescription(QString description) {
    _description = description;
}

/******************************************************************************
 *
 *  Mutator setCategory: Class Transaction
 *_____________________________________________________________________________
 *  This method will update the _category attribute to the parameter
 *      category value
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _category is updated
 ******************************************************************************/
void Transaction::setCategory(QString category) {
    _category = category;
}

/******************************************************************************
 *
 *  Mutator setCost: Class Transaction
 *_____________________________________________________________________________
 *  This method will update the _cost attribute to the parameter cost value
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _cost is updated
 ******************************************************************************/
void Transaction::setCost(double cost) {
    _cost = cost;
}

/******************************************************************************
 *
 *  Mutator setDate: Class Transaction
 *_____________________________________________________________________________
 *  This method will update the _date attribute to the parameter date value
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    date is a valid QDate
 *
 *  POST-CONDITIONS
 *    _date  is updated
 ******************************************************************************/
void Transaction::setDate(const QDate& date) {
    _date = date;
}

/******************************************************************************
 *
 *  Mutator setDate: Class Transaction
 *_____________________________________________________________________________
 *  This method will update the _date attribute with the given year,
 *      month, and day values
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    given arguments forms a valid date
 *
 *  POST-CONDITIONS
 *    _date is updated
 ******************************************************************************/
void Transaction::setDate(int year, int month, int day) {
    _date.setDate(year, month, day);
}

/******************************************************************************
 *
 *  Mutator setTimestamp: Class Transaction
 *_____________________________________________________________________________
 *  This method will update the _timestamp attribute to the parameter
 *      time value
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    time is a valid QDateTime
 *
 *  POST-CONDITIONS
 *    _timestamp is updated
 ******************************************************************************/
void Transaction::setTimestamp(const QDateTime &time) {
    _timestamp = time;
}

/******************************************************************************
 *
 *  Mutator setDescription: Class Transaction
 *_____________________________________________________________________________
 *  This method will update the _timestamp attribute with the given
 *      year, month, day, hour, minute, second, and millisecond values
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _timestamp is updated
 ******************************************************************************/
void Transaction::setTimestamp(int y, int M, int d, int h, int m, int s, int ms) {
    _timestamp.setDate(QDate(y, M, d));
    _timestamp.setTime(QTime(h, m, s, ms));
}

/******************************************************************************
 *
 *  Mutator setCheckNum: Class Transaction
 *_____________________________________________________________________________
 *  This method will update the _checkNum attribute with the given parameter
 *      checkNum value
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _checkNum is updated
 ******************************************************************************/
void Transaction::setCheckNum(QString checkNum) {
    _checkNum = checkNum;
}

/******************************************************************************
 *
 *  Method costText: Class Transaction
 *_____________________________________________________________________________
 *  Return a formatted QString _cost in the form of
 *      $10.50
 *  - returns QString
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    a formatted cost is returned as a QString
 ******************************************************************************/
QString Transaction::costText() const {
    return QString().asprintf("$%0.2f", _cost);
}

/******************************************************************************
 *
 *  Method dateFullText: Class Transaction
 *_____________________________________________________________________________
 *  Return a formatted QString of _date in the form of
 *      January 01, 2000
 *  - returns QString
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    a formatted date is returned as a QString
 ******************************************************************************/
QString Transaction::dateFullText() const {
    return _date.toString("MMMM dd, yyyy");
}

/******************************************************************************
 *
 *  Method dateShortText: Class Transaction
 *_____________________________________________________________________________
 *  Return a formatted QString of _date in the form of
 *      01/01/2000
 *  - returns QString
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    a formatted date is returned as a QString
 ******************************************************************************/
QString Transaction::dateShortText() const {
    return _date.toString("MM/dd/yyyy");
}

/******************************************************************************
 *
 *  Method timestampText: Class Transaction
 *_____________________________________________________________________________
 *  Return a formatted QString of _timestamp in the form of
 *      2000:01:01:11:59:59:999
 *  - returns QString
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    a formatted timestamp is returned as a QString
 ******************************************************************************/
QString Transaction::timestampText() const {
    return _timestamp.toString("yyyy:MM:dd:hh:mm:ss:zzz");
}

/******************************************************************************
 *
 *  Method toString: Class Transaction
 *_____________________________________________________________________________
 *  Return the Transaction in a QString in the form of
 *      Category
 *      January 01, 2000 -- $10.50
 *      Check #:
 *
 *      Description
 *      Description
 *  - returns QString
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    transaction is returned as a formatted QString
 ******************************************************************************/
QString Transaction::toString() const {
    QString descrip = _category + "\n" + dateFullText() + " -- " + costText() + "\n";
    if(_checkNum != "") {
        descrip += "Check #: " + _checkNum + "\n";
    }
    descrip += "\n" + _description;
    return descrip;
}

/******************************************************************************
 *
 *  Method contains: Class Transaction
 *_____________________________________________________________________________
 *  Search for the keyword in _description, ignores case
 *  - returns bool
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    returns true if the keyword is found
 ******************************************************************************/
bool Transaction::contains(QString keyword) const {
    return _description.contains(keyword, Qt::CaseInsensitive);
}

/******************************************************************************
 *
 *  Operator Overload ==: Class Transaction
 *_____________________________________________________________________________
 *  Check if the given Transaction have the same instance variable values
 *  - returns bool
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    returns true if the transactions are equal
 ******************************************************************************/
bool Transaction::operator ==(const Transaction& t) const {
    return (_cost == t.getCost() && _description == t.getDescription() &&
            _date == t.getDate() && _timestamp == t.getTimestamp() &&
            _checkNum == t._checkNum);
}

/******************************************************************************
 *
 *  Operator Overload !=: Class Transaction
 *_____________________________________________________________________________
 *  Check if the given Transaction have different instance variable values
 *  - returns bool
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    returns true if the transactions are not equal
 ******************************************************************************/
bool Transaction::operator !=(const Transaction& t) const {
    return !(*this == t);
}

/******************************************************************************
 *
 *  Operator Overload >: Class Transaction
 *_____________________________________________________________________________
 *  Check if the current transaction is greater than the given Transaction
 *      First compares dates, then timestamp if the dates are identical
 *  - returns bool
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    returns true if the current transaction is greater than the argument
 ******************************************************************************/
bool Transaction::operator >(const Transaction& t) const {
    // first compare dates
    if (_date > t.getDate()) {
        return true;
    } else if(_date < t.getDate()) {
        return false;
    } else {
        // compare timestamp if on the same date
        return _timestamp > t.getTimestamp();
    }
}

/******************************************************************************
 *
 *  Operator Overload <: Class Transaction
 *_____________________________________________________________________________
 *  Check if the current transaction is less than the given Transaction
 *      First compares dates, then timestamp if the dates are identical
 *  - returns bool
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    returns true if the current transaction is less than the argument
 ******************************************************************************/
bool Transaction::operator <(const Transaction& t) const {
    // first compare dates
    if (_date < t.getDate()) {
        return true;
    } else if(_date > t.getDate()) {
        return false;
    } else {
        // compare timestamp if on the same date
        return _timestamp < t.getTimestamp();
    }
}

/******************************************************************************
 *
 *  Operator Overload >=: Class Transaction
 *_____________________________________________________________________________
 *  Check if the current transaction is greater than or equal to the given
 *  Transaction
 *      First compares dates, then timestamp if the dates are identical
 *  - returns bool
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    returns true if the current transaction is >= to the argument
 ******************************************************************************/
bool Transaction::operator >=(const Transaction& t) const {
    // first compare dates
    if (_date > t.getDate()) {
        return true;
    } else if(_date < t.getDate()) {
        return false;
    } else {
        // compare timestamp if on the same date
        return _timestamp >= t.getTimestamp();
    }
}

/******************************************************************************
 *
 *  Operator Overload <=: Class Transaction
 *_____________________________________________________________________________
 *  Check if the current transaction is less than or equal to the given
 *  Transaction
 *      First compares dates, then timestamp if the dates are identical
 *  - returns bool
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    returns true if the current transaction is <= to the argument
 ******************************************************************************/
bool Transaction::operator <=(const Transaction& t) const {
    // first compare dates
    if (_date < t.getDate()) {
        return true;
    } else if(_date > t.getDate()) {
        return false;
    } else {
        // compare timestamp if on the same date
        return _timestamp <= t.getTimestamp();
    }
}
