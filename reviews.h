#ifndef REVIEWS_H
#define REVIEWS_H

#include <QDialog>
#include <QStackedWidget>

namespace Ui {
class Reviews;
}

class Reviews : public QDialog
{
    Q_OBJECT

public:
    explicit Reviews(QWidget *parent = nullptr);
    ~Reviews();

private slots:
    void showPage();
    void showPage2();
    void on_pushButton_AddReview_clicked();

private:
    Ui::Reviews *ui;
    QStackedWidget *stackedWidget;
};

#endif // REVIEWS_H
