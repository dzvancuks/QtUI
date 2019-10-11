#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "timedate.h"
#include "loading.h"

#include <QHBoxLayout>
#include <QStackedWidget>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // set black background
    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::black);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    this->show();

    QHBoxLayout *layout = new QHBoxLayout;
    QStackedWidget *stack = new QStackedWidget;
    layout->addWidget(stack);

    Loading *l = new Loading(stack);
    stack->addWidget(l);
    TimeDate *td = new TimeDate();
    stack->addWidget(td);

    setCentralWidget(new QWidget);
    centralWidget()->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

