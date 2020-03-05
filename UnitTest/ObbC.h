#pragma once
class ObbC {



public:
	ObbC();
	~ObbC();
	bool ObbCollision(Vector2 posA, Matrix worldA, Vector2 posB, Matrix worldB);

private:
	static float lA[4];
	static float lB[4];
	static float l[4];
	static bool lCheck[4];

	//static float dr1;
	//static float dr2;


	struct ObbDesc {
		Vector2 Position;
		Vector2 Direction[3];//[0] 수평 [1]수직
		float Length[2];// 물체 내 충돌 허용길이
	};
	//void CreateObb(OUT ObbDesc * out, D3DXVECTOR2 position, D3DXMATRIX & world, D3DXVECTOR2 & length);
	static void CreateObb(OUT ObbDesc* out, Vector2 position, Matrix& world, Vector2& length);
	static float SeperateAxis(Vector2 & seperate, Vector2 & e1, Vector2 & e2);
	static bool CheckObb(ObbDesc &obbA, ObbDesc &obbB);

};