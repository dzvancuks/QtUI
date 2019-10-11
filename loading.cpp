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

Loading::Loading(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Loading)
{
    ui->setupUi(this);

    // TODO make opaque and remove this code as main window is black ?
    // set black background
    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::black);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    this->show();

    QVBoxLayout *layout = new QVBoxLayout(this);
    bar = new RoundProgressBar();
    layout->addWidget(bar);
    // TODO add CPBar. Split 100 and % sign

    connect(&lic, &LoaderIncrementerThread::finished, this, &Loading::fade_out);
    connect(&lic, &LoaderIncrementerThread::value_changed, this, &Loading::show_progress);
    lic.start();
}

Loading::~Loading()
{
    delete ui;
    if(lic.isRunning()) lic.wait();
}

void Loading::fade_out()
{
    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
    this->setGraphicsEffect(eff);
    QPropertyAnimation *animation = new QPropertyAnimation(eff, "opacity");
    animation->setDuration(1500);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->setEasingCurve(QEasingCurve::Linear);
    animation->start(QPropertyAnimation::DeleteWhenStopped);
    connect(animation, &QPropertyAnimation::finished, this, &Loading::hide_me);
}

void Loading::show_progress()
{
    int progress = lic.get();
    QString loaded = QString::number(progress) + "%";
    ui->lbl_loaded->setText(loaded);
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
    while(progress < 100)
    {
        m.lock();
        this->progress++;
        m.unlock();
        emit value_changed();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int LoaderIncrementerThread::get() const
{
    int ret;
    m.lock();
    ret = progress;
    m.unlock();
    return ret;
}
