#pragma once

#include "SDL.h"

bool isCollision(const SDL_Rect& r1, const SDL_Rect& r2);
bool isHorizontalCollision(const SDL_Rect& r1, const SDL_Rect& r2);
bool isVerticalCollision(const SDL_Rect& r1, const SDL_Rect& r2);
bool isRightCollision(const SDL_Rect& r1, const SDL_Rect& r2);
bool isLeftCollision(const SDL_Rect& r1, const SDL_Rect& r2);
bool isUpCollision(const SDL_Rect& r1, const SDL_Rect& r2);
bool isDownCollision(const SDL_Rect& r1, const SDL_Rect& r2);

