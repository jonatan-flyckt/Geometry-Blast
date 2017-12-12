#include "skull.h"

Skull::Skull(): Shape()
{
    setPixmap(QPixmap(":/images/skull.png"));
    health = 20;
    shapeScore = 20;
    x_speed = 1;
    movement_type = 3;
    sinus_y_interval = 220;
    starting_sinus_y = 255;
    rightX = 132;
}
