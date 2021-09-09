#include "tracker.h"
#include "transaction.h"
#include "category.h"
#include <QString>
#include <QDateTime>
#include <vector>

Tracker::Tracker() : _title("") {
}

Tracker::Tracker(QString title) : _title(title) {
}

QString Tracker::getTitle() const {
    return _title;
}

const std::vector<Category>& Tracker::getCategories() const {
    return _categories;
}

std::vector<QString> Tracker::getCategoryNames() const {
    std::vector<QString> names;
    for(const Category& c : _categories) {
        names.push_back(c.getCategory());
    }

    return names;
}


const Category& Tracker::getCategory(QString category) const {
    int i = find(category);

    return _categories[i];
}

const std::vector<Transaction>& Tracker::getTransDate(QString category) const {
    int i = find(category);

    return _categories[i].getTransDate();
}

const std::vector<Transaction>& Tracker::getTransAmount(QString category) const {
    int i = find(category);

    return _categories[i].getTransAmount();
}

std::vector<Transaction> Tracker::getAllTransactions() {
    std::vector<Transaction> t;

    for(const Category& c : _categories) {
        for(const Transaction& trans : c.getTransDate()) {
            t.push_back(trans);
        }
    }

    return t;
}

std::vector<Transaction> Tracker::getTransDateSorted() {
    if(_categories.size() <= 1) {
        return getAllTransactions();
    }

    std::vector<Transaction> sorted = getAllTransactions();
    std::sort(sorted.rbegin(), sorted.rend());

    return sorted;
}

std::vector<Transaction> Tracker::getTransAmountSorted() {
    if(_categories.size() <= 1) {
        return getAllTransactions();
    }

    std::vector<Transaction> sorted = getAllTransactions();
    std::sort(sorted.begin(), sorted.end(),
              [] (const Transaction& t1, const Transaction& t2) -> bool {
        return t1.getCost() > t2.getCost();
    });

    return sorted;
}

bool Tracker::exist(QString category) const {
    return find(category) != -1;
}

const Category& Tracker::at(int index) const {
    return _categories[index];
}


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

int Tracker::size() const {
    return _categories.size();
}

void Tracker::setTitle(QString title) {
    _title = title;
}

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

void Tracker::addCategory(QString category) {
    addCategory(Category(category));
}

void Tracker::clearCategory(QString category) {
    int i = find(category);

    if(i != -1) {
        _categories[i].clear();
    }
}

void Tracker::removeCategory(QString category) {
    int i = find(category);

    if(i != -1) {
        _categories.erase(_categories.begin()+i);
    }
}

void Tracker::changeCategoryName(QString old, QString category) {
    int i = find(old);

    if(i != -1) {
        _categories[i].setCategoryName(category);
    }
}

void Tracker::addTransaction(QString category, const Transaction& t) {
    int i = find(category);

    if(i != -1) {
        _categories[i].add(t);
    }
}

void Tracker::addTransaction(QString category, double cost, QString description,
                             const QDate& date, const QDateTime& time) {
    addTransaction(category, Transaction(cost, description, date, time, category));
}

void Tracker::removeTransaction(QString category, const Transaction& t) {
    int i = find(category);

    if(i != -1) {
        _categories[i].remove(t);
    }
}
