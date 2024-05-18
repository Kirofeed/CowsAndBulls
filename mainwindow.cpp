#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "stylehelper.h"
#include "records.h"

#include <QHeaderView>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    setStartProps();


    QFile file("recors.txt");

    // Открываем файл в режиме чтения
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Не удалось открыть файл для чтения";
    }

    // Создаем объект QTextStream и связываем его с файлом
    QTextStream in(&file);

    // Читаем текст из файла и выводим его на консоль
    while (!in.atEnd()) {
        QString line = in.readLine();
        qDebug() << line;
    }

    // Закрываем файл
    file.close();
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
    ui->recordsBtn->setStyleSheet(stylehelper::GetDisableBtnStyle());
    ui->checkBtn->setStyleSheet("");
}

void MainWindow::surrender()
{
    is_game  = false;
    ui->startBtn->setText("Новая игра");
    ui->statusLabel->setText("Игра не начата");
    ui->recordsBtn->setDisabled(false);
    ui->recordsBtn->setStyleSheet("");
    ui->checkBtn->setStyleSheet(stylehelper::GetDisableBtnStyle());
}

void MainWindow::setStartProps()
{
    ui->checkBtn->setStyleSheet(stylehelper::GetDisableBtnStyle());
    ProcessingLineEdit();
}

void MainWindow::ProcessingLineEdit()
{
    QRegularExpression regExp("\\d{0,4}");
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(regExp, this);
    ui->lineEdit->setValidator(validator);
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


