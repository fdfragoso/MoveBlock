#include "Scene.h"

Scene::Scene()
{
   screen = new SDL_Surface();
   background = new SDL_Surface();
}

Scene::~Scene()
{
	SDL_FreeSurface(background);
	SDL_FreeSurface(screen);
	SDL_Quit();
}

void Scene::Initialize(int pWidth, int pHeight)
{
   width = pWidth;
   height = pHeight;

	if (SDL_Init(SDL_INIT_VIDEO) == -1)
		exit(0);

	screen = SDL_SetVideoMode(pWidth, pHeight, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);

	if (screen == NULL) {
		SDL_Quit();
		exit(0);
	}
}

void Scene::SceneImage(char* image)
{
   background = SDL_LoadBMP(image);
}

void Scene::Draw()
{
   SDL_FillRect(screen, NULL, 0);
   SDL_BlitSurface(background, NULL, screen, NULL);
}

void Scene::Update()
{
   SDL_Flip(screen);
}

Uint32 Scene::Wait(Uint32 t0) 
{
	Uint32 t1 = SDL_GetTicks();

	if ((t1 - t0) < 75)
		SDL_Delay(75 - (t1 - t0));

	return t1;
}
