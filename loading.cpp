#include "loading.h"
#include "ui_loading.h"

#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QTimer>
#include <QThread>

#include <chrono>
#include <thread>
#include <mutex>

Loading::Loading(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Loading)
{
    ui->setupUi(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    bar = new RoundProgressBar();
    layout->addWidget(bar);

    connect(&lic, &LoaderIncrementerThread::finished, this, &Loading::fade_out);
    connect(&lic, &LoaderIncrementerThread::value_changed, this, &Loading::show_progress);
    lic.start();
}

Loading::~Loading()
{
    delete ui;
    if(lic.isRunning())
    {
        // try graceful shutdownm then terminate
        lic.abort = true;
        if(!lic.wait(1000))
        {
            lic.terminate();
        }
    }
}

void Loading::fade_out()
{
    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
    this->setGraphicsEffect(eff);
    QPropertyAnimation *animation = new QPropertyAnimation(eff, "opacity");
    connect(animation, &QPropertyAnimation::finished, this, &Loading::hide_me);
    animation->setDuration(1500);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->setEasingCurve(QEasingCurve::Linear);
    animation->start(QPropertyAnimation::DeleteWhenStopped);
}

void Loading::show_progress()
{
    int progress = lic.get();
    ui->lbl_loaded->setText(QString::number(progress));
    bar->upd(static_cast<double>(progress) / 100);
}

void Loading::hide_me()
{
    QWidget::hide();

    QStackedWidget *par = dynamic_cast<QStackedWidget*>(parent());
    if(par)
    {
        par->setCurrentIndex(par->currentIndex() + 1); // show next widget - TimeDate
    }
}

void LoaderIncrementerThread::run()
{
    while(!abort && progress < 100)
    {
        {
            std::lock_guard<std::mutex> lock(m);
            this->progress++;
        }
        emit value_changed();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int LoaderIncrementerThread::get() const
{
    std::lock_guard<std::mutex> lock(m);
    return progress;
}
