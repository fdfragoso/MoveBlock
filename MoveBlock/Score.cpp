#include "Score.h"

Score::Score()
{
   pontos = 0;
}

Score::~Score()
{
}

int Score::getScore(void) 
{
   return this->pontos;
}
      
void Score::sumScore(int soma) 
{
   this->pontos += soma;
}