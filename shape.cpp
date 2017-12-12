#include "shape.h"

Shape::Shape()
{
    connect(this, SIGNAL(clicked()), this, SLOT(shapeClicked()));
    y_pos = (rand() % 535) + 30;
    x_pos = -100;
    movement_type = rand() % 3 + 1;
        if (movement_type == 2)
            y_direction = rand() % 2;
        if (movement_type == 3)
        {
            sinus_y_interval = rand() % 100 + 50;
            if (y_pos < (100 + sinus_y_interval / 2))
                y_pos = y_pos + sinus_y_interval;
            if (y_pos > (500 - sinus_y_interval / 2))
                y_pos = y_pos - sinus_y_interval;
            x_speed = 3;
            starting_sinus_y = y_pos;
        }
    setPos(x_pos, y_pos);
    timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(25);
}

void Shape::move()
{
    if (movement_type == 1)
        x_pos += x_speed;
    if (movement_type == 2)
        moveDiagonal();
    if (movement_type == 3)
        moveSinus();
    setPos(x_pos, y_pos);
    if (crashed())
        emit endGameSignal();
}

void Shape::moveDiagonal()
{
    if (y_direction)
        y_pos += x_speed;
    else
        y_pos -= x_speed;
    x_pos += x_speed;
    if (collision())
        y_direction = !y_direction;
}

void Shape::moveSinus()
{
    x_pos += x_speed;
    y_pos = starting_sinus_y - sinus_y_interval * sin(((x_pos % 200) / 200.00) * 2 * PI);
}

bool Shape::crashed()
{
    if (x_pos + rightX > 820)
        return true;
    else
        return false;
}

bool Shape::collision()
{
    if ((y_pos < 30) || (y_pos > 565))
        return true;
    else
        return false;
}

void Shape::shapeClicked()
{
    health -= 1;
    if (health == 0)
        this->shapeDestroyed();
}

void Shape::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked();
}

void Shape::shapeDestroyed()
{
    emit shapeDestroyedSignal(shapeScore);
    delete this;
}

void Shape::clearShape()
{
    delete this;
}

Shape::~Shape()
{
    delete timer;
}

