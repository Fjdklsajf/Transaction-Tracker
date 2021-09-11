#include "tracker.h"
#include "transaction.h"
#include "category.h"
#include <QString>
#include <QDateTime>
#include <vector>

/******************************************************************************
 *
 *  Constructor Tracker: Class Tracker
 *_____________________________________________________________________________
 *  initialize _title
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _title = ""
 ******************************************************************************/
Tracker::Tracker() : _title("") {
}

/******************************************************************************
 *
 *  Constructor Tracker: Class Tracker
 *_____________________________________________________________________________
 *  initialize _title with given argument
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _title is initialized
 ******************************************************************************/
Tracker::Tracker(QString title) : _title(title) {
}

/******************************************************************************
 *
 *  Accessor getTitle: Class Tracker
 *_____________________________________________________________________________
 *  This method will return the title of the Tracker
 *  - returns QString
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _title is returned
 ******************************************************************************/
QString Tracker::getTitle() const {
    return _title;
}

/******************************************************************************
 *
 *  Accessor getCategories: Class Tracker
 *_____________________________________________________________________________
 *  This method will return the all categories in the Tracker
 *  - returns const std::vector<Category>&
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _category is returned
 ******************************************************************************/
const std::vector<Category>& Tracker::getCategories() const {
    return _categories;
}

/******************************************************************************
 *
 *  Accessor getCategoryNames: Class Tracker
 *_____________________________________________________________________________
 *  This method will return all Category names
 *  - returns std::vector<QString>
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    a list of category names is returned
 ******************************************************************************/
std::vector<QString> Tracker::getCategoryNames() const {
    std::vector<QString> names;

    for(const Category& c : _categories) {
        names.push_back(c.getCategory());
    }

    return names;
}

/******************************************************************************
 *
 *  Accessor getCategory: Class Tracker
 *_____________________________________________________________________________
 *  This method will return a Category given its name
 *  - returns const Category&
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    category exists
 *
 *  POST-CONDITIONS
 *    Category of the given name is returned
 ******************************************************************************/
const Category& Tracker::getCategory(QString category) const {
    int i = find(category);

    return _categories[i];
}

/******************************************************************************
 *
 *  Accessor getTransDate: Class Tracker
 *_____________________________________________________________________________
 *  This method will return all Transactions in the given category sorted by
 *      dates
 *  - returns const std::vector<Transasction>&
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    category exists
 *
 *  POST-CONDITIONS
 *    a list of transaction sorted by dates is returned
 ******************************************************************************/
const std::vector<Transaction>& Tracker::getTransDate(QString category) const {
    int i = find(category);

    return _categories[i].getTransDate();
}

/******************************************************************************
 *
 *  Accessor getTransAmount: Class Tracker
 *_____________________________________________________________________________
 *  This method will return all Transactions in the given category sorted by
 *      amounts
 *  - returns const std::vector<Transasction>&
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    category exists
 *
 *  POST-CONDITIONS
 *    a list of transaction sorted by amounts is returned
 ******************************************************************************/
const std::vector<Transaction>& Tracker::getTransAmount(QString category) const {
    int i = find(category);

    return _categories[i].getTransAmount();
}

/******************************************************************************
 *
 *  Accessor getAllTransactions: Class Tracker
 *_____________________________________________________________________________
 *  This method will return all Transactions combined in all Categories
 *  - returns std::vector<Transasction>
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    a list of all Transactions in the Tracker is returned
 ******************************************************************************/
std::vector<Transaction> Tracker::getAllTransactions() {
    std::vector<Transaction> t;

    for(const Category& c : _categories) {
        for(const Transaction& trans : c.getTransDate()) {
            t.push_back(trans);
        }
    }

    return t;
}

/******************************************************************************
 *
 *  Accessor getAllTransactions: Class Tracker
 *_____________________________________________________________________________
 *  This method will return all Transactions combined in all Categories
 *      sorted by dates
 *  - returns std::vector<Transasction>
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    a list of all Transactions sorted by dates is returned
 ******************************************************************************/
std::vector<Transaction> Tracker::getTransDateSorted() {
    if(_categories.size() <= 1) {
        return getAllTransactions();
    }

    // sort the list of all transactions by date
    std::vector<Transaction> sorted = getAllTransactions();
    std::sort(sorted.rbegin(), sorted.rend());

    return sorted;
}

/******************************************************************************
 *
 *  Accessor getAllTransactions: Class Tracker
 *_____________________________________________________________________________
 *  This method will return all Transactions combined in all Categories
 *      sorted by amounts
 *  - returns std::vector<Transasction>
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    a list of all Transactions sorted by amounts is returned
 ******************************************************************************/
std::vector<Transaction> Tracker::getTransAmountSorted() {
    if(_categories.size() <= 1) {
        return getAllTransactions();
    }

    // sort the list of all transactions by cost
    std::vector<Transaction> sorted = getAllTransactions();
    std::sort(sorted.begin(), sorted.end(),
              [] (const Transaction& t1, const Transaction& t2) -> bool {
        return t1.getCost() > t2.getCost();
    });

    return sorted;
}

/******************************************************************************
 *
 *  Mutator setTitle: Class Tracker
 *_____________________________________________________________________________
 *  This method will update the _title attribute to the parameter
 *      title value
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _title is initialized
 ******************************************************************************/
void Tracker::setTitle(QString title) {
    _title = title;
}

/******************************************************************************
 *
 *  Mutator addCategory: Class Tracker
 *_____________________________________________________________________________
 *  This method will add a Category to the Tracker if it does not already exist
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    category does not already exist
 *
 *  POST-CONDITIONS
 *    A Category is added to _categories
 ******************************************************************************/
void Tracker::addCategory(const Category& category) {
    if(exist(category.getCategory())) {
        return;
    }

    // alphabetical order
    for(unsigned i = 0; i < _categories.size(); i++) {
        if(category.getCategory().toLower() < _categories[i].getCategory().toLower()) {
            _categories.insert(_categories.begin()+i, category);
            return;
        }
    }

    _categories.push_back(category);
}

/******************************************************************************
 *
 *  Mutator addCategory: Class Tracker
 *_____________________________________________________________________________
 *  This method will add a new empty Category to the Tracker if it does not
 *      already exist
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    category does not already exist
 *
 *  POST-CONDITIONS
 *    A new Category is added to _categories
 ******************************************************************************/
void Tracker::addCategory(QString category) {
    addCategory(Category(category));
}

/******************************************************************************
 *
 *  Mutator clearCategory: Class Tracker
 *_____________________________________________________________________________
 *  This method will clear the given Category in the Tracker
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    category exists
 *
 *  POST-CONDITIONS
 *    A Category in the Tracker is erased
 ******************************************************************************/
void Tracker::clearCategory(QString category) {
    int i = find(category);

    if(i != -1) {
        _categories[i].clear();
    }
}

/******************************************************************************
 *
 *  Mutator removeCategory: Class Tracker
 *_____________________________________________________________________________
 *  This method will remove the given Category from the Tracker
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    category exists
 *
 *  POST-CONDITIONS
 *    The given Category is removed
 ******************************************************************************/
void Tracker::removeCategory(QString category) {
    int i = find(category);

    if(i != -1) {
        _categories.erase(_categories.begin()+i);
    }
}

/******************************************************************************
 *
 *  Mutator changeCategoryName: Class Tracker
 *_____________________________________________________________________________
 *  This method will change the name of a Category
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    old category name exists
 *
 *  POST-CONDITIONS
 *    A Category's name is changed
 ******************************************************************************/
void Tracker::changeCategoryName(QString old, QString category) {
    int i = find(old);

    if(i != -1) {
        _categories[i].setCategoryName(category);
    }
}

/******************************************************************************
 *
 *  Mutator addTransaction: Class Tracker
 *_____________________________________________________________________________
 *  This method will add a Transaction to the given category
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    category exists
 *
 *  POST-CONDITIONS
 *    A Transaction is added
 ******************************************************************************/
void Tracker::addTransaction(QString category, const Transaction& t) {
    int i = find(category);

    if(i != -1) {
        _categories[i].add(t);
    }
}

/******************************************************************************
 *
 *  Mutator addTransaction: Class Tracker
 *_____________________________________________________________________________
 *  This method will add a Transaction with the given info to the given category
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    category exists
 *
 *  POST-CONDITIONS
 *    A Transaction is added
 ******************************************************************************/
void Tracker::addTransaction(QString category, double cost, QString description,
                             const QDate& date, const QDateTime& time) {
    addTransaction(category, Transaction(cost, description, date, time, category));
}

/******************************************************************************
 *
 *  Mutator removeTransaction: Class Tracker
 *_____________________________________________________________________________
 *  This method will remove a Transaction from the given category
 *  - returns void
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    category exists
 *
 *  POST-CONDITIONS
 *    A Transaction is removed
 ******************************************************************************/
void Tracker::removeTransaction(QString category, const Transaction& t) {
    int i = find(category);

    if(i != -1) {
        _categories[i].remove(t);
    }
}

/******************************************************************************
 *
 *  Method exist: Class Category
 *_____________________________________________________________________________
 *  Search for the given Category name
 *  - returns bool
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    return true if the Category is found
 ******************************************************************************/
bool Tracker::exist(QString category) const {
    return find(category) != -1;
}

/******************************************************************************
 *
 *  Method exist: Class Category
 *_____________________________________________________________________________
 *  Search for the index of the given Category in the Tracker
 *  - returns int
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    return the index of the category, -1 otherwise
 ******************************************************************************/
int Tracker::find(QString category) const {
    int index = 0;

    for(const Category& c : _categories) {
        if(c.getCategory() == category) {
            return index;
        }
        index++;
    }

    return -1;
}

/******************************************************************************
 *
 *  Method at: Class Category
 *_____________________________________________________________________________
 *  Return the category at a given index of the Tracker
 *  - returns bool
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    index is valid
 *
 *  POST-CONDITIONS
 *    return the Category at index
 ******************************************************************************/
const Category& Tracker::at(int index) const {
    // prevent invalid index
    if(index < 0) {
        index = 0;
    } else if(index >= size()) {
        index = size() - 1;
    }

    return _categories[index];
}

/******************************************************************************
 *
 *  Method in: Class Category
 *_____________________________________________________________________________
 *  Return the number of Categories in the Tracker
 *  - returns int
 *_____________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    return size of Tracker
 ******************************************************************************/
int Tracker::size() const {
    return _categories.size();
}
