#pragma once

#include "SDL.h"

class Sprite 
{
private:
   SDL_Surface* image;
   SDL_Rect src, dest;
   int vx, vy;
   bool jump, move, caindo, colidiu;
public:
   Sprite();
   ~Sprite();
   void Sprite::Initialize(char* pImage);
   void Initialize(char* pImage, SDL_Surface *pScreen);
   inline void startMovingLeft() { vx = -16; }
   inline void stopMovingLeft() { vx = 0; }
   inline void startMovingRight() { vx = 16; } 
   inline void stopMovingRight() { vx = 0; }
   inline void startMovingUp() { vy = -16; } //16
   inline void stopMovingUp() { vy = 0; }
   inline void startMovingDown() { vy = 16; } //16
   inline void stopMovingDown() { vy = 0; }
   inline SDL_Rect getSrc() { return src; }
   inline void setSrc(SDL_Rect pSrc) { src = pSrc; }
   inline SDL_Rect getDest() { return dest; }
   inline void setDest(SDL_Rect pDest) { dest = pDest; }
   inline int getVX() { return vx; }
   inline void setVY(int pVY) { vy = pVY; };
   inline int getVY() { return vy; }
   inline void setVX(int pVX) { vx = pVX; };
   inline bool getJump() { return jump; }
   inline void setJump(bool pJump) { jump = pJump; }
   inline bool getMove() { return move; }
   inline void setMove(bool pMove) { move = pMove; }
   inline bool getCaindo() { return caindo; }
   inline void setCaindo(bool pCaindo) { caindo = pCaindo; }
   inline void setColidiu(bool pColidiu) { colidiu = pColidiu; }
   inline bool getColidiu() { return colidiu; }
   inline SDL_Surface *getImage() { return image; }
};

