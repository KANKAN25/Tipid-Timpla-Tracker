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

private:
    Ui::AddEatery *ui;
};

#endif // ADDEATERY_H
