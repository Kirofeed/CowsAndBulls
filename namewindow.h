#ifndef NAMEWINDOW_H
#define NAMEWINDOW_H

#include <QDialog>

namespace Ui {
class NameWindow;
}

class NameWindow : public QDialog
{
    friend class MainWindow;
    Q_OBJECT

public:
    explicit NameWindow(QWidget *parent = nullptr);
    ~NameWindow();

private:
    Ui::NameWindow *ui;
    QString GetName();
};

#endif // NAMEWINDOW_H
