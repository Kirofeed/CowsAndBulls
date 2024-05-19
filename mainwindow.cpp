#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "records.h"
#include "namewindow.h"

#include <QHeaderView>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <random>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QList>
#include <QRegularExpression>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    recordsDialog(new records(this))
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    setStartProps();
    connect(ui->lineEdit, &QLineEdit::returnPressed, this, &MainWindow::checkInput);
    highScores = loadHighScores();
    connect(recordsDialog, &records::clearHighScores, this, &MainWindow::handleClearHighScores);
    setWindowTitle("Быки и Коровы");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete recordsDialog;
}

void MainWindow::start() {
    is_game = true;
    ui->startBtn->setText("Сдаться");
    ui->statusLabel->setText("Игра идет...");
    ui->recordsBtn->setDisabled(true);
    RandNum();
    ui->tableWidget->setRowCount(0);
    if (ui->lineEdit->text().size() == 4) {
        ui->checkBtn->setEnabled(true);
    }
}

void MainWindow::surrender()
{
    is_game  = false;
    ui->startBtn->setText("Новая игра");
    ui->statusLabel->setText("Игра не начата");
    ui->recordsBtn->setDisabled(false);
    ui->checkBtn->setDisabled(true);
    ui->tableWidget->setRowCount(0);
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
    QString result;
    if (bulls != 4) {
        result = QString("Быков: %1; Коров: %2").arg(bulls).arg(cows);
    } else {
        result = QString("Число угадано!!!");

        Record newRec;
        {
            NameWindow dialog(this);
            if (dialog.exec() == QDialog::Accepted) {
                QString playerName = dialog.GetName();
                newRec.score = ui->tableWidget->rowCount() + 1; // Считаем количество попыток
                newRec.name = playerName;
            }
        }
        if (!newRec.name.isEmpty()) {
            highScores.append(newRec);
            std::sort(highScores.begin(), highScores.end());
            if (highScores.size() > 10) {
                highScores.removeLast();
            }
            saveHighScores(highScores);
        }
        GameOver();
    }

    int rowCount = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(rowCount);

    QTableWidgetItem *numItem = new QTableWidgetItem(EnteredNum);
    QTableWidgetItem *resultItem = new QTableWidgetItem(result);

    // Размещение текста по центру
    numItem->setTextAlignment(Qt::AlignCenter);
    resultItem->setTextAlignment(Qt::AlignCenter);

    ui->tableWidget->setItem(rowCount, 0, numItem);
    ui->tableWidget->setItem(rowCount, 1, resultItem);

    QTimer::singleShot(0, this, [this, rowCount]() {
        ui->tableWidget->scrollTo(ui->tableWidget->model()->index(rowCount, 0), QAbstractItemView::PositionAtBottom);
    });
}


void MainWindow::checkInput()
{
    if ((ui->lineEdit->text().size() == 4) && (is_game)) {
        EnteredNum = ui->lineEdit->text();
        ProcessRequest();
    }
}

void MainWindow::GameOver()
{
    is_game = false;
    ui->checkBtn->setDisabled(true);
    ui->recordsBtn->setDisabled(false);
    ui->startBtn->setText("Новая игра");
    ui->statusLabel->setText("Игра завершена");

}


void MainWindow::saveHighScores(const QList<Record> &highScores)
{
    QJsonArray scoreArray;
    for (const Record &record : highScores) {
        QJsonObject scoreObject;
        scoreObject["name"] = record.name;
        scoreObject["score"] = record.score;
        scoreArray.append(scoreObject);
    }

    QJsonDocument saveDoc(scoreArray);
    QFile saveFile(QStringLiteral("highscores.json"));
    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }

    saveFile.write(saveDoc.toJson());
}

QList<Record> MainWindow::loadHighScores()
{
    QFile loadFile(QStringLiteral("highscores.json"));

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return QList<Record>();
    }

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QJsonArray scoreArray = loadDoc.array();

    QList<Record> highScores;
    for (int i = 0; i < scoreArray.size(); ++i) {
        QJsonObject scoreObject = scoreArray[i].toObject();
        Record record;
        record.name = scoreObject["name"].toString();
        record.score = scoreObject["score"].toInt();
        highScores.append(record);
    }

    return highScores;
}

void MainWindow::addHighScore(QList<Record> &highScores, const Record &newRecord)
{
    // Если таблица рекордов меньше 10 записей, просто добавляем новый результат
    if (highScores.size() < 10) {
        highScores.append(newRecord);
    } else {
        // Находим худший рекорд
        auto worstRecordIt = std::max_element(highScores.begin(), highScores.end());
        // Если новый результат лучше худшего, заменяем его
        if (newRecord.score < worstRecordIt->score) {
            *worstRecordIt = newRecord;
        }
    }
    // Сортируем таблицу рекордов
    std::sort(highScores.begin(), highScores.end());
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
    recordsDialog->createRecordsTable(highScores);
    recordsDialog->exec();
}



void MainWindow::on_lineEdit_textEdited()
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

void MainWindow::handleClearHighScores()
{
    highScores.clear();
    saveHighScores(highScores);
}

