/********************************************************************************
** Form generated from reading UI file 'records.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECORDS_H
#define UI_RECORDS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_records
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTableWidget *tableWidget;

    void setupUi(QDialog *records)
    {
        if (records->objectName().isEmpty())
            records->setObjectName("records");
        records->resize(240, 320);
        verticalLayout = new QVBoxLayout(records);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(records);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(16);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        tableWidget = new QTableWidget(records);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName("tableWidget");

        verticalLayout->addWidget(tableWidget);


        retranslateUi(records);

        QMetaObject::connectSlotsByName(records);
    } // setupUi

    void retranslateUi(QDialog *records)
    {
        records->setWindowTitle(QCoreApplication::translate("records", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("records", "\320\240\320\265\320\272\320\276\321\200\320\264\321\213", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("records", "\320\237\320\276\320\277\321\213\321\202\320\276\320\272", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("records", "\320\230\320\274\321\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class records: public Ui_records {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECORDS_H
