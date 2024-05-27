#ifndef ADDREVIEW_H
#define ADDREVIEW_H

#include <QDialog>

namespace Ui {
class AddReview;
}

class AddReview : public QDialog
{
    Q_OBJECT

public:
    explicit AddReview(QWidget *parent = nullptr);
    ~AddReview();

private:
    Ui::AddReview *ui;
};

#endif // ADDREVIEW_H
