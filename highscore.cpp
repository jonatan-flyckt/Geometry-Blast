#include "highscore.h"

Highscore::Highscore(int _score, QString _name)
{
    name = _name;
    score = _score;
}

int Highscore::getScore()
{
    return score;
}

QString Highscore::getName()
{
    return name;
}

void Highscore::changeScore(int new_score)
{
    score = new_score;
}

void Highscore::changeName(QString new_name)
{
    name = new_name;
}

