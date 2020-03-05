#pragma once
#include "Systems/IExecute.h"

class EatBox : public IExecute
{
public:
	virtual void Initialize() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void PreRender() override {}
	virtual void Render() override;
	virtual void PostRender() override {}
	virtual void ResizeScreen() override {}

private:
	Shader* shader;

	Vertex vertices[6];
	ID3D11Buffer* vertexBuffer;
	class Obb*obb;
	class ObbC*obbC;
	class ObbCollision*obbcoli;
	Matrix playerWorld;
	
	Vector3 playerPosition = Vector3(0, 0, 1.0f);
	Vector3 playerScale = Vector3(1, 1, 1);
	Vector3 playerRotaition = Vector3(0, 0, 0);

	Matrix world[10];
	Vector3 position[10] ;
	Vector3 scale[10] ;
	Vector3 rotaition[10] ;
	

	//Vector3 position[2] = { Vector3(0, 0, 0), Vector3(1.1f, 1.1f, 0.0f) };
	//Vector3 scale[2] = { Vector3(1, 1, 1), Vector3(1, 1, 1) };
	//Vector3 rotaition = Vector3(0, 0, 0);
	Color color[10];
	bool RenderCheck[10];
	bool bCheck[10];
	void Setting();

};