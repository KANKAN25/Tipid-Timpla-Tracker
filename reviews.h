#ifndef REVIEWS_H
#define REVIEWS_H

#include <QDialog>
#include <QLabel>
#include "JSONCarrienderiaReviewHandler.h"

namespace Ui {
class Reviews;
}

class Reviews : public QDialog
{
    Q_OBJECT

public:
    explicit Reviews(const QString& eateryName, QWidget *parent = nullptr);
    ~Reviews();

private slots:
    void showPage();
    void showPage2();
    void on_pushButton_AddReview_clicked();
    void clearReviews();

private:
    Ui::Reviews *ui;
    QString name_eateryName;
    JSONCarrienderiaReviewHandler reviewHandler; // Instance of review handler
    void loadReviews();
    void displayReview(const QString& user, const QString& review, QWidget* parent); // Add this helper method
};

#endif // REVIEWS_H
