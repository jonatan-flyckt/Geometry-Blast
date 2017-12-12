#include "geometry_blast.h"

Geometry_Blast::Geometry_Blast()
{
    mainScene = new QGraphicsScene();
    mainScene->setSceneRect(0, 0, 1060, 660);
    menuImage.load(":/images/menu.png");
    mainScene->setBackgroundBrush(QBrush(menuImage));
    view = new QGraphicsView(mainScene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(1060, 660);
    //skapa alla knappar
    newGameButton = new Button (355, 82, "");
    int newGameButtonX = 31;
    int newGameButtonY = 231;
    newGameButton->setPos(newGameButtonX, newGameButtonY);
    connect(newGameButton, SIGNAL(clicked()), this, SLOT(newGame()));
    mainScene->addItem(newGameButton);
    highscoreButton = new Button (355, 82, "");
    int highscoreButtonX = 31;
    int highscoreButtonY = 315;
    highscoreButton->setPos(highscoreButtonX, highscoreButtonY);
    connect(highscoreButton, SIGNAL(clicked()), this, SLOT(getHighscore()));
    mainScene->addItem(highscoreButton);
    instructionsButton = new Button (355, 82, "");
    int instructionsButtonX = 32;
    int instructionsButtonY = 409;
    instructionsButton->setPos(instructionsButtonX, instructionsButtonY);
    connect(instructionsButton, SIGNAL(clicked()), this, SLOT(getInstructions()));
    mainScene->addItem(instructionsButton);
    exitButton = new Button (355, 82, "");
    int exitButtonX = 32;
    int exitButtonY = 503;
    exitButton->setPos(exitButtonX, exitButtonY);
    connect(exitButton, SIGNAL(clicked()), this, SLOT(exit()));
    mainScene->addItem(exitButton);
    readScores();
    view->show();
}

void Geometry_Blast::newGame()
{
    delete newGameButton;
    delete highscoreButton;
    delete instructionsButton;
    delete exitButton;
    mainScene->clear();
    game = new Game(mainScene);
    connect(game, SIGNAL(endGameSignal()), this, SLOT(restoreMenu()));
    game->startGame();
}

void Geometry_Blast::getHighscore()
{
    button_pressed = new QGraphicsPixmapItem();
    button_pressed->setPixmap(QPixmap(":/images/button_pressed_highscore.png"));
    button_pressed->setPos(41, 325);
    mainScene->addItem(button_pressed);
    highscore = new QGraphicsPixmapItem();
    highscore->setPixmap(QPixmap(":/images/highscore.png"));
    highscore->setPos(720, 240);
    mainScene->addItem(highscore);
    highscore_position = new QGraphicsTextItem;
    highscore_position->setDefaultTextColor(QColor(0, 255, 255));
    highscore_position->setFont(QFont("Bauhaus 93"));
    highscore_position->setScale(1.7);
    highscore_position->setPos(735, 320);
    highscore_position->setPlainText("1.\n2.\n3.\n4.\n5.");
    mainScene->addItem(highscore_position);
    QString temp_name;
    for (int i  = 0; i < highScoreVector.size(); i++)
    {
        temp_name.append(highScoreVector.at(i)->getName());
        temp_name.append('\n');
    }
    highscore_player = new QGraphicsTextItem;
    highscore_player->setDefaultTextColor(QColor(0, 255, 255));
    highscore_player->setFont(QFont("Bauhaus 93"));
    highscore_player->setScale(1.7);
    highscore_player->setPos(770, 320);
    highscore_player->setPlainText(temp_name);
    mainScene->addItem(highscore_player);
    QString temp_score;
    for (int i  = 0; i < highScoreVector.size(); i++)
    {
        QString temp_score_string = QString::number(highScoreVector.at(i)->getScore());
        temp_score.append(temp_score_string);
        temp_score.append('\n');
    }
    highscore_score = new QGraphicsTextItem;
    highscore_score->setDefaultTextColor(QColor(0, 255, 255));
    highscore_score->setFont(QFont("Bauhaus 93"));
    highscore_score->setScale(1.7);
    highscore_score->setPos(930, 320);
    highscore_score->setPlainText(temp_score);
    mainScene->addItem(highscore_score);
}

void Geometry_Blast::getInstructions()
{
    button_pressed = new QGraphicsPixmapItem();
    button_pressed->setPixmap(QPixmap(":/images/button_pressed_instructions.png"));
    button_pressed->setPos(44, 417);
    mainScene->addItem(button_pressed);
    instructions = new QGraphicsPixmapItem();
    instructions->setPixmap(QPixmap(":/images/instructions.png"));
    instructions->setPos(720, 240);
    mainScene->addItem(instructions);
}

void Geometry_Blast::exit()
{
    delete newGameButton;
    delete highscoreButton;
    delete instructionsButton;
    delete exitButton;
    view->close();
}

void Geometry_Blast::restoreMenu()
{
    new_score = game->getScore();
    new_player_name = game->getPlayerName();
    delete game;
    Highscore *newHighscore = new Highscore(new_score, new_player_name);
    highScoreVector.push_back(newHighscore);
    sortScores();
    writeScores();
    mainScene->clear();
    mainScene->setBackgroundBrush(QBrush(menuImage));
    newGameButton = new Button (355, 82, "");
    int newGameButtonX = 31;
    int newGameButtonY = 231;
    newGameButton->setPos(newGameButtonX, newGameButtonY);
    connect(newGameButton, SIGNAL(clicked()), this, SLOT(newGame()));
    mainScene->addItem(newGameButton);
    highscoreButton = new Button (355, 82, "");
    int highscoreButtonX = 31;
    int highscoreButtonY = 315;
    highscoreButton->setPos(highscoreButtonX, highscoreButtonY);
    connect(highscoreButton, SIGNAL(clicked()), this, SLOT(getHighscore()));
    mainScene->addItem(highscoreButton);
    instructionsButton = new Button (355, 82, "");
    int instructionsButtonX = 32;
    int instructionsButtonY = 409;
    instructionsButton->setPos(instructionsButtonX, instructionsButtonY);
    connect(instructionsButton, SIGNAL(clicked()), this, SLOT(getInstructions()));
    mainScene->addItem(instructionsButton);
    exitButton = new Button (355, 82, "");
    int exitButtonX = 32;
    int exitButtonY = 503;
    exitButton->setPos(exitButtonX, exitButtonY);
    connect(exitButton, SIGNAL(clicked()), this, SLOT(exit()));
    mainScene->addItem(exitButton);
    getHighscore();
}

void Geometry_Blast::sortScores()
{
    for (int j = highScoreVector.size() - 1; j >= 0; j--) //Sorterar alla highscores
    {
        for (int i = highScoreVector.size() - 1; i >= 0; i--) //Byter plats på 2 highscores
        {
            if ((i != 0) && (highScoreVector.at(i)->getScore() > highScoreVector.at(i - 1)->getScore() ))
            {
                Highscore tempHighscore(0, "");
                tempHighscore.changeScore(highScoreVector.at(i-1)->getScore());
                tempHighscore.changeName(highScoreVector.at(i-1)->getName());
                highScoreVector.at(i-1)->changeScore(highScoreVector.at(i)->getScore());
                highScoreVector.at(i-1)->changeName(highScoreVector.at(i)->getName());
                highScoreVector.at(i)->changeScore(tempHighscore.getScore());
                highScoreVector.at(i)->changeName(tempHighscore.getName());
            }
        }
    }
    if (highScoreVector.size() > 5) //Ta bort det sista om det finns 6 föremål i vektorn
        highScoreVector.pop_back();
}

void Geometry_Blast::readScores()
{
    QString filename ="./highscore.txt";
    QFile highscoreFile(filename);
    if (highscoreFile.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QTextStream stream(&highscoreFile);
        int a;
        for (a = 0; !highscoreFile.atEnd(); a++) //a indikerar antalet rader i filen
        {
            QString garbage = highscoreFile.readLine();
        }
        highscoreFile.close();
        highscoreFile.open(QIODevice::ReadWrite | QIODevice::Text);
        int i = 1; //i indikerar antalet lästa rader
            for (int j = 0; j <= ((a / 2) - 1); j++)
            {
                if (i > 10)
                    break;
//Lägg till spelarnamn om vi läser från ojämn rad
                    Highscore* newHighscore = new Highscore(0, "");
                    highScoreVector.push_back(newHighscore);
                    QString name = highscoreFile.readLine();
                    i++;
                    name = name.left(name.length() - 1); //rensa \n
                    highScoreVector.at(j)->changeName(name);
//Lägg till score om vi läser från jämn rad
                    QString scorestring = highscoreFile.readLine();
                    i++;
                    scorestring = scorestring.left(scorestring.length() - 1); //rensa \n
                    int the_score = scorestring.toInt();
                    highScoreVector.at(j)->changeScore(the_score);
            }
    }
    highscoreFile.close();
}

void Geometry_Blast::writeScores()
{
    QString filename ="./highscore.txt";
    QFile highscoreFile(filename);
    if (highscoreFile.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        for (int i = 0; i < highScoreVector.size(); i++)
        {
            QTextStream stream(&highscoreFile);
            stream << highScoreVector.at(i)->getName() << endl << highScoreVector.at(i)->getScore() << endl;
        }
    }
    highscoreFile.close();
}
