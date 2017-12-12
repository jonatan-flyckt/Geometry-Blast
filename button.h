#pragma once

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsTextItem>
#include <QBrush>
#include <QColor>
#include <QPixmap>

class Button : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:

    Button(int width, int height, QString buttonText, QGraphicsItem * parent = NULL);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);

    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    ~Button();

signals:

    void clicked();

private:

    QGraphicsTextItem *text;

};
