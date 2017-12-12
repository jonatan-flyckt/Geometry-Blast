#pragma once

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <ctime>
#include <QGraphicsScene>
#include <QTimer>
#include <math.h>

#define PI 3.14159265

class Shape : public QObject, public QGraphicsPixmapItem
{

    Q_OBJECT

public:

    Shape();

    bool collision();

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void shapeDestroyed();

    void moveDiagonal();

    void moveSinus();

    bool crashed();

    ~Shape();


public slots:

    void move();

    void shapeClicked();

    void clearShape();

signals:

    void clicked();

    void shapeDestroyedSignal(int shapeScore);

    void endGameSignal();

protected:

    int health;

    int x_speed;

    int movement_type;

    int sinus_y_interval;

    double starting_sinus_y;

    int shapeScore;

    int rightX;

private:

    int x_pos;

    int y_pos;

    bool y_direction;

    QTimer * timer;

};
