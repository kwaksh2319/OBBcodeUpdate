#pragma once
struct SHAPE {
	Vector3 position;
	Vector3 scale;
	float rot;
};

class ObbCollision {



public:
	ObbCollision();
	~ObbCollision();

	
	bool OBB(SHAPE a, SHAPE b);
	
	
private:
	SHAPE shape[2];
private:
	Vector3 getHeightVector(SHAPE a);
	Vector3 getWidthVector(SHAPE a);
	Vector3 getUnitVector(Vector3 a);
	

};