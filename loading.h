#ifndef LOADING_H
#define LOADING_H

#include <QFrame>

namespace Ui {
class Loading;
}

class Loading : public QFrame
{
    Q_OBJECT

public:
    explicit Loading(QWidget *parent = nullptr);
    ~Loading();

private:
    Ui::Loading *ui;
};

#endif // LOADING_H
