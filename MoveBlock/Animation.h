#pragma once

#include "SDL.h"
#include "Collision.h"
#include "Scene.h"
#include "Sprite.h"
#include <list>
#include <ctime>

using namespace std;

class Animation 
{
private:
   Sprite *pPlayer;
   list<Sprite> *pBlock;
   Scene *pScene;
   int vx, vy, contLinha;
   bool pMove, blocosCaindo, gameOver, lineDelete;
public:
   Animation(Sprite *objPlayer, list<Sprite> *lstBlock, Scene *objScene);
   ~Animation();
   void Initialize();
   void UpdatePlayer();
   void UpdateBlock();
   void MoveBlock(Sprite *bloco);
   void TestCollisionPlayer(Sprite *bloco);
   void DeleteLine();
   bool VerificaCaindo();
   inline bool isGameOver() { return gameOver; }
   void Jump();
};