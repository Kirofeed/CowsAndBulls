#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "records.h"
#include "record.h"
#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    friend class records;
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_startBtn_clicked();

    void on_recordsBtn_clicked();

    void on_lineEdit_textEdited();

    void on_checkBtn_clicked();

    void handleClearHighScores();

private:

    void start();
    void surrender();
    void setStartProps();
    void ProcessRequest();
    void RandNum();
    bool checkCows (QString enterednum, size_t indx);
    bool checkBull(QString enterednum, size_t indx);
    void ProcessingLineEdit();
    void addItemToTable(int cows, int bulls);
    void checkInput();
    void GameOver();
    void writeRecord();
    void saveHighScores(const QList<Record> &highScores);
    QList<Record> loadHighScores();
    void addHighScore(QList<Record> &highScores, const Record &newRecord);



    QString SecretNum;
    QString EnteredNum;

    Ui::MainWindow *ui;
    bool is_game = false;
    QList<Record> highScores;
    records *recordsDialog;
};
#endif // MAINWINDOW_H
