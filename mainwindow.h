#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_startBtn_clicked();

    void on_recordsBtn_clicked();

    void on_lineEdit_textEdited(const QString &arg1);

    void on_checkBtn_clicked();

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

    QString SecretNum;
    QString EnteredNum;

    Ui::MainWindow *ui;
    bool is_game = false;
};
#endif // MAINWINDOW_H
