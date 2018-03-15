#include "okno.h"

#include <QPaintEvent>
#include <QPainter>

Okno::Okno(QWidget *parent) : QWidget(parent)
{
    x=0;
    y=0;
}

void Okno::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    p.fillRect(0,0,width(),height(),Qt::blue);

    p.fillRect(x,y,50,50,Qt::red);

}

void Okno::mousePressEvent(QMouseEvent *vp)
{
       x=vp->x();
       y=vp->y();
       update();
}

void Okno::mouseMoveEvent(QMouseEvent *vp)
{
    x=vp->x();
    y=vp->y();
    update();
}

void Okno::mouseReleaseEvent(QMouseEvent *vp)
{
    x=vp->x();
    y=vp->y();
    update();
}

void Okno::setX(int v)
{
    x=v;
    update();
}

void Okno::setY(int v)
{
    y=250-v;
    update();
}
