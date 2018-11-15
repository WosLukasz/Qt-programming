#ifndef OKNO_H
#define OKNO_H

#include <QWidget>
#include <vector>

class Okno : public QWidget
{
    Q_OBJECT
public:
    explicit Okno(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *);


public slots:

   // void rysuj();

    void changeTX(int);
    void changeTY(int);
    void changeTZ(int);

    void changeRX(int);
    void changeRY(int);
    void changeRZ(int);

    void changeSX(int);
    void changeSY(int);
    void changeSZ(int);

private:
    QImage im;



    struct Vertex{

      float x;
      float y;
      float z;

    };

    struct Face{

      int a,b,c;

    };
    Face face[12];
    Vertex v[8];
    Vertex vp[8];
    Vertex v2d[8];

    float f=500.;
    int cx,cy;


    float TX;
    float TY;
    float TZ;
    float RX;
    float RY;
    float RZ;
    float SX;
    float SY;
    float SZ;


    void drawLine(float x1, float y1, float x2, float y2, int r, int g, int b);
    float projekcja_perspX(float x,float y, float z);
    float projekcja_perspY(float x,float y, float z);
    void rysuj_w_perspektywie();


};

#endif // OKNO_H
