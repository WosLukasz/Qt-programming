#ifndef OKNO3_H
#define OKNO3_H

#include <QWidget>

class Okno3 : public QWidget
{
    Q_OBJECT
public:
    explicit Okno3(QWidget *parent = nullptr);

signals:

public slots:
    void wywolaj();

protected:

    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);


private:
    QImage im;

    void zmieniaj();
};

#endif // OKNO3_H
