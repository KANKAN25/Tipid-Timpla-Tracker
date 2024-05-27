#ifndef EDITEATERY_H
#define EDITEATERY_H

#include <QDialog>

namespace Ui {
class EditEatery;
}

class EditEatery : public QDialog
{
    Q_OBJECT

public:
    explicit EditEatery(QWidget *parent = nullptr);
    ~EditEatery();

private:
    Ui::EditEatery *ui;
};

#endif // EDITEATERY_H
