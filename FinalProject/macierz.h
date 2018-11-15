#ifndef MACIERZ_H
#define MACIERZ_H

class macierz{

public:

float **tab;
int r,c;

    macierz();
    macierz(int rr,int cc,float tablica[]);
    macierz(const macierz &a);
    ~macierz();

    macierz mnoz(macierz A, macierz B);
};






#endif // MACIERZ_H
