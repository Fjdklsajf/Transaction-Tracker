#include "category.h"
#include <QString>
#include <QDateTime>
#include <vector>

/******************************************************************************
 *
 *  Constructor Category: Class Category
 *_____________________________________________________________________________
 *  initialize _category
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _category = ""
 ******************************************************************************/
Category::Category() : _category("") {
}

/******************************************************************************
 *
 *  Constructor Category: Class Category
 *_____________________________________________________________________________
 *  Initialize _category with given arguments
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _category is initialized
 ******************************************************************************/
Category::Category(QString category) : _category(category) {
}

/******************************************************************************
 *
 *  Accessor getTransDate: Class Category
 *_____________________________________________________________________________
 *  This method will return a list of Transaction sorted by dates
 *  - returns const std::vector<Transaction>&
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _transDate is returned
 ******************************************************************************/
const std::vector<Transaction>& Category::getTransDate() const {
    return _transDate;
}

/******************************************************************************
 *
 *  Accessor getTransDate: Class Category
 *_____________________________________________________________________________
 *  This method will return a list of Transaction between the given dates
 *       sorted by dates
 *  - returns std::vector<Transaction>&
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    part of _transDate is returned
 ******************************************************************************/
std::vector<Transaction> Category::getTransDate(const QDate& start, const QDate& end) {
    std::vector<Transaction> t;

    // iterate through the list sorted by date
    for(unsigned i = 0; i < _transDate.size(); i++) {
        // starting date is found
        if(_transDate[i].getDate() >= start) {
            for(unsigned j = i; j < _transDate.size(); j++) {
                // adds every transaction in range of date
                if(_transDate[i].getDate() <= end) {
                    t.push_back(_transDate[i]);
                } else {
                    // All Transactions in range have been found
                    return t;
                }
                // reached end of the list
                break;
            }
        }
    }

    return t;
}

/******************************************************************************
 *
 *  Accessor getTransAmount: Class Category
 *_____________________________________________________________________________
 *  This method will return a list of Transaction sorted by amounts
 *  - returns std::vector<Transaction>&
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _transAmount is returned
 ******************************************************************************/
const std::vector<Transaction>& Category::getTransAmount() const {
    return _transAmount;
}

/******************************************************************************
 *
 *  Accessor getTransAmount: Class Category
 *_____________________________________________________________________________
 *  This method will return a list of Transaction between the given dates
 *       sorted by amounts
 *  - returns std::vector<Transaction>&
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    part of _transAmount is returned
 ******************************************************************************/
std::vector<Transaction> Category::getTransAmount(const QDate& start, const QDate& end) {
    std::vector<Transaction> t;

    // iterate through the list sorted by amount
    for(const Transaction& trans : _transAmount) {
        // add Transactions in range of date
        if(trans.getDate() >= start && trans.getDate() <= end) {
            t.push_back(trans);
        }
    }

    return t;
}

/******************************************************************************
 *
 *  Accessor getCategory: Class Category
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
QString Category::getCategory() const {
    return _category;
}

/******************************************************************************
 *
 *  Accessor searchTransDate: Class Category
 *_____________________________________________________________________________
 *  This method will return transactions containing the given keyword sorted
 *      by dates
 *  - returns std::vecotr<Transaction>
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    a list of Transactions is returned
 ******************************************************************************/
std::vector<Transaction> Category::searchTransDate(QString keyword) const {
    std::vector<Transaction> t;

    // iterate through the list sorted by amount
    for(const Transaction& trans : _transDate) {
        // add Transactions with the keyword
        if(trans.contains(keyword)) {
            t.push_back(trans);
        }
    }

    return t;
}

/******************************************************************************
 *
 *  Mutator setCategoryName: Class Category
 *_____________________________________________________________________________
 *  This method will update the _category attribute to the parameter
 *      category value
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _category and each transaction's category is updated
 ******************************************************************************/
void Category::setCategoryName(QString category) {
    // change category name
    _category = category;

    // change name for each individual transaction
    for(unsigned i = 0; i < _transDate.size(); i++) {
        _transDate[i].setCategory(category);
        _transAmount[i].setCategory(category);
    }
}

/******************************************************************************
 *
 *  Mutator add: Class Category
 *_____________________________________________________________________________
 *  This method will add a Transaction in this Category
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    A transaction is added to both _transDate and _transAmount
 ******************************************************************************/
void Category::add(const Transaction& t) {
    bool added = false;

    // Add to list sorted by date, newest at the end
    for(unsigned i= 0; i < _transDate.size(); i++) {
        if(t > _transDate[i]) {
            _transDate.insert(_transDate.begin() + i, t);
            added =true;
            break;
        }
    }
    if(!added) {
        _transDate.push_back(t);
    }

    // Add to list sorted by amount, lowest at the end
    for(unsigned i= 0; i < _transAmount.size(); i++) {
        if(t.getCost() > _transAmount[i].getCost()) {
            _transAmount.insert(_transAmount.begin() + i, t);
            return;
        }
    }
    _transAmount.push_back(t);

}

/******************************************************************************
 *
 *  Mutator add: Class Category
 *_____________________________________________________________________________
 *  This method will add a Transaction in this Category with the given parmeters
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    A transaction is added to both _transDate and _transAmount
 ******************************************************************************/
void Category::add(double cost, QString description, const QDate& date,
                   QString checkNum, const QDateTime& time) {
    add(Transaction(cost, description, date, time, _category, checkNum));
}

/******************************************************************************
 *
 *  Mutator remove: Class Category
 *_____________________________________________________________________________
 *  This method will remove a Transaction from this Category
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    A transaction is removed from both _transDate and _transAmount if found
 ******************************************************************************/
void Category::remove(const Transaction& t) {
    // remove from list sorted by date
    for(auto it = _transDate.begin(); it != _transDate.end(); it++) {
        if(*it == t) {
            _transDate.erase(it);
            break;
        }
    }

    // remove from list sorted by amount
    for(auto it = _transAmount.begin(); it != _transAmount.end(); it++) {
        if(*it == t) {
            _transAmount.erase(it);
            break;
        }
    }
}

/******************************************************************************
 *
 *  Mutator clear: Class Category
 *_____________________________________________________________________________
 *  This method will remove all transactions in this category
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _transDate and _transAmount are cleared
 ******************************************************************************/
void Category::clear() {
    _transDate.clear();
    _transAmount.clear();
}

/******************************************************************************
 *
 *  Method exist: Class Category
 *_____________________________________________________________________________
 *  Search for the given Transaction in this category
 *  - returns bool
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    return true if the Transaction is found
 ******************************************************************************/
bool Category::exist(const Transaction& t) const {
    for(const Transaction& trans : _transDate) {
        if(trans == t) {
            return true;
        }
    }
    return false;
}

/******************************************************************************
 *
 *  Method size: Class Category
 *_____________________________________________________________________________
 *  Return the number of Transactions in the category
 *  - returns int
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    size of _transDate is returned
 ******************************************************************************/
int Category::size() const {
    return _transDate.size();
}

/******************************************************************************
 *
 *  Operator Overload ==: Class Category
 *_____________________________________________________________________________
 *  Check if the categories are equal
 *  - returns bool
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    returns true if the Categories have the same names
 ******************************************************************************/
bool Category::operator ==(const Category& t) const {
    return _category == t.getCategory();
}

/******************************************************************************
 *
 *  Operator Overload !=: Class Category
 *_____________________________________________________________________________
 *  Check if the categories are not equal
 *  - returns bool
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    returns true if the Categories have different names
 ******************************************************************************/
bool Category::operator !=(const Category& t) const {
    return _category != t.getCategory();
}

/******************************************************************************
 *
 *  Operator Overload >: Class Category
 *_____________________________________________________________________________
 *  Check if the current Category is greater than the parameter's
 *  - returns bool
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    returns true if the current Category's name is greater
 ******************************************************************************/
bool Category::operator >(const Category& t) const {
    return _category > t.getCategory();
}

/******************************************************************************
 *
 *  Operator Overload <: Class Category
 *_____________________________________________________________________________
 *  Check if the current Category is less than the parameter's
 *  - returns bool
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    returns true if the current Category's name is lower
 ******************************************************************************/
bool Category::operator <(const Category& t) const {
    return _category < t.getCategory();
}

/******************************************************************************
 *
 *  Operator Overload >=: Class Category
 *_____________________________________________________________________________
 *  Check if the current Category is >= the parameter's
 *  - returns bool
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    returns true if the current Category's name is greater or equal
 ******************************************************************************/
bool Category::operator >=(const Category& t) const {
    return _category >= t.getCategory();
}

/******************************************************************************
 *
 *  Operator Overload >=: Class Category
 *_____________________________________________________________________________
 *  Check if the current Category is <= the parameter's
 *  - returns bool
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    returns true if the current Category's name is lower or equal
 ******************************************************************************/
bool Category::operator <=(const Category& t) const {
    return _category <= t.getCategory();
}
