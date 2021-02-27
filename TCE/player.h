#pragma once
#include <glm/glm.hpp>

class Player
{
public:
	glm::vec2 position;
	float angle;
	glm::vec2 newPos;
	float fov;
	float speed = 5.f;

	Player(glm::vec2 _position, float _angle, float _fov)
	{
		this->position = _position;
		this->angle = _angle;
		this->newPos = glm::vec2(0, 0);
		this->fov = _fov;
	}
};

