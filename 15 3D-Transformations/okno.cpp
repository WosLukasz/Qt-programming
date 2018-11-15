#include "okno.h"

#include <QMouseEvent>
#include <QPainter>
#include <stack>
#include <vector>
#include <iostream>
#include <math.h>

class macierz{

public:

float **tab;
int r,c;

    macierz(){}

    macierz(int rr,int cc,float tablica[])
    {
        r=rr;
        c=cc;

        tab= new float *[r];

        for(int i=0;i<r;i++)
        {
            tab[i] = new float [c];
        }
           int k=0;
        for(int i=0;i<rr;i++)
        {
            for(int j=0;j<cc;j++)
            {
                tab[i][j]=tablica[k];
                k++;
            }
        }
    }

    macierz(const macierz &a)
    {

        r=a.r;
        c=a.c;

        tab= new float *[r];

        for(int i=0;i<r;i++)
        {
            tab[i] = new float [c];
        }

         for(int i=0;i<r;i++)
         {
             for(int j=0;j<c;j++)
             {
                 tab[i][j]=a.tab[i][j];
             }
         }
    }

    ~macierz()
    {
        for(int i=0;i<r;i++)
        {
            delete [] tab[i];
        }

        delete [] tab;
    }

   macierz mnoz(macierz A, macierz B)
   {
       float tablica[(A.r*B.c)]={0};

       macierz C(A.r,B.c,tablica);

       for( int i = 0; i < A.r; i++ )
           {
               for( int j = 0; j < B.c; j++ )
               {

                   for( int k = 0; k < B.r; k++ )
                   {
                       C.tab[ i ][ j ] = C.tab[ i ][ j ] + A.tab[ i ][ k ] * B.tab[ k ][ j ];
                   }


               }

           }

       return C;
   }
};


Okno::Okno(QWidget *parent) : QWidget(parent)
{
    im = QImage(900,500,QImage::Format_RGB32);

        im.fill(Qt::black);

        cx=im.width()/2;
        cy=im.height()/2;

        v[0].x=0;
        v[0].y=0;
        v[0].z=0+600;

        v[1].x=200;
        v[1].y=0;
        v[1].z=0+600;

        v[2].x=0;
        v[2].y=200;
        v[2].z=0+600;

        v[3].x=200;
        v[3].y=200;
        v[3].z=0+600;

        v[4].x=0;
        v[4].y=0;
        v[4].z=200+600;

        v[5].x=200;
        v[5].y=0;
        v[5].z=200+600;

        v[6].x=0;
        v[6].y=200;
        v[6].z=200+600;

        v[7].x=200;
        v[7].y=200;
        v[7].z=200+600;


        face[0].a=0;
        face[0].b=1;
        face[0].c=2;

        face[1].a=3;
        face[1].b=1;
        face[1].c=2;

        face[2].a=0;
        face[2].b=4;
        face[2].c=6;

        face[3].a=0;
        face[3].b=6;
        face[3].c=2;

        face[4].a=0;
        face[4].b=1;
        face[4].c=4;

        face[5].a=1;
        face[5].b=4;
        face[5].c=5;

        face[6].a=1;
        face[6].b=5;
        face[6].c=7;

        face[7].a=1;
        face[7].b=3;
        face[7].c=7;

        face[8].a=3;
        face[8].b=6;
        face[8].c=2;

        face[9].a=3;
        face[9].b=6;
        face[9].c=7;

        face[10].a=4;
        face[10].b=5;
        face[10].c=7;

        face[11].a=4;
        face[11].b=7;
        face[11].c=6;


        SX=100.0/100.0;
        SY=100.0/100.0;
        SZ=100.0/100.0;

        TX=0;
        TY=0;
        TZ=0;

        RX=0;
        RY=0;
        RZ=0;

        rysuj_w_perspektywie();
}

void Okno::paintEvent(QPaintEvent *)
{
    QPainter p(this);


    p.drawImage(0,0,im);
}

void Okno::changeTX(int e)
{
    TX=(float)e;
    rysuj_w_perspektywie();
}

void Okno::changeTY(int e)
{
    TY=(float)e;
    rysuj_w_perspektywie();
}

void Okno::changeTZ(int e)
{
    TZ=(float)e;
    rysuj_w_perspektywie();
}

void Okno::changeRX(int e)
{
    RX=(float)e;
    rysuj_w_perspektywie();
}

void Okno::changeRY(int e)
{
    RY=(float)e;
    rysuj_w_perspektywie();
}

void Okno::changeRZ(int e)
{
    RZ=(float)e;
    rysuj_w_perspektywie();
}

void Okno::changeSX(int e)
{
    SX=(float)e/100.;
    rysuj_w_perspektywie();
}

void Okno::changeSY(int e)
{
    SY=(float)e/100.;
    rysuj_w_perspektywie();
}

void Okno::changeSZ(int e)
{
    SZ=(float)e/100.;
    rysuj_w_perspektywie();
}

float Okno::projekcja_perspX(float x, float y, float z)
{
    return (f*(x/z)+cx);
}

float Okno::projekcja_perspY(float x, float y, float z)
{
    return (f*(y/z)+cy);
}

void Okno::drawLine(float x1, float y1, float x2, float y2, int r, int g, int b)
{
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

void Okno::rysuj_w_perspektywie()
{

    float obrotx[16] = {1.,0.,0.,0.,
                        0.,cos((RX*M_PI)/180.),-sin((RX*M_PI)/180.),0.,
                       0.,sin((RX*M_PI)/180.),cos((RX*M_PI)/180.),0.,
                       0.,0.,0.,1.};
    float obroty[16] = {cos((RY*M_PI)/180.),0.,sin((RY*M_PI)/180.),0.,
                       0.,1.,0.,0.,
                       -sin((RY*M_PI)/180.),0.,cos((RY*M_PI)/180.),0.,
                       0.,0.,0.,1.};
    float obrotz[16] = {cos((RZ*M_PI)/180.),-sin((RZ*M_PI)/180.),0.,0.,
                       sin((RZ*M_PI)/180.),cos((RZ*M_PI)/180.),0.,0.,
                       0.,0.,1.,0.,
                       0.,0.,0.,1.};


    float przesuniecie[16] = {1.,0.,0.,TX,0.,1.,0.,TY,0.,0.,1.,TZ,0.,0.,0.,1.};
    float skala[16] = {SX,0.,0.,0.,0.,SY,0.,0.,0.,0.,SZ,0.,0.,0.,0.,1.};

    float przesuniecieDoPoczatku[16] = {1.,0.,0.,0,0.,1.,0.,0,0.,0.,1.,-600.,0.,0.,0.,1.};
    float przesuniecieDoSrodka[16] = {1.,0.,0.,0,0.,1.,0.,0,0.,0.,1.,600.,0.,0.,0.,1.};

    macierz A0(4,4,przesuniecieDoPoczatku);
    macierz A1(4,4,obrotx);
    macierz A2(4,4,obroty);
    macierz A3(4,4,obrotz);
    macierz A4(4,4,przesuniecieDoSrodka);

    macierz B= macierz(4,4,przesuniecie);
    macierz C= macierz(4,4,skala);

    macierz WYNIKOWAObrotu = WYNIKOWAObrotu.mnoz(A2,A1);
    macierz WYNIKOWAObrotu1 = WYNIKOWAObrotu.mnoz(A3,WYNIKOWAObrotu);


    macierz WYNIKOWA = WYNIKOWA.mnoz(B,C);


    for(int i=0;i<8;i++)
    {

     float tab1[4] = {v[i].x,v[i].y,v[i].z,1.};

    macierz D= macierz(4,1,tab1);

    macierz poczatkowaObrotu = poczatkowaObrotu.mnoz(A0,D);

    macierz KONCOWAObrotu = WYNIKOWAObrotu.mnoz(WYNIKOWAObrotu1,poczatkowaObrotu);

   macierz E=E.mnoz(A4,KONCOWAObrotu);

    macierz F=F.mnoz(WYNIKOWA,E);


     vp[i].x=F.tab[0][0]+1;
     vp[i].y=F.tab[1][0]+1;
     vp[i].z=F.tab[2][0]+1;

     v2d[i].x=projekcja_perspX(vp[i].x,vp[i].y,vp[i].z);
     v2d[i].y=projekcja_perspY(vp[i].x,vp[i].y,vp[i].z);
    }

    im.fill(Qt::black);
    for(int i =0;i<12;i++)
    {
        drawLine(v2d[face[i].a].x,v2d[face[i].a].y,v2d[face[i].b].x,v2d[face[i].b].y,255,255,255);
        drawLine(v2d[face[i].b].x,v2d[face[i].b].y,v2d[face[i].c].x,v2d[face[i].c].y,255,255,255);
        drawLine(v2d[face[i].c].x,v2d[face[i].c].y,v2d[face[i].a].x,v2d[face[i].a].y,255,255,255);
    }
    update();
}
