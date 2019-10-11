#include "loading.h"
#include "ui_loading.h"

Loading::Loading(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Loading)
{
    ui->setupUi(this);
}

Loading::~Loading()
{
    delete ui;
}
