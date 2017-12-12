#include "geometry_blast.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    srand (time (NULL));
    QApplication a(argc, argv);
    Geometry_Blast w;
    return a.exec();
}
