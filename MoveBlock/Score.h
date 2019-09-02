#pragma once

class Score
{
private:
    int pontos;
public:
    Score();
    ~Score();
    int getScore();
    void sumScore(int soma);
};