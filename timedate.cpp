#include "timedate.h"
#include "ui_timedate.h"

#include <QDateTime>
#include <QTimer>
#include <QString>

TimeDate::TimeDate(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::TimeDate)
{
    ui->setupUi(this);

    // set black background
    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::black);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    this->show();

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &TimeDate::showTime);
    timer->start(1000);

    showTime();
}

TimeDate::~TimeDate()
{
    delete ui;
}

void TimeDate::showTime()
{
    QDateTime dt = QDateTime::currentDateTime();
    QString time_hour = dt.toString("hh:");
    QString time_minutes = dt.toString("mm");
    QString day = dt.toString("dddd");
    QString date = dt.toString("MMM d");

    if(dt.time().second() % 2) time_hour[2] = ' '; // tick ':' for every second
    ui->lbl_hours->setText(time_hour);
    ui->lbl_minutes->setText(time_minutes);
    day[0] = day[0].toUpper(); // Capitalize day. Qt reference states that QDateTime Class returns capitalized, i.e. Monday. But its not
    ui->lbl_day->setText(day);
    date[0] = date[0].toUpper();
    ui->lbl_date->setText(date);
}
