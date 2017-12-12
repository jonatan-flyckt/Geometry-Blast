#include "circle.h"

Circle::Circle(): Shape()
{
    setPixmap(QPixmap(":/images/circle.png"));
    health = 1;
    shapeScore = 1;
    if (movement_type == 1)
        x_speed = 3;
    if (movement_type == 2)
        x_speed = 2;
    rightX = 58;
}
