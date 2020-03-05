#include"stdafx.h"
#include"Obb.h"


/*
bool Obb(Sprite * a, Sprite * b)
{

	ObbDesc obbA, obbB;
	D3DXVECTOR2 lengthA = D3DXVECTOR2(a->world._11, a->world._22)*0.5f;
	CreateObb(&obbA, a->position, a->world, lengthA);
	D3DXVECTOR2 lengthB = D3DXVECTOR2(b->world._11, b->world._22)*0.5f;
	CreateObb(&obbB, b->position, b->world, lengthB);

	return CheckObb(obbA, obbB);
}*/
/*
void CreateObb(OUT ObbDesc * out, D3DXVECTOR2 position, D3DXMATRIX & world, D3DXVECTOR2 & length)
{
	out->Position = position;
	out->Length[0] = length.x;
	out->Length[1] = length.y;

	out->Direction[0] = D3DXVECTOR2(world._11, world._12);
	out->Direction[1] = D3DXVECTOR2(world._21, world._22);
	//방향값을 사용할때 자신의 크기를 나줘줘야 함-> 결과값이 1
	//방향값을 사용할떄는 항상 1로 만들어 놓고 쓴다.
	//Normalize는 방향 원소에서 크기를 나눠준다.
	D3DXVec2Normalize(&out->Direction[0], &out->Direction[0]);
	D3DXVec2Normalize(&out->Direction[1], &out->Direction[1]);

	*/

Obb::Obb()
{
}

Obb::~Obb()
{
}

bool Obb::ObbCollision(Vector3 posA, Matrix worldA, Vector3 posB, Matrix worldB,Vector3 scale, Vector3 playerScale)
{
	ObbDesc obbA, obbB;
	//D3DXVECTOR2 lengthA = D3DXVECTOR2(a->world._11, a->world._22)*0.5f;
	//Vector3 lengthA = Vector3(worldA._11, worldA._22, worldA._33)*0.5;
	Vector3 lengthA = playerScale*0.6f;
	CreateObb(&obbA, posA, posB, worldA, lengthA);

	Vector3 lengthB = scale*0.6f;
	CreateObb(&obbB, posB,  posA, worldB, lengthB);

	return CheckObb(obbA, obbB);

}

void Obb::CreateObb(OUT ObbDesc * out, Vector3 positionA, Vector3 positionB, Matrix & world, Vector3 & length)
{

	out->Position = positionA;
	out->Length[0] = length.x;
	out->Length[1] = length.y;
	

	out->Direction[0] = Vector3(world._11, world._12, world._13);
	out->Direction[1] = Vector3(world._21, world._22, world._23);
	//out->Direction[0] = Vector3(world._11, world._12, world._13);
	//out->Direction[1] = Vector3(world._21, world._22,world._23);
	out->Direction[2] = Vector3(world._31, world._32, world._33);
	//방향값을 사용할때 자신의 크기를 나줘줘야 함-> 결과값이 1
	//방향값을 사용할떄는 항상 1로 만들어 놓고 쓴다.
	//Normalize는 방향 원소에서 크기를 나눠준다.

	//D3DXVec2Normalize(&out->Direction[0], &out->Direction[0]);
	//D3DXVec2Normalize(&out->Direction[1], &out->Direction[1]);
	D3DXVec3Normalize(&out->Direction[0], &out->Direction[0]);
	D3DXVec3Normalize(&out->Direction[1], &out->Direction[1]);
	//D3DXVec3Normalize(&out->Direction[2], &out->Position);


}

float Obb::SeperateAxis(Vector3  & seperate, Vector3  & e1, Vector3  & e2)
{
	float r1 = fabsf(D3DXVec3Dot(&seperate, &e1));
	float r2 = fabsf(D3DXVec3Dot(&seperate, &e2));
	return r1 + r2;

}

float Obb::lA[4];
float  Obb::lB[4];
float Obb::l[4];
bool Obb::lCheck[4];

bool Obb::CheckObb(ObbDesc & obbA, ObbDesc & obbB)
{

	//nea : 방향(노말라이즈된 1로 변환된 값), ea : 방향*길이(1에 대한 비율을 곱한값)
	Vector3 nea1 = obbA.Direction[0], ea1 = nea1 * obbA.Length[0];//x방향
	Vector3  nea2 = obbA.Direction[1], ea2 = nea2 * obbA.Length[1];//y방향
	Vector3  nea3 = obbA.Direction[2], ea3 = nea3 * obbA.Length[2];//z방향

	Vector3  neb1 = obbB.Direction[0], eb1 = neb1 * obbB.Length[0];//x방향
	Vector3  neb2 = obbB.Direction[1], eb2 = neb2 * obbB.Length[1];//y방향
	Vector3  neb3 = obbB.Direction[2], eb3 = neb3 * obbB.Length[2];//z방향
	//방향 계산 :obbA위치 -obbB위치 (서로 떨어져 있는 거리이기도함)
	Vector3  direction = obbA.Position - obbB.Position;//Distance 중점간의 거리
	Vector3  direction2 = obbB.Position - obbA.Position;//Distance 중점간의 거리
	//lengthA 충돌체A lengthB 충돌체 B length 거리 
	float lengthA = 0.0f, lengthB = 0.0f, length = 0.0f, length2 = 0.0f;

	//수평방향(A)

	//lengthA = D3DXVec2Length(&ea1);
	//lengthA = D3DXVec3Length(&ea1);
	lengthA = fabsf(D3DXVec3Length(&ea1));
	lengthB = fabsf(SeperateAxis(nea1, eb1, eb2));
	//length = fabsf(D3DXVec2Dot(&direction, &nea1));
	length = fabsf(D3DXVec3Dot(&direction, &nea1));

	//length2 = fabsf(D3DXVec3Dot(&direction2, &neb2));
	lA[0] = lengthA;
	lB[0] = lengthB;
	l[0] = length;
	lCheck[0] = length > lengthA + lengthB;

	if (length > lengthA + lengthB )
		return false;

	//수직방향(A)
	//lengthA = D3DXVec2Length(&ea2);
	lengthA = fabsf(D3DXVec3Length(&ea1));
	
	lengthB = fabsf(SeperateAxis(nea2, eb1, eb2));
	//length = fabsf(D3DXVec2Dot(&direction, &nea2));
	length = fabsf(D3DXVec3Dot(&direction, &nea2));
	//length2 = fabsf(D3DXVec3Dot(&direction2, &neb1));
	lA[1] = lengthA;
	lB[1] = lengthB;
	l[1] = length;
	lCheck[1] = length > lengthA + lengthB ;

	if (length > lengthA + lengthB )
		return false;
	//수평방향(B)
	lengthA = fabsf(SeperateAxis(neb1, ea1, ea2));
	//lengthB = D3DXVec2Length(&eb1);
	lengthB = fabsf(D3DXVec3Length(&eb1));
	//length = fabsf(D3DXVec2Dot(&direction, &neb1));
	length = fabsf(D3DXVec3Dot(&direction, &neb1 ));
	//length2 = fabsf(D3DXVec3Dot(&direction2, &nea2));
	lA[2] = lengthA;
	lB[2] = lengthB;
	l[2] = length;
	lCheck[2] = length > lengthA + lengthB ;

	if (length > lengthA + lengthB )
		return false;

	//수직방향(B)
	lengthA = fabsf(SeperateAxis(neb2, ea1, ea2));
	lengthB = fabsf(D3DXVec3Length(&eb2));
	length = fabsf(D3DXVec3Dot(&direction, &neb2));
	//length2 = fabsf(D3DXVec3Dot(&direction2, &nea1));
	//lengthB = D3DXVec2Length(&eb2);
	//length = fabsf(D3DXVec2Dot(&direction, &neb2));

	lA[3] = lengthA;
	lB[3] = lengthB;
	l[3] = length;
	lCheck[3] = length > lengthA + lengthB ;

	if (length > lengthA + lengthB )
		return false;
	

	return true;
}
