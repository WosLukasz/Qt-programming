#include "okno2.h"

#include <QMouseEvent>
#include <QPainter>

Okno2::Okno2(QWidget *parent) : QWidget(parent)
{
    im = QImage(1400,600,QImage::Format_RGB32);

    im.fill(Qt::black);


}

void Okno2::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    //p.fillRect(0,0,width(),height(),Qt::blue);

    p.drawImage(0,0,im);

}

void Okno2::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton) // kropka
    {
        putPixel(ev->x(), ev->y(), 255, 255, 255);
    } else if(ev->button() == Qt::RightButton) //spray
    {
        sprayPixel(ev->x(), ev->y(), 255, 255, 255);
    }
}

void Okno2::mouseMoveEvent(QMouseEvent *ev)
{

    if(ev->buttons() & Qt::LeftButton) //jesli jest przytrzymywany przycisk to trzeba uzyc funkcji buttons a nie button || linia
    {
        putPixel(ev->x(), ev->y(), 255, 255, 255);
    } else if(ev->buttons() & Qt::RightButton) //spray
    {
        sprayPixel(ev->x(), ev->y(), 255, 255, 255);
    }
}

void Okno2::mouseReleaseEvent(QMouseEvent *)
{

}

void Okno2::czysc()
{
    //im = QImage(1400,600,QImage::Format_RGB32);

    im.fill(Qt::black);
    update();
}

void Okno2::putPixel(int x, int y, int r, int g, int b)
{

    if(x>=0 && y>=0 && x<im.width() && y<im.height())
    {
         uchar *buf = im.scanLine(y);
         buf[4*x]=b;
         buf[4*x+1]=g;
         buf[4*x+2]=r;

    }
    update();
}

void Okno2::sprayPixel(int x, int y, int r, int g, int b)
{
    uchar *buf;
        for(int i=0;i<7;i++)
        {
            y=y+rand()%21-10;
            x=x+rand()%21-10;

            if(x>=0 && y>=0 && x<im.width() && y<im.height())
            {
                buf = im.scanLine(y);
                buf[4*x]=b;
                buf[4*x+1]=g;
                buf[4*x+2]=r;
            }
        }




    update();
}
