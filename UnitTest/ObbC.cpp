#include"stdafx.h"
#include"ObbC.h"


/*
bool ObbC(Sprite * a, Sprite * b)
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
	//���Ⱚ�� ����Ҷ� �ڽ��� ũ�⸦ ������� ��-> ������� 1
	//���Ⱚ�� ����ҋ��� �׻� 1�� ����� ���� ����.
	//Normalize�� ���� ���ҿ��� ũ�⸦ �����ش�.
	D3DXVec2Normalize(&out->Direction[0], &out->Direction[0]);
	D3DXVec2Normalize(&out->Direction[1], &out->Direction[1]);

	*/

ObbC::ObbC()
{
}

ObbC::~ObbC()
{
}

bool ObbC::ObbCollision(Vector2 posA, Matrix worldA, Vector2 posB, Matrix worldB)
{
	ObbDesc obbA, obbB;
	//D3DXVECTOR2 lengthA = D3DXVECTOR2(a->world._11, a->world._22)*0.5f;
	//Vector3 lengthA = Vector3(worldA._11, worldA._22, worldA._33)*0.7;
	//CreateObb(&obbA, posA, worldA, lengthA);

	//Vector3  lengthB = Vector3(worldB._11, worldB._22, worldB._33)*0.7;
	//CreateObb(&obbB, posB, worldB, lengthB);

	Vector2 lengthA = Vector2(worldA._11, worldA._22)*0.5;
	CreateObb(&obbA, posA, worldA, lengthA);

	Vector2  lengthB = Vector2(worldB._11, worldB._22)*0.5;
	CreateObb(&obbB, posB, worldB, lengthB);

	return CheckObb(obbA, obbB);

}

void ObbC::CreateObb(OUT ObbDesc * out, Vector2 position, Matrix & world, Vector2 & length)
{

	out->Position = position;
	out->Length[0] = length.x;
	out->Length[1] = length.y;

	out->Direction[0] = Vector2(world._11, world._12);
	out->Direction[1] = Vector2(world._21, world._22);

	//���Ⱚ�� ����Ҷ� �ڽ��� ũ�⸦ ������� ��-> ������� 1
	//���Ⱚ�� ����ҋ��� �׻� 1�� ����� ���� ����.
	//Normalize�� ���� ���ҿ��� ũ�⸦ �����ش�.

	//D3DXVec2Normalize(&out->Direction[0], &out->Direction[0]);
	//D3DXVec2Normalize(&out->Direction[1], &out->Direction[1]);
	D3DXVec2Normalize(&out->Direction[0], &out->Direction[0]);
	D3DXVec2Normalize(&out->Direction[1], &out->Direction[1]);
	


}

float ObbC::SeperateAxis(Vector2  & seperate, Vector2  & e1, Vector2  & e2)
{
	float r1 = fabsf(D3DXVec2Dot(&seperate, &e1));
	float r2 = fabsf(D3DXVec2Dot(&seperate, &e2));
	return r1 + r2;

}

float ObbC::lA[4];
float  ObbC::lB[4];
float ObbC::l[4];
bool ObbC::lCheck[4];

bool ObbC::CheckObb(ObbDesc & obbA, ObbDesc & obbB)
{

	//nea : ����(�븻������� 1�� ��ȯ�� ��), ea : ����*����(1�� ���� ������ ���Ѱ�)
	Vector2 nea1 = obbA.Direction[0], ea1 = nea1 * obbA.Length[0];//x����
	Vector2  nea2 = obbA.Direction[1], ea2 = nea2 * obbA.Length[1];//y����
	

	Vector2  neb1 = obbB.Direction[0], eb1 = neb1 * obbB.Length[0];//x����
	Vector2  neb2 = obbB.Direction[1], eb2 = neb2 * obbB.Length[1];//y����

	//���� ��� :obbA��ġ -obbB��ġ (���� ������ �ִ� �Ÿ��̱⵵��)
	Vector2  direction = obbA.Position - obbB.Position;//Distance �������� �Ÿ�
	
	//lengthA �浹üA lengthB �浹ü B length �Ÿ� 
	float lengthA = 0.0f, lengthB = 0.0f, length = 0.0f;

	//�������(A)

	//lengthA = D3DXVec2Length(&ea1);
	lengthA = D3DXVec2Length(&ea1);
	lengthB = SeperateAxis(nea1, eb1, eb2);
	//length = fabsf(D3DXVec2Dot(&direction, &nea1));
	length = fabsf(D3DXVec2Dot(&direction, &nea1));

	lA[0] = lengthA;
	lB[0] = lengthB;
	l[0] = length;
	lCheck[0] = length > lengthA + lengthB;

	if (length > lengthA + lengthB )
		return false;

	//��������(A)
	//lengthA = D3DXVec2Length(&ea2);
	lengthA = D3DXVec2Length(&ea2);
	lengthB = SeperateAxis(nea2, eb1, eb2);
	//length = fabsf(D3DXVec2Dot(&direction, &nea2));
	length = fabsf(D3DXVec2Dot(&direction, &nea2));

	lA[1] = lengthA;
	lB[1] = lengthB;
	l[1] = length;
	lCheck[1] = length > lengthA + lengthB ;

	if (length > lengthA + lengthB )
		return false;
	//�������(B)
	lengthA = SeperateAxis(neb1, ea1, ea2);
	//lengthB = D3DXVec2Length(&eb1);
	lengthB = D3DXVec2Length(&eb1);
	//length = fabsf(D3DXVec2Dot(&direction, &neb1));
	length = fabsf(D3DXVec2Dot(&direction, &nea1 ));
	
	lA[2] = lengthA;
	lB[2] = lengthB;
	l[2] = length;
	lCheck[2] = length > lengthA + lengthB ;

	if (length > lengthA + lengthB )
		return false;

	//��������(B)
	lengthA = SeperateAxis(neb2, ea1, ea2);
	lengthB = D3DXVec2Length(&eb2);
	length = fabsf(D3DXVec2Dot(&direction, &nea2));
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
