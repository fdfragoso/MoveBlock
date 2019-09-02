#include "Sprite.h"

Sprite::Sprite()
{
   image = NULL;
   vx = 0;
   vy = 0;
   jump = false;  
   move = true;
   caindo = true;
   colidiu = false;
}

Sprite::~Sprite()
{
   if (image != NULL)
   {
      SDL_FreeSurface(image);
      image = NULL;
   }
}

void Sprite::Initialize(char* pImage)
{
   SDL_Surface* temp = SDL_LoadBMP(pImage);
   SDL_SetColorKey(temp, SDL_SRCCOLORKEY, SDL_MapRGB(temp->format, 255, 0, 255));
   image = SDL_DisplayFormat(temp);
   SDL_FreeSurface(temp);

   src.x = 0;
   src.y = 0;
   src.w = image->w;
   src.h = image->h;

   dest.x = 0;
   dest.y = 0;
   dest.w = image->w;
   dest.h = image->h; 
}

void Sprite::Initialize(char* pImage, SDL_Surface *pScreen)
{
   SDL_Surface* temp = SDL_LoadBMP(pImage);
   SDL_SetColorKey(temp, SDL_SRCCOLORKEY, SDL_MapRGB(temp->format, 255, 0, 255));
   image = SDL_DisplayFormat(temp);
   SDL_FreeSurface(temp);

   src.x = 0;
   src.y = 0;
   src.w = image->w;
   src.h = image->h;

   dest.x = (pScreen->w / 2) - image->w;
   dest.y = pScreen->h - image->h;
   dest.w = image->w;
   dest.h = image->h; 
}

