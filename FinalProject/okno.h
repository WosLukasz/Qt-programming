#ifndef OKNO_H
#define OKNO_H

#include <QWidget>

class Okno : public QWidget
{
    Q_OBJECT
public:
    explicit Okno(QWidget *parent = nullptr);

    struct Vertex{

      float x;
      float y;
      float z;

    };

    struct Point
        {
            float x,y;
            float u,v;
            float z;

            Vertex N;
        };

    struct Face{

      int a,b,c;

    };
    std::vector<Point> p;

protected:
    void paintEvent(QPaintEvent *);
signals:

public slots:

    void changeTX(int);
    void changeTY(int);
    void changeTZ(int);

    void changeRX(int);
    void changeRY(int);
    void changeRZ(int);

    void changeSX(int);
    void changeSY(int);
    void changeSZ(int);

    void if_szkielet(bool);
    void if_texturowanie(bool);
    void if_backface(bool);
    void if_obr(bool);
    void if_z_buff(bool);

    void if_brakOsw(bool);
    void if_oswietlenie1(bool);
    void if_oswietlenie2(bool);
    void changeS1X(int);
    void changeS1Y(int);
    void changeS1Z(int);


    void change_to_1(bool);
    void change_to_3(bool);
    void change_to_4(bool);
    void change_to_5(bool);

    void change_text(QString);


private:

    QImage im;
    QImage im2;

    std::string path;
    std::string file;


    bool if_sz;
    bool if_text;
    bool is_backface;
    bool is_oswietlenie1;
    bool is_oswietlenie2;
    bool obracanie;
    bool isZbuff;
    Point S1;
    Point S2;

    std::vector<Point> uv;
    std::vector<Point> v;
    std::vector<Face> face;
    std::vector<Point> v2d;
    std::vector<Point>vp;

    int **zbuffor;


    float f=500.;
    float cx,cy;
    float doZ;
    int z,zx,zy;

    float TX;
    float TY;
    float TZ;
    float RX;
    float RY;
    float RZ;
    float SX;
    float SY;
    float SZ;

    int iss;
    float cs;


    void drawLine(float x1, float y1, float x2, float y2, int r, int g, int b);
    float projekcja_perspX(float x,float y, float z);
    float projekcja_perspY(float x,float y, float z);
    void rysuj_w_perspektywie();
    void b_sort( int ile_liczb);
    bool backface_culling(Point A,Point B,Point C);
    void wczytajPlik(std::string path);


    void scan_line2(std::vector<Point> pp);
    void draw_line2(float xl, float xr, float y, float ul, float vl, float ur, float vr,Vertex L, Vertex R,float zl,float zr);
    void drawDot(int x, int y, int r, int g, int b);
    float cos_norm_light(Point a, Point b, Point c);
    Vertex normalna(Point a, Point b, Point c);
    float cos_norm_light3(Point a,Vertex K);
    float cos_odbite_view(Point a, Vertex K, float B);
    float cos_odbite_view2(Point a, Vertex K, float B);
    void rysuj_swiatlo();


};

#endif // OKNO_H
