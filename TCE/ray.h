#pragma once
#include "global_functions.h"
#include "world.h"
#include "player.h"

class Ray
{
public:

	float rayAngle;
	float wallHitX;
	float wallHitY;
	float distance = 0;
	bool isRayFacingDown;
	bool isRayFacingUp;

	bool isRayFacingRight;
	bool isRayFacingLeft;

	Ray(float _rayAngle)
	{
		this->rayAngle = normalizeAngle(_rayAngle);
		this->wallHitX = 0;
		this->wallHitY = 0;
		this->distance = 0;

		this->isRayFacingDown = this->rayAngle > 0 && this->rayAngle < PI;
		this->isRayFacingUp = !isRayFacingDown;

		this->isRayFacingRight = this->rayAngle < 0.5f * PI || this->rayAngle > 1.5 * PI;
		this->isRayFacingLeft = !isRayFacingRight;

	}
	
	void cast(unsigned int columnId, Player* player, World * world)
	{
		float xintercept, yintercept; // start tile
		float xstep, ystep;

		yintercept = floor(player->position.y / world->TILE_SIZE) * world->TILE_SIZE;
		yintercept += this->isRayFacingDown ? world->TILE_SIZE : 0;

		xintercept = player->position.x + (yintercept - player->position.y) / tan(this->rayAngle);

		ystep = world->TILE_SIZE;
		ystep *= this->isRayFacingUp ? -1 : 1;

		xstep = world->TILE_SIZE / tan(this->rayAngle);
		xstep *= (this->isRayFacingLeft && xstep > 0) ? -1 : 1;
		xstep *= (this->isRayFacingRight && xstep < 0) ? -1 : 1;
		
		float nextHorzTouchX = xintercept;
		float nextHorzTouchY = yintercept;

		if (this->isRayFacingUp)
			nextHorzTouchY--;

		while (true)
		{
			//if(world->hasWallAt(nextHorzTouchX, nextHorzTouchY)
			break;
		}
	}
};
