#include "SDL.h"
#include "Scene.h"
#include "Sprite.h"
#include "Animation.h"
#include <list>

using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;

int main(int argc, char *argv[]) 
{
	// Cria Scene e Inicializa a SDL
   Scene *objScene = new Scene();   
   objScene->Initialize(WIDTH, HEIGHT);
   objScene->SceneImage("img_start.bmp");

   // Cria Sprites
   Sprite *objPlayer = new Sprite();
   objPlayer->Initialize("img_player.bmp", objScene->getScreen());
   objPlayer->setMove(false);

   list<Sprite> *lstBlock = new list<Sprite>();
   
   // Cria Animation]
   Animation *objAnimation = new Animation(objPlayer, lstBlock, objScene);
   objAnimation->Initialize();

   // Variáveis de apoio
   bool quitGame = false, pauseGame = false, startGame = false, finishGame = false;
   Uint32 t0 = SDL_GetTicks();

   // Intro
   while ((!quitGame) && (!startGame))
   {
      // Ler entradas
      SDL_Event event;
      while( SDL_PollEvent( &event ) ) 
      {
         if (event.type == SDL_KEYDOWN) 
         {
            switch(event.key.keysym.sym) 
            {
               case SDLK_ESCAPE:
                  quitGame = true;
                  break;
               case SDLK_RETURN:
                  startGame = true;
                  break;
            }
         }
      }

      // Desenha a Tela
      objScene->Draw();

	   // Atualiza a Tela
	   objScene->Update();
   }

   // Altera o fundo para o jogo
   objScene->SceneImage("img_background.bmp");

   // Main Loop
   while ((!quitGame) && (!finishGame))
   {
      // Ler entradas
      SDL_Event event;
      while( SDL_PollEvent( &event ) ) 
      {
         if (event.type == SDL_KEYDOWN) 
         {
            switch(event.key.keysym.sym) 
            {
               case SDLK_ESCAPE:
                  quitGame = true;
                  break;
               case SDLK_p:
                  //PauseGame();
                  break;
               case SDLK_UP:
                  objPlayer->startMovingUp();
                  objPlayer->setJump(true);
                  objPlayer->setMove(true);
                  break;
               case SDLK_DOWN:
                  objPlayer->startMovingDown();
                  break;
               case SDLK_LEFT:
                  objPlayer->startMovingLeft();
                  break;
               case SDLK_RIGHT:
                  objPlayer->startMovingRight();
                  break; 
            }
         }
         else if (event.type == SDL_KEYUP) 
         {
            switch(event.key.keysym.sym) 
            {
               case SDLK_ESCAPE:
                  quitGame = true;
                  break;
               case SDLK_p:
                  //PauseGame();
                  break;
               case SDLK_UP:
                  objPlayer->stopMovingUp();
				  objPlayer->startMovingDown();
				  objAnimation->Jump();
                  break;
               case SDLK_DOWN:
                  objPlayer->stopMovingDown();
                  break;
               case SDLK_LEFT:
                  objPlayer->stopMovingLeft();
                  break;
               case SDLK_RIGHT:
                  objPlayer->stopMovingRight();
                  break; 
            }
         }
      }
   
      // Desenha a Tela
      objScene->Draw();

      // Atualiza o Personagem
      objAnimation->UpdatePlayer();

      // Atualiza o Bloco
      objAnimation->UpdateBlock();

	  // Atualiza a Tela
	  objScene->Update();

      // Game Over?
      if (objAnimation->isGameOver())
          finishGame = true;

      // Main Loop Fixed Rate
      t0 = objScene->Wait(t0);
   }

   // Altera o fundo para o jogo
   objScene->SceneImage("img_gameover.bmp");

   // Intro
   while (!quitGame)
   {
      // Ler entradas
      SDL_Event event;
      while( SDL_PollEvent( &event ) ) 
      {
         if (event.type == SDL_KEYDOWN) 
         {
            switch(event.key.keysym.sym) 
            {
               case SDLK_ESCAPE:
                  quitGame = true;
                  break;
            }
         }
      }

      // Desenha a Tela
      objScene->Draw();

	   // Atualiza a Tela
	   objScene->Update();
   }

   // FreeSurface
   objScene->~Scene();   
   objPlayer->~Sprite();
   objAnimation->~Animation();
   list<Sprite>::iterator it = lstBlock->begin();
   for (it = lstBlock->begin(); it != lstBlock->end(); it++) 
      (*it).~Sprite();

   // Finaliza a SDL
   SDL_Quit();
      
   // Sai do programa
   exit(0);
}