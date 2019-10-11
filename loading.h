#ifndef LOADING_H
#define LOADING_H

#include "roundprogressbar.h"

#include <QFrame>
#include <QThread>

namespace Ui {
class Loading;
}

class LoaderIncrementerThread : public QThread
{
    Q_OBJECT

public:
    LoaderIncrementerThread(QObject *parent = nullptr) : QThread(parent)
    {
    }

    void run() override;
    int get() const;
    bool abort = false; // terminate is unsafe, use flag workaround

signals:
    void value_changed();

private:
    mutable std::mutex m;
    int progress = 0;
};

class Loading : public QFrame
{
    Q_OBJECT

public:
    explicit Loading(QWidget *parent = nullptr);
    ~Loading();

private:
    Ui::Loading *ui;
    RoundProgressBar *bar;
    LoaderIncrementerThread lic;

private slots:
    void show_progress();
    void fade_out();
    void hide_me();
};

#endif // LOADING_H
