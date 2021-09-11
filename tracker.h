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

    /*******************************
     ** CONSTANT MEMBER FUNCTIONS **
     *******************************/
    bool exist(QString category) const;
    int find(QString category) const;
    const Category& at(int index) const;
    int size() const;

  private:
    std::vector<Category> _categories;
    QString _title;
};

#endif // TRACKER_H

/******************************************************************************
 *  Tracker Class
 *    Stores a list of categories each containing its Transctions
 ******************************************************************************/


/******************************
 ** CONSTRUCTOR & DESTRUCTOR **
 ******************************/

/******************************************************************************
 *  Tracker()
 *    Default Constructor; Initialize _title
 *    Parameters: none
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  explicit Tracker(QString title);
 *    Constructor; Initialize _title with given arguments
 *    Parameters: QString
 *    Return: void
 ******************************************************************************/


/***************
 ** ACCESSORS **
 ***************/

/******************************************************************************
 *  QString getTitle() const;
 *
 *    Accessor; This method will return _title
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: QString
 ******************************************************************************/

/******************************************************************************
 *   const std::vector<Category>& getCategories() const;
 *
 *    Accessor; This method will return _categories
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: const std::vector<Category>&
 ******************************************************************************/

/******************************************************************************
 *  std::vector<QString> getCategoryNames() const;
 *
 *    Accessor; This method will return a list of Category names
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: std::vector<QString>
 ******************************************************************************/

/******************************************************************************
 *    const Category& getCategory(QString category) const;
 *
 *    Accessor; This method will return a Category given its name
 * ----------------------------------------------------------------------------
 *    Parameters: QString
 * ----------------------------------------------------------------------------
 *    Return: const Category&
 ******************************************************************************/

/******************************************************************************
 *  const std::vector<Transaction>& getTransDate(QString category) const;
 *
 *    Accessor; This method will return all transactions in the given category
 *      sorted by dates
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: const std::vector<Transaction>&
 ******************************************************************************/

/******************************************************************************
 *  const std::vector<Transaction>& getTransAmount(QString category) const;
 *
 *    Accessor; This method will return all transactions in the given category
 *      sorted by amounts
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: const std::vector<Transaction>&
 ******************************************************************************/

/******************************************************************************
 *  std::vector<Transaction> getAllTransactions();
 *
 *    Accessor; This method will return all Transactions combined
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: std::vector<Transaction>
 ******************************************************************************/

/******************************************************************************
 *  std::vector<Transaction> getTransDateSorted();
 *
 *    Accessor; This method will return all Transactions combined sorted
 *      by dates
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: std::vector<Transaction>
 ******************************************************************************/

/******************************************************************************
 *  std::vector<Transaction> getTransAmountSorted();
 *
 *    Accessor; This method will return all Transactions combined sorted
 *      by amounts
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: std::vector<Transaction>
 ******************************************************************************/


/**************
 ** MUTATORS **
 **************/

/******************************************************************************
 *  void setTitle(QString title);
 *
 *    Mutator; This method will update the _title attribute to the
 *      parameter title value
 * ----------------------------------------------------------------------------
 *    Parameters: QString
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *   void addCategory(const Category& category);
 *
 *    Mutator; This method will add the given Category to the Tracker
 * ----------------------------------------------------------------------------
 *    Parameters: const Category&
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void addCategory(QString category);
 *
 *    Mutator; This method will create a new empty Category in the Tracker
 * ----------------------------------------------------------------------------
 *    Parameters: QString
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void clearCategory(QString category);
 *
 *    Mutator; This method will clear a Category in the Tracker
 * ----------------------------------------------------------------------------
 *    Parameters: QString
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void removeCategory(QString category);
 *
 *    Mutator; This method will remove a Category in this Tracker
 * ----------------------------------------------------------------------------
 *    Parameters: const Transaction&
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void changeCategoryName(QString old, QString category);
 *
 *    Mutator; This method will change the name of a Category
 * ----------------------------------------------------------------------------
 *    Parameters: QString, QString
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void addTransaction(QString category, const Transaction& t);
 *
 *    Mutator; This method will add a Transaction in the given Category if the
 *      category exists
 * ----------------------------------------------------------------------------
 *    Parameters: QString, const Transaction&
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 *  void addTransaction(QString category, double cost, QString description = "",
                        const QDate& date = QDate::currentDate(),
                        const QDateTime& time = QDateTime::currentDateTime());
 *
 *    Mutator; This method will add a Transaction with the given info in the
 *      given Category if the category exists
 * ----------------------------------------------------------------------------
 *    Parameters: QString, double, QString, const QDate&, const QDateTime&
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/

/******************************************************************************
 * void removeTransaction(QString category, const Transaction& t);
 *
 *    Mutator; This method will remove a Transaction in the given Category
 *      if the category exists
 * ----------------------------------------------------------------------------
 *    Parameters: QString, double, QString, const QDate&, const QDateTime&
 * ----------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************/


/*******************************
 ** CONSTANT MEMBER FUNCTIONS **
 *******************************/

/******************************************************************************
 *  bool exist(QString category) const;
 *
 *    Search for the given Category
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: bool
 ******************************************************************************/

/******************************************************************************
 *  int find(QString category) const;
 *
 *    Search for the index of the given Category in the Tracker
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: int
 ******************************************************************************/

/******************************************************************************
 *  const Category& at(int index) const;
 *
 *    Return the category at a given index of the Tracker
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: const Category&
 ******************************************************************************/

/******************************************************************************
 *  int size() const;
 *
 *    Return the number of Categories
 * ----------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------
 *    Return: int
 ******************************************************************************/
