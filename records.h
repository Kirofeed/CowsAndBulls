#ifndef RECORDS_H
#define RECORDS_H


#include "record.h"


#include <QDialog>


namespace Ui {
class records;
}

class records : public QDialog
{
    friend class MainWindow;
    Q_OBJECT


public:
    explicit records(QWidget *parent = nullptr);
    ~records();

signals:
    void clearHighScores();  // Объявление сигнала

private slots:
    void on_pushButton_clicked();

private:
    void clearJsonFile();
    void createRecordsTable(const QList<Record> &records);
    Ui::records *ui;
};

#endif // RECORDS_H
