#include "namewindow.h"
#include "ui_namewindow.h"

NameWindow::NameWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NameWindow)
{
    ui->setupUi(this);
    this->setWindowModality(Qt::WindowModal);
    setWindowTitle(" ");
}

NameWindow::~NameWindow()
{
    delete ui;
}

QString NameWindow::GetName()
{
    return (ui->lineEdit->text());
}
