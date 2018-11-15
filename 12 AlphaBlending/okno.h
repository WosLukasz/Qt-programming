#ifndef OKNO_H
#define OKNO_H

#include <QWidget>

class okno : public QWidget
{
    Q_OBJECT
public:
    int a;
    int k;
    QImage im0;
    QImage im00;
    QImage im;
    QImage im1;
    QImage im2;
    QImage im3;
    QImage im4;
    explicit okno(QWidget *parent = nullptr);

    struct Warstwa{
        int id;
        int mix;
        int al;
    };

    std::vector<Warstwa> warstwy;


private:

signals:

public slots:

    void odejmowanie(QImage imm);
    void dodawanie(QImage imm);
    void alphaupdate(int a);

    void zmiana1();
    void zmiana2();
    void zmiana3();
    void rysuj();
    void mix_1();
    void alpha_change(int a);
    void mix_2();
    void mnozenie(QImage imm);
    void mix_3();
    void mix_4();
    void lighten(QImage imm);
    void mix_5();
    void difference(QImage imm);

protected:
    void paintEvent(QPaintEvent *);

};

#endif // OKNO_H
