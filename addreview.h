#ifndef ADDREVIEW_H
#define ADDREVIEW_H

#include <QDialog>
#include "JSONUserHandler.h"
#include "JSONCarrienderiaReviewHandler.h"

namespace Ui {
class AddReview;
}

class AddReview : public QDialog
{
    Q_OBJECT

public:
    explicit AddReview(const QString& eateryName, QWidget *parent = nullptr);
    ~AddReview();

private slots:
    void on_submitButton_clicked();

private:
    Ui::AddReview *ui;
    QString name_eateryName;
    JSONUserHandler userHandler;
    JSONCarrienderiaReviewHandler reviewHandler;
};

#endif // ADDREVIEW_H
