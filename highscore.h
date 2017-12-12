#pragma once
#include <QString>

class Highscore
{
public:

    Highscore(int _score, QString _name);

    int getScore();

    QString getName();

    void changeScore(int new_score);

    void changeName(QString new_name);

private:

    QString name;

    int score;
};
