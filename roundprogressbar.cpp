#include "roundprogressbar.h"

#include <QPainter>

RoundProgressBar::RoundProgressBar(QWidget *parent) : QWidget(parent), progress(0), pen_width(20)
{
    setMinimumSize(200, 200);
    setMaximumSize(200, 200);
}

void RoundProgressBar::upd(qreal new_val) {
    if (progress >= new_val) return;
    progress = new_val;
    update();
}

void RoundProgressBar::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPainterPath path;

    int border_offset = pen_width/2;
    path.moveTo(width()/2, border_offset);
    path.arcTo(QRectF(border_offset, border_offset, width()-pen_width, height()-pen_width), 90, -progress * 360);

    QPen pen;
    pen.setCapStyle(Qt::RoundCap);
    pen.setColor(QColor("#0000ff"));
    pen.setWidth(pen_width);
    painter.strokePath(path, pen);
}
