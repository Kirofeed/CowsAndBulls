#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "stylehelper.h"
#include "records.h"

#include <QHeaderView>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    setStartProps();
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
}


void MainWindow::on_recordsBtn_clicked()
{
    records *recordsWindow = new records(this);
    recordsWindow->setWindowModality(Qt::WindowModal);
    recordsWindow->show();

    connect(recordsWindow, &records::finished, recordsWindow, &records::deleteLater);
}

