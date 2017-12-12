#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QBrush>
#include <QImage>
#include <QTimer>
#include <vector>
#include <QMouseEvent>
#include "circle.h"
#include "square.h"
#include "triangle.h"
#include "skull.h"
#include <iostream>
#include <string>
#include <button.h>
#include <QLineEdit>
#include <QInputDialog>
#include <QDir>

class Game : public QGraphicsScene
{

    Q_OBJECT

public:

    Game(QGraphicsScene * scene);

    void startGame();

    void runGame();

    void createSkull();

    int getScore();

    QString getPlayerName();

    ~Game();


public slots:

    void createCircle();

    void createSquare();

    void createTriangle();

    void addScore(int addingScore);

    void levelUp();

    void endGame();

    void continueButton();

    void nameClicked();

signals:

    void clearShapes();

    void endGameSignal();

private:

    int current_score;

    QString player_name;

    int level;

    int circle_frequency;

    int square_frequency;

    int triangle_frequency;

    QTimer * circle_timer;

    QTimer * square_timer;

    QTimer * triangle_timer;

    QTimer * game_timer;

    int x_click;

    int y_click;

    QGraphicsScene * gameScene;

    QGraphicsTextItem * level_text;

    QGraphicsTextItem * score_text;

    QGraphicsTextItem * timer_text;

    QGraphicsTextItem * timer_text_minute;

    QGraphicsTextItem * final_score;

    QGraphicsTextItem * name_box;

    QGraphicsPixmapItem * game_over;

    QGraphicsPixmapItem * enter_name;

    QImage playfield;

    QImage playfieldFrame;

    std::vector<Shape*> shapeVector;

    int time;

    int minute;

    QString timestringM;

    QString timestring;

    Button * _continue;

    Button * nameButton;

};

