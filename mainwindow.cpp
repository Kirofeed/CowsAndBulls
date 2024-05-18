#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "stylehelper.h"
#include "records.h"

#include <QHeaderView>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <random>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    setStartProps();
    connect(ui->lineEdit, &QLineEdit::returnPressed, this, &MainWindow::checkInput);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start() {
    is_game = true;
    ui->startBtn->setText("Сдаться");
    ui->statusLabel->setText("Игра идет...");
    ui->recordsBtn->setDisabled(true);
    RandNum();
}

void MainWindow::surrender()
{
    is_game  = false;
    ui->startBtn->setText("Новая игра");
    ui->statusLabel->setText("Игра не начата");
    ui->recordsBtn->setDisabled(false);
}

void MainWindow::setStartProps()
{
    ProcessingLineEdit();
    ui->checkBtn->setDisabled(true);
}



void MainWindow::ProcessRequest()
{
    int cows;
    int bulls;

    bulls = 0;
    cows = 0;
    std::unordered_map<char, int> secretFreq;
    std::unordered_map<char, int> enteredFreq;

    // Первоначальный проход для нахождения быков
    for (int i = 0; i < SecretNum.size(); ++i) {
        if (SecretNum[i] == EnteredNum[i]) {
            bulls++;
        } else {
            char secretChar = SecretNum[i].toLatin1();
            char enteredChar = EnteredNum[i].toLatin1();
            // Считаем частоты символов, которые не являются быками
            secretFreq[secretChar]++;
            enteredFreq[enteredChar]++;
        }
    }

    // Второй проход для нахождения коров
    for (const auto& pair : enteredFreq) {
        char digit = pair.first;
        int countInEntered = pair.second;
        if (secretFreq.find(digit) != secretFreq.end()) {
            cows += std::min(countInEntered, secretFreq[digit]);
        }
    }

    addItemToTable(cows, bulls);
}

void MainWindow::RandNum()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1000, 9999);
    int random_number = dis(gen);
    SecretNum = QString::number(random_number);
    qDebug() << random_number;
}

void MainWindow::ProcessingLineEdit()
{
    QRegularExpression regExp("\\d{0,4}");
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(regExp, this);
    ui->lineEdit->setValidator(validator);
}

void MainWindow::addItemToTable(int cows, int bulls)
{

    int rowCount = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(rowCount);


    QString result;
    if (bulls != 4) {
        result = QString("Быков: %1; Коров: %2").arg(bulls).arg(cows);
    }
    else {
        result = QString("Число угадано!!!");
    }

    ui->tableWidget->setItem(rowCount, 0, new QTableWidgetItem(EnteredNum));
    ui->tableWidget->setItem(rowCount, 1, new QTableWidgetItem(result));

}

void MainWindow::checkInput()
{
    EnteredNum = ui->lineEdit->text();
    ProcessRequest();
}





void MainWindow::on_startBtn_clicked()
{
    if (!is_game) {
        start();
    }
    else {
        surrender();
    }
}


void MainWindow::on_recordsBtn_clicked()
{
    records *recordsWindow = new records(this);
    recordsWindow->setWindowModality(Qt::WindowModal);
    recordsWindow->show();

    connect(recordsWindow, &records::finished, recordsWindow, &records::deleteLater);
}



void MainWindow::on_lineEdit_textEdited(const QString &arg1)
{
    if(is_game) {
        if (ui->lineEdit->text().size() == 4) {
            ui->checkBtn->setDisabled(false);
        }
        else {
            ui->checkBtn->setDisabled(true);
        }
    }
    else {
        ui->checkBtn->setDisabled(true);
    }
}


void MainWindow::on_checkBtn_clicked()
{
    EnteredNum = ui->lineEdit->text();
    ProcessRequest();
}

