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
	float distance;
	bool wasHitVertical;

	bool isRayFacingDown;
	bool isRayFacingUp;

	bool isRayFacingRight;
	bool isRayFacingLeft;

	bool fieldOfView;

	Ray(float _rayAngle)
	{
		this->rayAngle = normalizeAngle(_rayAngle);
		this->wallHitX = 0;
		this->wallHitY = 0;
		this->distance = 0;
		this->wasHitVertical = false;

		this->isRayFacingDown = this->rayAngle > 0 && this->rayAngle < PI;
		this->isRayFacingUp = !isRayFacingDown;

		this->isRayFacingRight = this->rayAngle < 0.5f * PI || this->rayAngle > 1.5 * PI;
		this->isRayFacingLeft = !isRayFacingRight;

		this->fieldOfView = false;
	}

	void cast(unsigned int columnId, Player* player, World* world, Game* game)
	{
		float xintercept, yintercept; // start tile
		float xstep, ystep;


		// horizontal ---------------------------------------------------------------------------------
		bool foundHorzWallHit = false;
		float horzWallHitX = 0;
		float horzWallHitY = 0;

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

		while (nextHorzTouchX >= 0 && nextHorzTouchX <= game->WINDOW_WIDTH / 2
			&& nextHorzTouchY >= 0 && nextHorzTouchY <= game->WINDOW_HEIGHT)
		{
			if (world->hasWallAt(nextHorzTouchX, nextHorzTouchY - (this->isRayFacingUp ? 1 : 0)))
			{
				foundHorzWallHit = true;
				horzWallHitX = nextHorzTouchX;
				horzWallHitY = nextHorzTouchY;
				break;
			}
			else
			{
				nextHorzTouchX += xstep;
				nextHorzTouchY += ystep;
			}
		}

		// vertical ---------------------------------------------------------------------------------
		bool foundVertWallHit = false;
		float vertWallHitX = 0;
		float vertWallHitY = 0;

		xintercept = floor(player->position.x / world->TILE_SIZE) * world->TILE_SIZE;
		xintercept += this->isRayFacingRight ? world->TILE_SIZE : 0;

		yintercept = player->position.y + (xintercept - player->position.x) * tan(this->rayAngle);

		xstep = world->TILE_SIZE;
		xstep *= this->isRayFacingLeft ? -1 : 1;

		ystep = world->TILE_SIZE * tan(this->rayAngle);
		ystep *= (this->isRayFacingUp && ystep > 0) ? -1 : 1;
		ystep *= (this->isRayFacingDown && ystep < 0) ? -1 : 1;

		float nextVertTouchX = xintercept;
		float nextVertTouchY = yintercept;

		while (nextVertTouchX >= 0 && nextVertTouchX <= game->WINDOW_WIDTH / 2
			&& nextVertTouchY >= 0 && nextVertTouchY <= game->WINDOW_HEIGHT)
		{
			if (world->hasWallAt(nextVertTouchX - (this->isRayFacingLeft ? 1 : 0), nextVertTouchY))
			{
				foundVertWallHit = true;
				vertWallHitX = nextVertTouchX;
				vertWallHitY = nextVertTouchY;
				break;
			}
			else
			{
				nextVertTouchX += xstep;
				nextVertTouchY += ystep;
			}
		}

		float horzHitDistance = (foundHorzWallHit)
			? distanceBetweenPoints(player->position.x, player->position.y, horzWallHitX, horzWallHitY)
			: INT_MAX;

		float vertHitDistance = (foundVertWallHit)
			? distanceBetweenPoints(player->position.x, player->position.y, vertWallHitX, vertWallHitY)
			: INT_MAX;

		// smallest
		this->wallHitX = (horzHitDistance < vertHitDistance) ? horzWallHitX : vertWallHitX;
		this->wallHitY = (horzHitDistance < vertHitDistance) ? horzWallHitY : vertWallHitY;
		this->distance = (horzHitDistance < vertHitDistance) ? horzHitDistance : vertHitDistance;
		this->wasHitVertical = (vertHitDistance < horzHitDistance);
		//this->finalHitX = horzWallHitX;
		//this->finalHitY = horzWallHitY;
	}
};
