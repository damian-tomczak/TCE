#pragma once
#include <math.h> 

constexpr float PI = 3.14159265358979323846f;

float toRadian(float _degress)
{
    return _degress * PI / 180;
}

static float normalizeAngle(float _angle)
{
	_angle = fmod(_angle, (2 * PI));

	if (_angle < 0)
		_angle = (2 * PI) + _angle;

	return _angle;
}