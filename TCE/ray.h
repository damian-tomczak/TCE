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
	
	unsigned int hitWallColor;

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
		this->hitWallColor = 0;
	}

	void cast(unsigned int columnId, Player* player, World* world, Game* game)
	{
		float xintercept, yintercept; // start tile
		float xstep, ystep;


		// horizontal ---------------------------------------------------------------------------------
		bool foundHorzWallHit = false;
		float horzWallHitX = 0;
		float horzWallHitY = 0;
		int horzWallColor = 0;

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
			int wallGridContent = world->getWallContentAt(nextHorzTouchX, nextHorzTouchY + (this->isRayFacingUp ? -1 : 0));

			if (wallGridContent != 1) {
				foundHorzWallHit = true;
				horzWallHitX = nextHorzTouchX;
				horzWallHitY = nextHorzTouchY;
				horzWallColor = wallGridContent;
				break;
			}
			else {
				nextHorzTouchX += xstep;
				nextHorzTouchY += ystep;
			}
		}

		// vertical ---------------------------------------------------------------------------------
		bool foundVertWallHit = false;
		float vertWallHitX = 0;
		float vertWallHitY = 0;
		int vertWallColor = 0;

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
			int wallGridContent = world->getWallContentAt(nextVertTouchX + (this->isRayFacingLeft ? -1 : 0), nextVertTouchY);

			if (wallGridContent != 1)
			{
				foundVertWallHit = true;
				vertWallHitX = nextVertTouchX;
				vertWallHitY = nextVertTouchY;
				vertWallColor = wallGridContent;
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
		if (vertHitDistance < horzHitDistance)
		{
			this->wallHitX = vertWallHitX;
			this->wallHitY = vertWallHitY;
			this->distance = vertHitDistance;
			this->hitWallColor = vertWallColor;
			this->wasHitVertical = true;
		}
		else
		{
			this->wallHitX = horzWallHitX;
			this->wallHitY = horzWallHitY;
			this->distance = horzHitDistance;
			this->hitWallColor = horzWallColor;
			this->wasHitVertical = false;
		}
	}
};
