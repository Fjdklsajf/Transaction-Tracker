#ifndef TRACKER_H
#define TRACKER_H

#include "transaction.h"
#include "category.h"
#include <QString>
#include <QDateTime>
#include <vector>

class Tracker {
  public:
    /*****************
     ** CONSTRUCTOR **
     *****************/
    Tracker();
    explicit Tracker(QString title);

    /***************
     ** ACCESSORS **
     ***************/
    QString getTitle() const;
    const std::vector<Category>& getCategories() const;
    std::vector<QString> getCategoryNames() const;
    const Category& getCategory(QString category) const;
    const std::vector<Transaction>& getTransDate(QString category) const;
    const std::vector<Transaction>& getTransAmount(QString category) const;
    std::vector<Transaction> getAllTransactions();
    std::vector<Transaction> getTransDateSorted();
    std::vector<Transaction> getTransAmountSorted();
    bool exist(QString category) const;
    int find(QString category) const;
    const Category& at(int index) const;
    int size() const;

    /**************
     ** MUTATORS **
     **************/
    void setTitle(QString title);
    void addCategory(const Category& category);
    void addCategory(QString category);
    void clearCategory(QString category);
    void removeCategory(QString category);
    void changeCategoryName(QString old, QString category);
    void addTransaction(QString category, const Transaction& t);
    void addTransaction(QString category, double cost, QString description = "",
                        const QDate& date = QDate::currentDate(),
                        const QDateTime& time = QDateTime::currentDateTime());
    void removeTransaction(QString category, const Transaction& t);



  private:
    std::vector<Category> _categories;
    QString _title;
};

#endif // TRACKER_H
