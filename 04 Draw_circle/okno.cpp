#include "okno.h"

#include <QMouseEvent>
#include <QPainter>


Okno::Okno(QWidget *parent) : QWidget(parent)
{
    im = QImage(600,350,QImage::Format_RGB32);

    im.fill(Qt::black);

    x=0;
    y=0;

    //setMouseTracking(true);

}
void Okno::paintEvent(QPaintEvent *)
{
    QPainter p(this);

   // p.fillRect(0,0,width(),height(),Qt::blue);

    p.drawImage(0,0,im);

}

void Okno::mousePressEvent(QMouseEvent *ev)
{
    x=ev->x();
    y=ev->y();
}

void Okno::mouseMoveEvent(QMouseEvent *ev)
{
    im.fill(Qt::black);

    if(ev->buttons() & Qt::LeftButton)
    {
        drawCircle(x,y,ev->x(),ev->y());

    } else if(ev->buttons() & Qt::RightButton)
    {
        drawWheel(x, y, ev->x(), ev->y());
    }






    update();

}

void Okno::mouseReleaseEvent(QMouseEvent *ev)
{



    if(ev->button() == Qt::LeftButton)
    {
         drawCircle(x,y,ev->x(),ev->y());
    } else if(ev->button() == Qt::RightButton)
    {
        drawWheel(x, y, ev->x(), ev->y());
    }
}


void Okno::drawCircle(float x1, float y1, float x2, float y2)
{

    float rkw = (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
    float r = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    int yy,xx;


    for(yy=0;yy<=r/sqrt(2);yy++)
    {
        xx=sqrt(rkw-yy*yy);

        putPixel(xx+x1,yy+y1,255,255,255);
        putPixel(-xx+x1,-yy+y1,255,255,255);
        putPixel(-xx+x1,yy+y1,255,255,255);
        putPixel(xx+x1,-yy+y1,255,255,255);
        putPixel(yy+x1,xx+y1,255,255,255);
        putPixel(-yy+x1,-xx+y1,255,255,255);
        putPixel(-yy+x1,xx+y1,255,255,255);
        putPixel(yy+x1,-xx+y1,255,255,255);

    }

}

void Okno::drawWheel(float x1, float y1, float x2, float y2)
{

    float rkw = (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
    float r = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    int yy,xx;

    uchar *buf;

    for(yy=0;yy<=r;yy++)
    {

        xx=sqrt(rkw-yy*yy);

        for(int i=0;i<2*xx;i++)
        {
            putPixel(x1-xx+i,y1+yy,255,255,255);
            putPixel(x1-xx+i,y1-yy,255,255,255);
        }

    }
}

void Okno::putPixel(int x, int y, int r, int g, int b)
{

    uchar *buf;


        if(x>=0 && x<im.width() && y>=0 && y<im.height())
        {
            buf= im.scanLine(y);

            buf[4*x]=b;
            buf[4*x+1]=g;
            buf[4*x+2]=r;

        }


    update();


}
