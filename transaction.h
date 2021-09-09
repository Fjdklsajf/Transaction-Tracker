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
    Transaction(double cost, QString descrip = "",
                const QDate& date = QDate::currentDate(),
                const QDateTime& time = QDateTime::currentDateTime(),
                QString category = "");

    /***************
     ** ACCESSORS **
     ***************/
    QString getDescription() const;
    QString getCategory() const;
    double getCost() const;
    const QDate& getDate() const;
    const QDateTime& getTimestamp() const;
    QString costText() const;
    QString dateFullText() const;
    QString dateShortText() const;
    QString timestampText() const;
    QString toString() const;
    bool contains(QString keyword) const;

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
};

#endif // TRANSACTION_H
