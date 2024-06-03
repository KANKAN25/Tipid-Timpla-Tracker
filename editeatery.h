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

private slots:
    void on_pushButton_updateEatery_clicked();

    void on_pushButton_updateMenu_clicked();

    void on_pushButton_done_clicked();

    void on_pushButton_addMenu_clicked();

private:
    Ui::EditEatery *ui;
};

#endif // EDITEATERY_H
