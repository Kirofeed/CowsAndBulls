#include "records.h"
#include "ui_records.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QList>

records::records(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::records)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->setWindowModality(Qt::WindowModal);
    setWindowTitle("Рекорды");
}

records::~records()
{
    delete ui;
}

void records::createRecordsTable(const QList<Record> &records)
{
    ui->tableWidget->setRowCount(0);
    int row;
    for (const auto& record : records) {
        row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        QTableWidgetItem* newItemScore = new QTableWidgetItem(QString::number(record.score));
        QTableWidgetItem* newItemName = new QTableWidgetItem(record.name);

        newItemScore->setTextAlignment(Qt::AlignCenter);
        newItemName->setTextAlignment(Qt::AlignCenter);

        ui->tableWidget->setItem(row, 0, newItemScore);
        ui->tableWidget->setItem(row, 1, newItemName);
    }
}


void records::clearJsonFile()
{
    QFile file("highscores.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Не удалось открыть файл для чтения";
        return;
    }

    // Читаем содержимое файла
    QByteArray fileData = file.readAll();
    file.close();

    // Парсим JSON данные
    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
    if (jsonDoc.isNull()) {
        qWarning() << "Ошибка при парсинге JSON данных.";
        return;
    }

    QJsonObject emptyObject;

    jsonDoc.setObject(emptyObject);

    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Не удалось открыть файл для записи";
        return;
    }

    file.write(jsonDoc.toJson(QJsonDocument::Indented));
    file.close();

    qDebug() << "Файл успешно очищен.";
}


void records::on_pushButton_clicked()
{
    clearJsonFile();
    ui->tableWidget->setRowCount(0);
    emit clearHighScores();
}

