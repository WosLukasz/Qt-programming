#include "okno.h"

#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <math.h>

Okno::Okno(QWidget *parent) : QWidget(parent)
{
    im = QImage(900,500,QImage::Format_RGB32);

    im.fill(Qt::black);
    g=0;
    opcja =1;
    z=0;


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
    Point p;
    p.x=ev->x();
    p.y=ev->y();

    if(opcja==1)
    {
        putPixel(p.x,p.y,255,255,255);
       tab.push_back(p);
       g++;
    }
    else if(opcja ==2)
    {
        for(int i=0;i<tab.size();i++)
        {
            if((tab[i].x-p.x)*(tab[i].x-p.x) + (tab[i].y-p.y)*(tab[i].y-p.y)<= 16)
            {

                z=i;
            }
        }
    }
    else if(opcja ==3)
    {
        for(int i=0;i<tab.size();i++)
        {
            if((tab[i].x-p.x)*(tab[i].x-p.x) + (tab[i].y-p.y)*(tab[i].y-p.y)<= 120)
            {
                tab.erase(tab.begin()+i);
                im.fill(Qt::black);
                for(int i=0;i<tab.size();i++)
                {
                    putPixel(tab[i].x,tab[i].y,255,255,255);
                }
                update();
            }
        }

    }



     if(g>=4)
     {
         for(int i=4;i<=tab.size();i++)
         {
             drawBezier(tab[i-4],tab[i-3],tab[i-2],tab[i-1]);
         }


     }
     update();
}

void Okno::mouseMoveEvent(QMouseEvent *ev)
{
    if(opcja ==2)
    {
        tab[z].x=ev->x();
        tab[z].y=ev->y();

        im.fill(Qt::black);

        for(int i=0;i<tab.size();i++)
        {
            putPixel(tab[i].x,tab[i].y,255,255,255);
        }

        if(g>=4)
        {
            for(int i=4;i<=tab.size();i++)
            {
                drawBezier(tab[i-4],tab[i-3],tab[i-2],tab[i-1]);
            }


        }
        update();


    }
}

void Okno::mouseReleaseEvent(QMouseEvent *ev)
{

}

void Okno::but1()
{
    opcja =1;
}

void Okno::but2()
{
    opcja =2;
}

void Okno::but3()
{
    opcja =3;
}

void Okno::drawLine(float x1, float y1, float x2, float y2, int r, int g, int b)
{


        float a,N;
        int x,y;

        uchar *buf ;




        if(abs(x2-x1) >=abs(y2-y1))
        {

            if(x1<x2)
            {


                for(x=x1;x<=x2;x++)
                {

                        y=(y2-y1)*(x-x1)/(x2-x1)+y1;

                        if(x>=0 && x<im.width() && y>=0 && y<im.height())
                        {
                            buf= im.scanLine(y);

                            buf[4*x]=b;
                            buf[4*x+1]=g;
                            buf[4*x+2]=r;

                        }
                }
            }else
            {
                for(x=x2;x<=x1;x++)
                {

                        y=(y1-y2)*(x-x2)/(x1-x2)+y2;

                        if(x>=0 && x<im.width() && y>=0 && y<im.height())
                        {
                            buf= im.scanLine(y);

                            buf[4*x]=b;
                            buf[4*x+1]=g;
                            buf[4*x+2]=r;

                        }
                }
            }


        }else
        {
            if(y1<y2)
            {


                for(y=y1;y<=y2;y++)
                {

                        x=(x2-x1)*(y-y1)/(y2-y1)+x1;

                        if(x>=0 && x<im.width() && y>=0 && y<im.height())
                        {
                            buf= im.scanLine(y);

                            buf[4*x]=b;
                            buf[4*x+1]=g;
                            buf[4*x+2]=r;

                        }
                }
            }else
            {
                for(y=y2;y<=y1;y++)
                {

                        x=(x1-x2)*(y-y2)/(y1-y2)+x2;

                        if(x>=0 && x<im.width() && y>=0 && y<im.height())
                        {
                            buf= im.scanLine(y);

                            buf[4*x]=b;
                            buf[4*x+1]=g;
                            buf[4*x+2]=r;

                        }
                }
            }

        }
}

void Okno::drawBezier(Okno::Point a, Okno::Point b, Okno::Point c, Okno::Point d)
{
    int N=64;

    float x1,y1,x2,y2;

    x1=a.x;
    y1=a.y;
    float t;

    for(int i=0;i<=N;i++)
    {
        t=(float)i/(float)N;

        x2=(1.0/6)*(-t*t*t + 3*t*t -3*t +1)*a.x+(1.0/6)*(3*t*t*t - 6*t*t +4)*b.x +(1./6)*(-3*t*t*t + 3*t*t +3*t +1)*c.x+(1./6)*t*t*t*d.x;
        y2=(1.0/6)*(-t*t*t + 3*t*t -3*t +1)*a.y+(1./6)*(3*t*t*t - 6*t*t +4)*b.y +(1./6)*(-3*t*t*t + 3*t*t +3*t +1)*c.y+(1./6)*t*t*t*d.y;

        if(i!=0)
           drawLine(x1,y1,x2,y2,255,255,255);



        x1=x2;
        y1=y2;


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
