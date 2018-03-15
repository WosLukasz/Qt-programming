#ifndef OKNO2_H
#define OKNO2_H

#include <QWidget>

class Okno2 : public QWidget
{
    Q_OBJECT
public:
    explicit Okno2(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);


signals:

public slots:

    void czysc();

private:
    QImage im;

    void putPixel(int x, int y , int r, int g, int b);
    void sprayPixel(int x, int y , int r, int g, int b);
};

#endif // OKNO2_H
