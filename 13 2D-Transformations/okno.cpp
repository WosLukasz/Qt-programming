#include "okno.h"

#include <QMouseEvent>
#include <QPainter>
#include <stack>
#include <vector>
#include <sstream>
#include <iostream>
#include <math.h>

/*
 * INT
class macierz{

public:

int **tab;
int r,c;

    macierz(){}

    macierz(int rr,int cc,int tablica[])
    {
        r=rr;
        c=cc;

        tab= new int *[r];

        for(int i=0;i<r;i++)
        {
            tab[i] = new int [c];
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

        tab= new int *[r];

        for(int i=0;i<r;i++)
        {
            tab[i] = new int [c];
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
       int tablica[(A.r*B.c)]={0};

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
*/


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


    im = QImage(820,570,QImage::Format_RGB32);

    im.fill(Qt::black);
    x=0;
    y=0;

    SX=100.;
    SY=100.;

    xx=820/2;
    yy=570/2;


    Point z[10];


    z[0].x=390;
    z[0].y=305;

    p.push_back(z[0]);

    z[1].x=390;
    z[1].y=265;

    p.push_back(z[1]);

    z[2].x=410;
    z[2].y=230;

    p.push_back(z[2]);
    z[3].x=430;
    z[3].y=265;

    p.push_back(z[3]);
    z[4].x=430;
    z[4].y=305;


    p.push_back(z[4]);


    stable = p;

   Vectorr v;

   v.a=z[0];
   v.b=z[1];

   vectors.push_back(v);

   v.a=z[1];
   v.b=z[2];

   vectors.push_back(v);

   v.a=z[2];
   v.b=z[3];

   vectors.push_back(v);

   v.a=z[3];
   v.b=z[4];

   vectors.push_back(v);
   v.a=z[4];
   v.b=z[0];

   vectors.push_back(v);


   for(int i =0;i<vectors.size();i++)
   {
       drawLine(vectors[i].a.x,vectors[i].a.y,vectors[i].b.x,vectors[i].b.y,255,255,255);
   }


}

void Okno::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    p.drawImage(0,0,im);

}

void Okno::mousePressEvent(QMouseEvent *ev)
{

}

void Okno::mouseMoveEvent(QMouseEvent *ev)
{

}

void Okno::mouseReleaseEvent(QMouseEvent *ev)
{

}

void Okno::sxchange(int e)
{
    SX=e;
    wykonaj_operacje();
}

void Okno::sychange(int e)
{
    SY = e;
    wykonaj_operacje();
}

void Okno::txchange(int e)
{
    TX = e;
    wykonaj_operacje();
}

void Okno::tychange(int e)
{
    TY=e;
    wykonaj_operacje();
}

void Okno::rrchange(int e)
{
    R=(float)e;
    wykonaj_operacje();
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

void Okno::wykonaj_operacje()
{


        // kolejnosc : obrot od punktu [0,0] a potem zlozona macierz skalowania i przesuniecia.

        float x,y;

        float obrot[9] = {cos((R*M_PI)/180.),-sin((R*M_PI)/180.),0,sin((R*M_PI)/180.),cos((R*M_PI)/180.),0,0,0,1};
        float przesuniecie[9] = {1.,0.,(float)TX,0.,1.,(float)TY,0.,0.,1.};
        float skala[9] = {((float)SX/100.),0.,0.,0.,((float)SY/100.),0.,0.,0.,1.};


       float obrot1[9] = {cos((R*M_PI)/180.),-sin((R*M_PI)/180.),(float)xx*(1.-cos((R*M_PI)/180.))+(float)yy*sin((R*M_PI)/180.),sin((R*M_PI)/180.),cos((R*M_PI)/180.),(float)yy*(1.-cos((R*M_PI)/180.))-(float)xx*sin((R*M_PI)/180.),0.,0.,1.};



        macierz A = macierz(3,3,obrot1);
        macierz B = macierz(3,3,przesuniecie);
        macierz C = macierz(3,3,skala);

        macierz WYNIKOWA ;
        WYNIKOWA = WYNIKOWA.mnoz(B,C);
        std::cout<<"wynik: "<<std::endl;
        for(int i =0;i<3;i++)
        {
            for(int j = 0 ; j< 3;j++)
            {
                std::cout<<WYNIKOWA.tab[i][j]<<" ";
            }
            std::cout<<std::endl;
        }

        //std::cout<<"dobrz utworzono tablice"<<std::endl;

        macierz D ;
        macierz E ;
        macierz F ;

        for(int i=0;i<p.size();i++)
        {
            x=(float)stable[i].x;
            y=(float)stable[i].y;

            float tab1[3] = {x,y,1.};

            D= macierz(3,1,tab1);


            E=E.mnoz(A,D);

            F=F.mnoz(WYNIKOWA,E);

            p[i].x=F.tab[0][0];
            p[i].y=F.tab[1][0];

        }

        vectors.clear();
        Vectorr v;

        v.a=p[0];
        v.b=p[1];

        vectors.push_back(v);

        v.a=p[1];
        v.b=p[2];

        vectors.push_back(v);

        v.a=p[2];
        v.b=p[3];

        vectors.push_back(v);

        v.a=p[3];
        v.b=p[4];

        vectors.push_back(v);
        v.a=p[4];
        v.b=p[0];

        vectors.push_back(v);



        im.fill(Qt::black);
        for(int i =0;i<vectors.size();i++)
        {
            drawLine(vectors[i].a.x,vectors[i].a.y,vectors[i].b.x,vectors[i].b.y,255,255,255);
        }

        update();
}


