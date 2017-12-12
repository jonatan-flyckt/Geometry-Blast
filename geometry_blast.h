#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QBrush>
#include <QImage>
#include <QMouseEvent>
#include "game.h"
#include "button.h"
#include "shape.h"
#include "highscore.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QGraphicsTextItem>

class Geometry_Blast : public QGraphicsScene
{

    Q_OBJECT

public:

    Geometry_Blast();

    void sortScores(); //Uppdaterar scores i highScoreVector

    void readScores(); //Läser från highscorefilen

    void writeScores(); //Skriver om highscorefilen

public slots:

    void newGame();

    void getHighscore();

    void getInstructions();

    void exit();

    void restoreMenu();

private:

    QGraphicsScene * mainScene;

    QGraphicsView * view;

    QImage menuImage;

    std::vector<Highscore*> highScoreVector;

    Game * game;

    Button * newGameButton;

    Button * highscoreButton;

    Button * instructionsButton;

    Button * exitButton;

    QGraphicsPixmapItem * highscore;

    QGraphicsPixmapItem * instructions;

    QGraphicsPixmapItem * button_pressed;

    int new_score;

    QString new_player_name;

    QGraphicsTextItem * highscore_player;

    QGraphicsTextItem * highscore_position;

    QGraphicsTextItem * highscore_score;

    bool highscore_pressed;

    bool instructions_pressed;

};
