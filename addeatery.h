#ifndef ADDEATERY_H
#define ADDEATERY_H

#include <QDialog>

namespace Ui {
class AddEatery;
}

class AddEatery : public QDialog
{
    Q_OBJECT

public:
    explicit AddEatery(QWidget *parent = nullptr);
    ~AddEatery();

private slots:
    void on_pushButton_addEatery_clicked();

    void on_pushButton_addMenu_clicked();

    void on_pushButton_done_clicked();

private:
    Ui::AddEatery *ui;
};

#endif // ADDEATERY_H
