#include "reviews.h"
#include "ui_reviews.h"
#include "addreview.h"

Reviews::Reviews(const QString& eateryName, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Reviews)
    , name_eateryName(eateryName)
{
    ui->setupUi(this);
    this->setFixedSize(347, 459); // Main window's fixed size

    QWidget *page = new QWidget();
    QWidget *page2 = new QWidget();

    // Index
    ui->stackedWidget->addWidget(page);
    ui->stackedWidget->addWidget(page2);

    // Setup connections for navigating pages
    connect(ui->next, &QPushButton::clicked, this, &Reviews::showPage2);
    connect(ui->back, &QPushButton::clicked, this, &Reviews::showPage);

    loadReviews();
    showPage(); // Ensure page1 is shown first
}

Reviews::~Reviews()
{
    delete ui;
}

void Reviews::showPage()
{
    // Get the index of the current page
    int currentIndex = ui->stackedWidget->currentIndex();

    // Switch to the previous page if it exists
    if (currentIndex - 1 >= 0) {
        ui->stackedWidget->setCurrentIndex(currentIndex - 1);
    }

    // Back button is disabled if the current page is the first page
    if (currentIndex <= 0) {
        ui->back->setEnabled(false);
    } else {
        ui->back->setEnabled(true);
    }

    // Always enable next button
    ui->next->setEnabled(true);
}

void Reviews::showPage2()
{
    // Get the index of the current page
    int currentIndex = ui->stackedWidget->currentIndex();

    // Switch to the next page if it exists
    if (currentIndex + 1 < ui->stackedWidget->count()) {
        ui->stackedWidget->setCurrentIndex(currentIndex + 1);
    }

    // Always enable back button
    ui->back->setEnabled(true);

    // Disable the next button
    if (ui->stackedWidget->currentIndex() == ui->stackedWidget->count() - 2) {
        ui->next->setEnabled(false);
    }
}



void Reviews::on_pushButton_AddReview_clicked()
{
    AddReview *addreview = new AddReview(name_eateryName, this); // Declaration
    addreview->show(); // Show the Add Review window

    connect(addreview, &QObject::destroyed, this, &Reviews::loadReviews); // Reload reviews when AddReview dialog is closed
    connect(addreview, &QObject::destroyed, addreview, &QObject::deleteLater); // Deallocates when closed
}

void Reviews::loadReviews()
{
    // Convert QString to std::string
    std::string name = name_eateryName.toStdString();

    // Load reviews from JSON file
    if (reviewHandler.load(name)) // Load reviews for the specific eatery
    {
        auto reviews = reviewHandler.getReviews();

        clearReviews();

        // Iterate through reviews and display them(5 limit)
        int reviewCount = 0;
        int pageIndex = 0;
        QWidget* parentPage = nullptr;
        QVBoxLayout* parentLayout = nullptr;

        for (const auto& review : reviews)
        {
            QString user = QString::fromStdString(review["User"]);
            QString reviewText = QString::fromStdString(review["Review"]);

            if (reviewCount % 5 == 0)
            {
                // Create a new page if needed
                if (reviewCount > 0) {
                    ++pageIndex;
                }
                if (pageIndex >= ui->stackedWidget->count()) {
                    QWidget *newPage = new QWidget();
                    ui->stackedWidget->addWidget(newPage);
                }
                parentPage = ui->stackedWidget->widget(pageIndex);
                parentLayout = qobject_cast<QVBoxLayout*>(parentPage->layout());
                if (!parentLayout)
                {
                    parentLayout = new QVBoxLayout(parentPage);
                    parentPage->setLayout(parentLayout);
                }
            }

            displayReview(user, reviewText, parentPage);
            ++reviewCount;
        }

        // Ensure that the back button is enabled
        ui->back->setEnabled(true);
    }
    else
    {
        // If loading fails, clear the existing reviews from the interface
        clearReviews();
    }
}



void Reviews::clearReviews()
{
    // Clear the existing widgets on the pages
    for (int i = 0; i < ui->stackedWidget->count(); ++i)
    {
        QWidget* page = ui->stackedWidget->widget(i);
        QLayout* layout = page->layout();
        if (layout != nullptr)
        {
            QLayoutItem* item;
            while ((item = layout->takeAt(0)) != nullptr)
            {
                QWidget* widget = item->widget();
                if (widget != nullptr)
                {
                    delete widget;
                }
                delete item;
            }
        }
    }
}



void Reviews::displayReview(const QString& user, const QString& review, QWidget* parent)
{
    // Create a frame to hold the review
    QFrame* frame = new QFrame(parent);
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Raised);

    QVBoxLayout* layout = new QVBoxLayout(frame);

    QLabel* userLabel = new QLabel(user, frame);
    userLabel->setFont(QFont("Lato", 10));
    userLabel->setAlignment(Qt::AlignLeft);

    QLabel* reviewLabel = new QLabel(review, frame);
    reviewLabel->setFont(QFont("Lato Light", 9));
    reviewLabel->setWordWrap(true);

    layout->addWidget(userLabel);
    layout->addWidget(reviewLabel);

    QVBoxLayout* parentLayout = qobject_cast<QVBoxLayout*>(parent->layout());
    if (!parentLayout)
    {
        parentLayout = new QVBoxLayout(parent);
        parent->setLayout(parentLayout);
    }
    parentLayout->addWidget(frame);
}
