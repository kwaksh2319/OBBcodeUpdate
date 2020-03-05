#include"stdafx.h"
#include"ObbCollision.h"

ObbCollision::ObbCollision()
{
}

ObbCollision::~ObbCollision()
{
}



Vector3 ObbCollision::getHeightVector(SHAPE a)
{
	Vector3 ret;
	ret.x = a.scale.y*sinf(a.rot) / 2;
	ret.y = -a.scale.y*cosf(a.rot) / 2;
	return ret;
}

Vector3 ObbCollision::getWidthVector(SHAPE a)
{
	Vector3 ret;
	ret.x = a.scale.x*cosf(a.rot) / 2;
	ret.y = -a.scale.x*sinf(a.rot) / 2;
	return ret;
}

Vector3 ObbCollision::getUnitVector(Vector3 a)
{

	Vector3 ret;
	float size;
	size = sqrt(a.x*a.x + a.y*a.y);
	ret.x = a.x / size;
	ret.y = a.y / size;
	return ret;
}

bool ObbCollision::OBB(SHAPE a, SHAPE b)
{
	Vector3 dist = a.position - b.position;
	Vector3 vec[4] = { getHeightVector(a),getHeightVector(b),getWidthVector(a),getWidthVector(b) };
	Vector3 unit;
	for (int i = 0; i < 4; i++) {
		double sum = 0;
		unit = getUnitVector(vec[i]);
		for (int j = 0; j < 4; j++) {
			sum += abs(vec[j].x*unit.x + vec[j].y*unit.y);
		}
		if (abs(dist.x*unit.x + dist.y*unit.y) > sum) {
			return false;
		}
	}
	return true;
}