#ifndef EATERY_H
#define EATERY_H

#include <QDialog>

namespace Ui {
class Eatery;
}

class Eatery : public QDialog
{
    Q_OBJECT

public:
    explicit Eatery(QWidget *parent = nullptr);
    ~Eatery();

private:
    Ui::Eatery *ui;
};

#endif // EATERY_H
