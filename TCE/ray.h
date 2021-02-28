#pragma once
#include "global_functions.h"

class Ray
{
public:

	float rayAngle;

	Ray(float _rayAngle)
	{
		this->rayAngle = normalizeAngle(_rayAngle);
	}
};
