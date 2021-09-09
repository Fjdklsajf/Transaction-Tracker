#include "transaction.h"
#include <QDateTime>
#include <QString>

Transaction::Transaction() : Transaction(0, "") {
    _date = QDate::currentDate();
    _timestamp = QDateTime::currentDateTime();
    _category = "";
}

Transaction::Transaction(double cost, QString descrip, const QDate& date,
                         const QDateTime& time, QString category) :
    _cost(cost), _description(descrip), _date(date),
    _timestamp(time), _category(category) {
}

QString Transaction::getDescription() const {
    return _description;
}

QString Transaction::getCategory() const {
    return _category;
}

double Transaction::getCost() const {
    return _cost;
}

const QDate& Transaction::getDate() const {
    return _date;
}

const QDateTime& Transaction::getTimestamp() const {
    return _timestamp;
}

QString Transaction::costText() const {
    // $20.00
    return QString().asprintf("$%0.2f", _cost);
}

QString Transaction::dateFullText() const {
    return _date.toString("MMMM dd, yyyy");
}

QString Transaction::dateShortText() const {
    return _date.toString("MM/dd/yyyy");
}

QString Transaction::timestampText() const {
    return _timestamp.toString("yyyy:MM:dd:hh:mm:ss:zzz");
}

QString Transaction::toString() const {
    return _category + "\n" + dateFullText() + " -- " + costText() + "\n\n" + _description;
}

bool Transaction::contains(QString keyword) const {
    return _description.contains(keyword, Qt::CaseInsensitive);
}

void Transaction::setDescription(QString description) {
    _description = description;
}

void Transaction::setCategory(QString category) {
    _category = category;
}

void Transaction::setCost(double cost) {
    _cost = cost;
}

void Transaction::setDate(const QDate& date) {
    _date = date;
}

void Transaction::setDate(int year, int month, int day) {
    _date.setDate(year, month, day);
}

void Transaction::setTimestamp(const QDateTime &time) {
    _timestamp = time;
}

void Transaction::setTimestamp(int y, int M, int d, int h, int m, int s, int ms) {
    _timestamp.setDate(QDate(y, M, d));
    _timestamp.setTime(QTime(h, m, s, ms));
}

bool Transaction::operator ==(const Transaction& t) const {
    return (_cost == t.getCost() && _description == t.getDescription()
            && _date == t.getDate() && _timestamp == t.getTimestamp());
}
bool Transaction::operator !=(const Transaction& t) const {
    return !(*this == t);
}

bool Transaction::operator >(const Transaction& t) const {
    if (_date > t.getDate()) {
        return true;
    } else if(_date < t.getDate()) {
        return false;
    } else {
        return _timestamp > t.getTimestamp();
    }
}

bool Transaction::operator <(const Transaction& t) const {
    if (_date < t.getDate()) {
        return true;
    } else if(_date > t.getDate()) {
        return false;
    } else {
        return _timestamp < t.getTimestamp();
    }
}

bool Transaction::operator >=(const Transaction& t) const {
    if (_date > t.getDate()) {
        return true;
    } else if(_date < t.getDate()) {
        return false;
    } else {
        return _timestamp >= t.getTimestamp();
    }
}

bool Transaction::operator <=(const Transaction& t) const {
    if (_date < t.getDate()) {
        return true;
    } else if(_date > t.getDate()) {
        return false;
    } else {
        return _timestamp <= t.getTimestamp();
    }
}
