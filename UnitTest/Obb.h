#pragma once
class Obb {



public:
	Obb();
	~Obb();
	bool ObbCollision(Vector3 posA, Matrix worldA, Vector3 posB, Matrix worldB,Vector3 scale,Vector3 playerScale);

private:
	static float lA[4];
	static float lB[4];
	static float l[4];
	static bool lCheck[4];

	//static float dr1;
	//static float dr2;


	struct ObbDesc {
		Vector3 Position;
		Vector3 Direction[3];//[0] 수평 [1]수직
		float Length[2];// 물체 내 충돌 허용길이
	};
	//void CreateObb(OUT ObbDesc * out, D3DXVECTOR2 position, D3DXMATRIX & world, D3DXVECTOR2 & length);
	//static void CreateObb(OUT ObbDesc* out, Vector3 position, Matrix& world, Vector3& length);
	static void CreateObb(OUT ObbDesc* out, Vector3 positionA, Vector3 positionB, Matrix& world, Vector3& length);
	static float SeperateAxis(Vector3 & seperate, Vector3 & e1, Vector3 & e2);
	static bool CheckObb(ObbDesc &obbA, ObbDesc &obbB);
	
};