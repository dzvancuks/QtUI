#include "timedate.h"
#include "ui_timedate.h"

TimeDate::TimeDate(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::TimeDate)
{
    ui->setupUi(this);
}

TimeDate::~TimeDate()
{
    delete ui;
}
