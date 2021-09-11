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
    const std::vector<Transaction>& getTransAmount() const;
    std::vector<Transaction> getTransAmount(const QDate& start,
                                            const QDate& end = QDate::currentDate());
    QString getCategory() const;
    std::vector<Transaction> searchTransDate(QString keyword) const;

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

    /*******************************
     ** CONSTANT MEMBER FUNCTIONS **
     *******************************/
    bool exist(const Transaction& t) const;
    int size() const;

    /***********************
     ** OPERATOR OVERLOAD **
     ***********************/
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

/******************************************************************************
 *  Category Class
 *    Stores a number of transactions and their shared category title,
 *    two lists of transactions are saved, one sroted by date, another by amount
 ******************************************************************************/


/******************************
 ** CONSTRUCTOR & DESTRUCTOR **
 ******************************/

/******************************************************************************
 *  Category()
 *    Default Constructor; Initialize _category
 *    Parameters: none
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  explicit Category(QString category);
 *    Constructor; Initialize _category with given arguments
 *    Parameters: QString
 *    Return: void
 ******************************************************************************/


/***************
 ** ACCESSORS **
 ***************/

/******************************************************************************
 *  const std::vector<Transaction>& getTransDate() const;
 *
 *    Accessor; This method will return _transDate
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: const std::vector<Transaction>&
 ******************************************************************************/

/******************************************************************************
 *   std::vector<Transaction> getTransDate(const QDate& start,
                                           const QDate& end = QDate::currentDate());
 *
 *    Accessor; This method will return transactions between the start and end
 *      dates in _transDate
 * ----------------------------------------------------------------------------
 *    Parameters: const QDate&, const QDate&
 * ----------------------------------------------------------------------------
 *    Return: std::vector<Transaction>
 ******************************************************************************/

/******************************************************************************
 *  const std::vector<Transaction>& getTransAmount() const;
 *
 *    Accessor; This method will return _transAmount
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: const std::vector<Transaction>&
 ******************************************************************************/

/******************************************************************************
 *   std::vector<Transaction> getTransAmount(const QDate& start,
                                           const QDate& end = QDate::currentDate());
 *
 *    Accessor; This method will return transactions between the start and end
 *      dates in _transAmount
 * ----------------------------------------------------------------------------
 *    Parameters: const QDate&, const QDate&
 * ----------------------------------------------------------------------------
 *    Return: std::vector<Transaction>
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
 *   std::vector<Transaction> searchTransDate(QString keyword) const;
 *
 *    Accessor; This method will return transactions containing the keyword
 *      in _transAmount
 * ----------------------------------------------------------------------------
 *    Parameters: QString
 * ----------------------------------------------------------------------------
 *    Return: std::vector<Transaction>
 ******************************************************************************/


/**************
 ** MUTATORS **
 **************/

/******************************************************************************
 *  void setCategoryName(QString category);
 *
 *    Mutator; This method will update the _category attribute to the
 *      parameter category value
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
 *  void add(const Transaction& t);
 *
 *    Mutator; This method will add a Transaction in this Category
 * ----------------------------------------------------------------------------
 *    Parameters: const Transaction&
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void add(double cost, QString description = "",
             const QDate& date = QDate::currentDate(),
             const QDateTime& time = QDateTime::currentDateTime());
 *
 *    Mutator; This method will add a transactions in this category with the
 *      given parameter values
 * ----------------------------------------------------------------------------
 *    Parameters: double, QString, const QDate&, const QDateTime&
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void remove(const Transaction& t);
 *
 *    Mutator; This method will remove a transactions in this category
 * ----------------------------------------------------------------------------
 *    Parameters: const Transaction&
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void clear();
 *
 *    Mutator; This method will remove all transactions in this category
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/


/*******************************
 ** CONSTANT MEMBER FUNCTIONS **
 *******************************/

/******************************************************************************
 *  bool exist(const Transaction& t) const;
 *
 *    Search for the given Transaction in this category
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: bool
 ******************************************************************************/

/******************************************************************************
 *  int size() const;
 *
 *    Return the number of Transactions in the category
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: int
 ******************************************************************************/


/***********************
 ** OPERATOR OVERLOAD **
 ***********************/

/******************************************************************************
 *  bool operator ==(const Category& t) const;
 *
 *    Check if the categories have the same names
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: bool
 ******************************************************************************/

/******************************************************************************
 *  bool operator !=(const Category& t) const;
 *
 *    Check if the categories have different names
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: bool
 ******************************************************************************/

/******************************************************************************
 *  bool operator >(const Category& t) const;
 *
 *    Check if the current Category name is greater than the given parameter's
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: bool
 ******************************************************************************/

/******************************************************************************
 *  bool operator <(const Category& t) const;
 *
 *    Check if the current Category name is less than the given parameter's
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: bool
 ******************************************************************************/

/******************************************************************************
 *  bool operator >=(const Category& t) const;
 *
 *    Check if the current Category name is >= to the given parameter's
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: bool
 ******************************************************************************/

/******************************************************************************
 *  bool operator <=(const Category& t) const;
 *
 *    Check if the current Category name is <= to the given parameter's
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: bool
 ******************************************************************************/
