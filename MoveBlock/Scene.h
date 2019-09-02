#pragma once

#include "SDL.h"

class Scene 
{
private:
   SDL_Surface *screen;
   SDL_Surface *background;
   int width, height;
public:
   Scene();
   ~Scene(); 
   void Initialize(int pWidth, int pHeight);
   void Draw();
   void Update();
   Uint32 Wait(Uint32 t0);
   inline SDL_Surface *getScreen() { return screen; }
   inline SDL_Surface *getBackground() { return background; }
   inline int getWidth() { return width; }
   inline int getHeight() { return height; }
   void SceneImage(char* image);
};