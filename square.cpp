#include "square.h"

Square::Square(): Shape()
{
    setPixmap(QPixmap(":/images/square.png"));
    health = 2;
    shapeScore = 2;
    if (movement_type == 1)
        x_speed = 5;
    if (movement_type == 2)
        x_speed = 4;
    rightX = 58;
}
