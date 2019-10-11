#ifndef TIMEDATE_H
#define TIMEDATE_H

#include <QFrame>

namespace Ui {
class TimeDate;
}

class TimeDate : public QFrame
{
    Q_OBJECT

public:
    explicit TimeDate(QWidget *parent = nullptr);
    ~TimeDate();

private:
    Ui::TimeDate *ui;

private slots:
    void showTime();
};

#endif // TIMEDATE_H
