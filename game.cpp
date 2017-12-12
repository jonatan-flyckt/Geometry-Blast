#include "game.h"

Game::Game(QGraphicsScene * scene)
{
    gameScene = scene;
    playfield.load(":/images/playfield.png");
    gameScene->setBackgroundBrush(QBrush(playfield));
    playfieldFrame.load(":/images/playfield_frame.png");
    gameScene->setForegroundBrush(QBrush(playfieldFrame));
    current_score = 0;
    level = 1;
    circle_frequency = 3000;
    square_frequency = 5000;
    triangle_frequency = 7000;
    level_text = new QGraphicsTextItem;
    level_text->setDefaultTextColor(QColor(0, 255, 255));
    level_text->setFont(QFont("Bauhaus 93"));
    level_text->setScale(4);
    level_text->setPos(975, 145);
    score_text = new QGraphicsTextItem;
    score_text->setDefaultTextColor(QColor(0, 255, 255));
    score_text->setFont(QFont("Bauhaus 93"));
    score_text->setScale(4);
    score_text->setPos(975, 288);
    timer_text = new QGraphicsTextItem;
    timer_text->setDefaultTextColor(QColor(0, 255, 255));
    timer_text->setFont(QFont("Bauhaus 93"));
    timer_text->setScale(4);
    timer_text->setPos(975, 513);
    timer_text_minute = new QGraphicsTextItem;
    timer_text_minute->setDefaultTextColor(QColor(0, 255, 255));
    timer_text_minute->setFont(QFont("Bauhaus 93"));
    timer_text_minute->setScale(2.2);
    timer_text_minute->setPos(965, 545);
    final_score = new QGraphicsTextItem;
    final_score->setDefaultTextColor(QColor(35, 35, 35));
    final_score->setFont(QFont("Bauhaus 93"));
    final_score->setScale(9);
    final_score->setPos(475, 290);
    final_score->setZValue(1);
    game_over = new QGraphicsPixmapItem;
    game_over->setPixmap(QPixmap(":/images/game_over.png"));
    game_over->setPos(0, 0);
}

void Game::startGame()
{
    enter_name = new QGraphicsPixmapItem;
    enter_name->setPixmap(QPixmap(":/images/enter_name.png"));
    enter_name->setPos(163, 112);
    gameScene->addItem(enter_name);
    nameButton = new Button(355, 82, "");
    nameButton->setPos(350, 413);
    connect(nameButton, SIGNAL(clicked()), this, SLOT(nameClicked()));
    gameScene->addItem(nameButton);
    name_box = new QGraphicsTextItem;
    name_box->setPos(340, 315);
    name_box->setScale(2);
    name_box->setDefaultTextColor(QColor(0, 255, 255));
    name_box->setFont(QFont("Bauhaus 93"));
    name_box->setTextInteractionFlags(Qt::TextEditorInteraction);
    name_box->setTextWidth(190);
    gameScene->addItem(name_box);
}

void Game::endGame()
{
    circle_timer->stop();
    square_timer->stop();
    triangle_timer->stop();
    game_timer->stop();
    emit clearShapes();
    gameScene->setForegroundBrush(Qt::NoBrush);
    gameScene->addItem(game_over);
    QString stringscore = QString::number(current_score);
    final_score->setPlainText(stringscore);
    if (current_score > 9 && current_score < 100)
        final_score->setPos(440, 290);
    else if (current_score > 99)
        final_score->setPos(405, 290);
    gameScene->addItem(final_score);
    _continue = new Button(355, 82, "");
    _continue->setPos(372, 513);
    connect(_continue, SIGNAL(clicked()), this, SLOT(continueButton()));
    gameScene->addItem(_continue);
}

void Game::runGame()
{
    QString stringlvl = QString::number(level);
    level_text->setPlainText(stringlvl);
    gameScene->addItem(level_text);
    QString stringscore = QString::number(current_score);
    score_text->setPlainText(stringscore);
    gameScene->addItem(score_text);
    circle_timer = new QTimer();
    QObject::connect(circle_timer, SIGNAL(timeout()), this, SLOT(createCircle()));
    circle_timer->start(circle_frequency);
    square_timer = new QTimer();
    QObject::connect(square_timer, SIGNAL(timeout()), this, SLOT(createSquare()));
    triangle_timer = new QTimer();
    QObject::connect(triangle_timer, SIGNAL(timeout()), this, SLOT(createTriangle()));
    game_timer = new QTimer();
    QObject::connect(game_timer, SIGNAL(timeout()), this, SLOT(levelUp()));
    game_timer->start(10000);
}

void Game::addScore(int addingScore)
{
    current_score += addingScore;
    if (current_score > 9 && current_score < 13)
    {
        score_text->setPos(960, 290);
        score_text->setScale(3.8);
    }
    if (current_score > 99 && current_score < 125)
    {
        score_text->setScale(2.6);
        score_text->setPos(963, 305);
    }
    QString string = QString::number(current_score);
    score_text->setPlainText(string);
    gameScene->removeItem(score_text);
    gameScene->addItem(score_text);
}

void Game::createCircle()
{
    Shape* newShape = new Circle();
    connect(newShape, SIGNAL(shapeDestroyedSignal(int)), this, SLOT(addScore(int)));
    connect(newShape, SIGNAL(endGameSignal()), this, SLOT(endGame()));
    connect(this, SIGNAL(clearShapes()), newShape, SLOT(clearShape()));
    shapeVector.push_back(newShape);
    gameScene->addItem(newShape);
}

void Game::createSquare()
{
    Shape* newShape = new Square();
    connect(newShape, SIGNAL(shapeDestroyedSignal(int)), this, SLOT(addScore(int)));
    connect(newShape, SIGNAL(endGameSignal()), this, SLOT(endGame()));
    connect(this, SIGNAL(clearShapes()), newShape, SLOT(clearShape()));
    shapeVector.push_back(newShape);
    gameScene->addItem(newShape);
}

void Game::createTriangle()
{
    Shape* newShape = new Triangle();
    connect(newShape, SIGNAL(shapeDestroyedSignal(int)), this, SLOT(addScore(int)));
    connect(newShape, SIGNAL(endGameSignal()), this, SLOT(endGame()));
    connect(this, SIGNAL(clearShapes()), newShape, SLOT(clearShape()));
    shapeVector.push_back(newShape);
    gameScene->addItem(newShape);
}

void Game::createSkull()
{
    Shape* newShape = new Skull();
    connect(newShape, SIGNAL(shapeDestroyedSignal(int)), this, SLOT(addScore(int)));
    connect(newShape, SIGNAL(endGameSignal()), this, SLOT(endGame()));
    connect(this, SIGNAL(clearShapes()), newShape, SLOT(clearShape()));
    shapeVector.push_back(newShape);
    gameScene->addItem(newShape);
}

void Game::levelUp()
{
    level += 1;
    if (level % 2 == 0)
    {
        circle_frequency *= 0.9;
        circle_timer->stop();
        circle_timer->start(circle_frequency);
    }
    if ((level % 3 == 0) && (level != 3))
    {
        square_frequency *= 0.8;
        square_timer->stop();
        square_timer->start(square_frequency);
    }
    if (level == 3)
        square_timer->start(square_frequency);
    if ((level % 4 == 0) && (level != 4))
    {
        triangle_frequency *= 0.8;
        triangle_timer->stop();
        triangle_timer->start(triangle_frequency);
    }
    if (level == 5)
        triangle_timer->start(triangle_frequency);
    if (level % 8 == 0)
        createSkull();
    if (level == 10)
        level_text->setPos(955, 150);
    QString string = QString::number(level);
    level_text->setPlainText(string);
    gameScene->removeItem(level_text);
    gameScene->addItem(level_text);
}

void Game::continueButton()
{
    emit endGameSignal();
}

void Game::nameClicked()
{
    player_name = name_box->toPlainText();
    gameScene->removeItem(name_box);
    delete nameButton;
    delete enter_name;
    delete name_box;
    gameScene->removeItem(enter_name);
    runGame();
}

int Game::getScore()
{
    return current_score;
}

QString Game::getPlayerName()
{
    return player_name;
}

Game::~Game()
{
    delete circle_timer;
    delete square_timer;
    delete triangle_timer;
    delete game_timer;
}
