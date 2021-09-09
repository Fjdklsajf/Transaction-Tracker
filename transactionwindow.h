#ifndef TRANSACTIONWINDOW_H
#define TRANSACTIONWINDOW_H

#include <QDialog>
#include <QDate>
#include <QString>

namespace Ui {
    class TransactionWindow;
}

class TransactionWindow : public QDialog {
    Q_OBJECT

  public:
    explicit TransactionWindow(QWidget *parent = nullptr,
                               const std::vector<QString>& categories = std::vector<QString>());
    TransactionWindow(const std::vector<QString>& categories, const QDate& d,
                      double cost, QString descrip, QWidget *parent = nullptr);
    ~TransactionWindow();

    const QDate& date() const;
    double cost() const;
    QString description() const;
    bool save() const;
    QString category() const;
    void setCategory(QString cat);


  private slots:
    void on_saveButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::TransactionWindow *ui;
    QDate _date;
    double _cost;
    QString _description;
    bool _save;
};

#endif // TRANSACTIONWINDOW_H
