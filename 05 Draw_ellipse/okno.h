#ifndef OKNO_H
#define OKNO_H

#include <QWidget>

class Okno : public QWidget
{
    Q_OBJECT
public:
    explicit Okno(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);


signals:

public slots:
    void obsl(int);

private:

    QImage im;
    float x,y,x9,y9;

    void putPixel(int x, int y,int r, int g, int b);
    void drawCircle(float x1, float y1, float x2, float y2);
    void drawCircle2(int x1, int y1, int x2, int y2,int al);
    void drawWheel(float x1, float y1, float x2, float y2);
    void drawLine(float x1, float y1, float x2, float y2,int r, int g, int b);

};

#endif // OKNO_H
