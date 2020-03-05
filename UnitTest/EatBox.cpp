#include "stdafx.h"
#include "EatBox.h"
#include"Obb.h"
#include"ObbC.h"
#include"ObbCollision.h"

void EatBox::Initialize()
{
	shader = new Shader(L"05_World.fx");
	//obb = new Obb();
	//obbC = new ObbC();
	obbcoli = new ObbCollision();
	vertices[0].Position = Vector3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = Vector3(-0.5f, +0.5f, 0.0f);
	vertices[2].Position = Vector3(+0.5f, -0.5f, 0.0f);

	vertices[3].Position = Vector3(+0.5f, -0.5f, 0.0f);
	vertices[4].Position = Vector3(-0.5f, +0.5f, 0.0f);
	vertices[5].Position = Vector3(+0.5f, +0.5f, 0.0f);

	
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.ByteWidth = sizeof(Vertex) * 6;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA subResource = { 0 };
	subResource.pSysMem = vertices;

	Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer));
	playerPosition = Vector3(0.0f, 0.0f, 0.0f);
	playerScale= Vector3(1.0f, 1.0f, 1.0f);
	for (int i = 0; i < 10; i++) {
		D3DXMatrixIdentity(&world[i]);
	}
	Setting();
}

void EatBox::Destroy()
{
	SafeDelete(shader);
	//SafeDelete(obb);
	//SafeDelete(obbC);
	SafeDelete(obbcoli);
	SafeRelease(vertexBuffer);
}

void EatBox::Update()
{
	for (int i = 0; i < 10; i++) {

		Matrix S, R, T;
		D3DXMatrixScaling(&S, scale[i].x, scale[i].y, 1.0f);
		D3DXMatrixTranslation(&T, position[i].x, position[i].y, position[i].z);
		D3DXMatrixRotationZ(&R, rotaition[i].z);
		//D3DXMatrixRotationZ(&R, rotaition.z);
		world[i] = S * R* T;
	}
	if (!(Keyboard::Get()->Press(VK_SHIFT)))
	{
		if (Keyboard::Get()->Press(VK_RIGHT))
			playerPosition.x += 2.0f * Time::Delta();
		else if (Keyboard::Get()->Press(VK_LEFT))
			playerPosition.x -= 2.0f * Time::Delta();

		if (Keyboard::Get()->Press(VK_UP))
			playerPosition.y += 2.0f * Time::Delta();
		else if (Keyboard::Get()->Press(VK_DOWN))
			playerPosition.y -= 2.0f * Time::Delta();
		SHAPE player;
		SHAPE enemy[10];
		for(int i=0;i<10;i++){

		
			

			player.position = playerPosition;
			player.scale = playerScale;
			player.rot = playerRotaition.z;

			enemy[i].position = position[i];
			enemy[i].scale = scale[i];
			enemy[i].rot = rotaition[i].z;


			//bCheck[i] = obb->ObbCollision(playerPosition, playerWorld, position[i], world[i],scale[i], playerScale);
			
			bCheck[i] = obbcoli->OBB(player,enemy[i]);
			//bCheck[i] = obbC->ObbCollision(Vector2(playerPosition.x, playerPosition.y), playerWorld, Vector2(position[i].x, position[i].y), world[i]);
		if (bCheck[i]) {
			RenderCheck[i] = true;
		   }
		}
	}
	else
	{
		
		if (Keyboard::Get()->Press(VK_RIGHT))
			playerRotaition.z += 2.0f * Time::Delta();
		else if (Keyboard::Get()->Press(VK_LEFT))
			playerRotaition.z -= 2.0f * Time::Delta();

		//if (Keyboard::Get()->Press(VK_UP))
		
		//else if (Keyboard::Get()->Press(VK_DOWN))
		
	}
	int count = 0;
	for (int i = 0; i < 10; i++) {
		
		if (RenderCheck[i] == true) {
			count++;
		}
		if (count >= 10) {
			Setting();
			count = 0;
		}
	}
	
	

}

void EatBox::Render()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	static bool bWireframe = false;
	ImGui::Checkbox("Wireframe", &bWireframe);

	shader->AsMatrix("View")->SetMatrix(Context::Get()->View());
	shader->AsMatrix("Projection")->SetMatrix(Context::Get()->Projection());

	//World
	{
		Matrix S,R, T;
		D3DXMatrixScaling(&S,playerScale.x, playerScale.y, playerScale.z);
		D3DXMatrixTranslation(&T, playerPosition.x, playerPosition.y, playerPosition.z);
		D3DXMatrixRotationZ(&R, playerRotaition.z);
		playerWorld = S *R* T;

		shader->AsMatrix("World")->SetMatrix(playerWorld);
		shader->AsVector("Color")->SetFloatVector(Color(1, 0, 0, 1));

		shader->Draw(0, bWireframe == true ? 1 : 0, 6);
	}
	for(int i=0;i<10;i++){
	if(!RenderCheck[i]){
	//World2
	{
		//Matrix world;
		//D3DXMatrixIdentity(&world);
		
		shader->AsMatrix("World")->SetMatrix(world[i]);
		shader->AsVector("Color")->SetFloatVector(color[i]);
		shader->Draw(0, bWireframe == true ? 1 : 0, 6);
	}
	}
	}
}

void EatBox::Setting()
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 10; i++) {
		RenderCheck[i] = false;
		position[i] = Vector3((float)(rand() % 6) - (float)(rand() % 6), (float)(rand() % 5) - (float)(rand() % 5), 1.0f);
		//scale[i] = Vector3(1.0f, 1.0f, 1.0f);
		scale[i] = Vector3((float)(rand() % 10)*0.1+1.0f, (float)(rand() %10)*0.1 + 1.0f, 0.0f);
		color[i] = Color((float)(rand() % 10)*0.1, (float)(rand() % 10)*0.1, (float)(rand() % 10)*0.1, 1);
		rotaition[i].z = (float)(rand() % 10) - (float)(rand() % 10);
	}
}
