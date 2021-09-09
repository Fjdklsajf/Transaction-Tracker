#include "category.h"
#include <QString>
#include <QDateTime>
#include <vector>

Category::Category() : _category("") {
}

Category::Category(QString category) : _category(category) {
}

const std::vector<Transaction>& Category::getTransDate() const {
    return _transDate;
}

std::vector<Transaction> Category::getTransDate(const QDate& start, const QDate& end) {
    std::vector<Transaction> t;

    for(unsigned i = 0; i < _transDate.size(); i++) {
        // find starting date
        if(_transDate[i].getDate() >= start) {
            for(unsigned j = i; j < _transDate.size(); j++) {
                // adds every date in range
                if(_transDate[i].getDate() <= end) {
                    t.push_back(_transDate[i]);
                } else {
                    return t;
                }
                // reached end of the list
                break;
            }
        }
    }

    return t;
}

std::vector<Transaction> Category::searchTransDate(QString keyword) const {
    std::vector<Transaction> t;

    for(const Transaction& trans : _transDate) {
        if(trans.contains(keyword)) {
            t.push_back(trans);
        }
    }

    return t;
}

const std::vector<Transaction>& Category::getTransAmount() const {
    return _transAmount;
}

std::vector<Transaction> Category::getTransAmount(const QDate& start, const QDate& end) {
    std::vector<Transaction> t;

    for(const Transaction& trans : _transAmount) {
        if(trans.getDate() >= start && trans.getDate() <= end) {
            t.push_back(trans);
        }
    }

    return t;
}


QString Category::getCategory() const {
    return _category;
}

bool Category::exist(const Transaction& t) const {
    for(const Transaction& trans : _transDate) {
        if(trans == t) {
            return true;
        }
    }
    return false;
}

int Category::size() const {
    return _transDate.size();
}

void Category::setCategoryName(QString category) {
    _category = category;

    for(unsigned i = 0; i < _transDate.size(); i++) {
        _transDate[i].setCategory(category);
        _transAmount[i].setCategory(category);
    }
}

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

void Category::add(double cost, QString description, const QDate& date, const QDateTime& time) {
    add(Transaction(cost, description, date, time, _category));
}

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

void Category::clear() {
    _transDate.clear();
    _transAmount.clear();
}

bool Category::operator ==(const Category& t) const {
    return _category == t.getCategory();
}

bool Category::operator !=(const Category& t) const {
    return _category != t.getCategory();
}

bool Category::operator >(const Category& t) const {
    return _category > t.getCategory();
}

bool Category::operator <(const Category& t) const {
    return _category < t.getCategory();
}

bool Category::operator >=(const Category& t) const {
    return _category >= t.getCategory();
}

bool Category::operator <=(const Category& t) const {
    return _category <= t.getCategory();
}
