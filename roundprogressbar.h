#ifndef ROUNDPROGRESSBAR_H
#define ROUNDPROGRESSBAR_H

#include <QWidget>

class RoundProgressBar : public QWidget
{
    Q_OBJECT
public:
    explicit RoundProgressBar(QWidget *parent = nullptr);

    void upd(qreal new_val);
    void paintEvent(QPaintEvent *);

private:
    qreal progress; // progress 0.0 to 1.0
    int pen_width;

signals:

public slots:
};

#endif // ROUNDPROGRESSBAR_H
