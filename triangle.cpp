#include "triangle.h"

Triangle::Triangle(): Shape()
{
    setPixmap(QPixmap(":/images/triangle.png"));
    health = 3;
    shapeScore = 3;
    if (movement_type == 1)
        x_speed = 7;
    if (movement_type == 2)
        x_speed = 5;
    rightX = 53;
}
