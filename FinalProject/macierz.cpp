#include "macierz.h";



macierz::macierz(){}

macierz::macierz(int rr,int cc,float tablica[])
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

macierz::macierz(const macierz &a)
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

macierz::~macierz()
{
    for(int i=0;i<r;i++)
    {
        delete [] tab[i];
    }

    delete [] tab;
}

macierz macierz::mnoz(macierz A, macierz B)
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
