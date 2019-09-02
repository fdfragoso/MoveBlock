#include "Collision.h"

bool isCollision(const SDL_Rect& r1, const SDL_Rect& r2)
{
	bool collision = true;

	if (r1.x <= r2.x)
		collision &= r2.x <= (r1.x + r1.w);
	else
		collision &= r1.x <= (r2.x + r2.w);
	if (r1.y <= r2.y)
		collision &= r2.y <= (r1.y + r1.h);
	else
		collision &= r1.y <= (r2.y + r2.h);

	return collision;
}

bool isHorizontalCollision(const SDL_Rect& r1, const SDL_Rect& r2)
{
	bool collision = true;

	if (r1.x <= r2.x)
		collision &= r2.x <= (r1.x + r1.w);
	else
		collision &= r1.x <= (r2.x + r2.w);

	return collision;
}

bool isVerticalCollision(const SDL_Rect& r1, const SDL_Rect& r2)
{
	bool collision = true;

	if (r1.y <= r2.y)
		collision &= r2.y <= (r1.y + r1.h);
	else
		collision &= r1.y <= (r2.y + r2.h);

	return collision;
}

bool isRightCollision(const SDL_Rect& r1, const SDL_Rect& r2)
{
	bool collision = true;

	if (r1.x <= r2.x)
		collision &= r2.x < (r1.x + r1.w);

	return collision;
}

bool isLeftCollision(const SDL_Rect& r1, const SDL_Rect& r2)
{
	bool collision = true;

	if (r1.x >= r2.x)
		collision &= r1.x < (r2.x + r2.w);

	return collision;
}

bool isUpCollision(const SDL_Rect& r1, const SDL_Rect& r2)
{
	bool collision = true;

	if (r1.y >= r2.y)
		collision &= r2.y > (r1.y + r1.h);

	return collision;
}

bool isDownCollision(const SDL_Rect& r1, const SDL_Rect& r2) //r1 - player, r2 - bloco
{
	bool collision = true;

	if (r2.y <= r1.y)
		collision &= r2.y <= (r2.y + r2.h);

	return collision;
}