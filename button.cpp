#include "button.h"

Button::Button(int width, int height, QString buttonText, QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    setRect(0, 0, width, height);
    text = new QGraphicsTextItem(buttonText, this);
    int xTextPos = rect().width()/2 - text->boundingRect().width() / 2;
    int yTextPos = rect().height()/2 - text->boundingRect().height() / 2;
    text->setPos(xTextPos, yTextPos);
    setAcceptHoverEvents(true);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QBrush brush;
    QPixmap mouseover(":/images/button_mouseover.png");
    brush.setTexture(QPixmap(mouseover));
    setBrush(mouseover);
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(0, 0, 0, 0));
    setBrush(brush);
}

Button::~Button()
{
    delete text;
}
