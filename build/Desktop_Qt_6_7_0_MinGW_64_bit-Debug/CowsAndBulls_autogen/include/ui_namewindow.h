/********************************************************************************
** Form generated from reading UI file 'namewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NAMEWINDOW_H
#define UI_NAMEWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_NameWindow
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLineEdit *lineEdit;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *NameWindow)
    {
        if (NameWindow->objectName().isEmpty())
            NameWindow->setObjectName("NameWindow");
        NameWindow->resize(248, 139);
        NameWindow->setMaximumSize(QSize(250, 150));
        QFont font;
        font.setPointSize(13);
        NameWindow->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/icon.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        NameWindow->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(NameWindow);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(NameWindow);
        label->setObjectName("label");
        QFont font1;
        font1.setPointSize(15);
        label->setFont(font1);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        lineEdit = new QLineEdit(NameWindow);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setMinimumSize(QSize(150, 35));
        lineEdit->setMaximumSize(QSize(150, 16777215));
        lineEdit->setFont(font1);
        lineEdit->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(lineEdit);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(NameWindow);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(NameWindow);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, NameWindow, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, NameWindow, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(NameWindow);
    } // setupUi

    void retranslateUi(QDialog *NameWindow)
    {
        NameWindow->setWindowTitle(QCoreApplication::translate("NameWindow", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("NameWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\262\320\260\321\210\320\265 \320\270\320\274\321\217", nullptr));
        lineEdit->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class NameWindow: public Ui_NameWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NAMEWINDOW_H
