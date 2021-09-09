#ifndef CATEGORY_H
#define CATEGORY_H

#include "transaction.h"
#include <QString>
#include <QDateTime>
#include <vector>

class Category {
  public:
    /*****************
     ** CONSTRUCTOR **
     *****************/
    Category();
    explicit Category(QString category);

    /***************
     ** ACCESSORS **
     ***************/
    const std::vector<Transaction>& getTransDate() const;
    std::vector<Transaction> getTransDate(const QDate& start,
                                                 const QDate& end = QDate::currentDate());
    std::vector<Transaction> searchTransDate(QString keyword) const;
    const std::vector<Transaction>& getTransAmount() const;
    std::vector<Transaction> getTransAmount(const QDate& start,
                                                   const QDate& end = QDate::currentDate());
    QString getCategory() const;
    bool exist(const Transaction& t) const;
    int size() const;

    /**************
     ** MUTATORS **
     **************/
    void setCategoryName(QString category);
    void add(const Transaction& t);
    void add(double cost, QString description = "",
             const QDate& date = QDate::currentDate(),
             const QDateTime& time = QDateTime::currentDateTime());
    void remove(const Transaction& t);
    void clear();

    bool operator ==(const Category& t) const;
    bool operator !=(const Category& t) const;
    bool operator >(const Category& t) const;
    bool operator <(const Category& t) const;
    bool operator >=(const Category& t) const;
    bool operator <=(const Category& t) const;

  private:
    std::vector<Transaction> _transDate;
    std::vector<Transaction> _transAmount;
    QString _category;
};

#endif // CATEGORY_H
