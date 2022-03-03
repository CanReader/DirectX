#ifndef MODELCLASS_H_
#define MODELCLASS_H_

#include "TextureClass.h"
#include "ShaderClass.h"

struct Vertex
{
	XMFLOAT3 Pos;
	XMFLOAT2 Texture;
	XMFLOAT3 Normal;
};

struct Triangle
{
	Vertex v1;
	Vertex v2;
	Vertex v3;
};

class ModelClass
{
public:
	ModelClass(LPCSTR Texture);
	ModelClass(LPCSTR Texture, XMFLOAT3 Location);
	ModelClass(XMFLOAT3 Location);
	ModelClass(const ModelClass&);
	~ModelClass();

	Vertex* vertices;
	int* Indices;

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*);
	void Render();
	void Shutdown();

	LPCSTR TextureFile;

	XMFLOAT3 GetPos();

	void Translate(XMFLOAT3 Position);
	void Translate(FLOAT x, FLOAT y, FLOAT z);
	void RotatePitchYawRoll(FLOAT Pitch, FLOAT Yaw, FLOAT Roll);
	void RotateX(float Angle);
	void RotateY(float Angle);
	void RotateZ(float Angle);
	void Scale(XMFLOAT3 Scale);
	void Scale(FLOAT Value);
	void Scale(FLOAT x, FLOAT y, FLOAT z);

	void SetMatrices(XMMATRIX*);
	void SetLighting(LightClass&);

	XMMATRIX GetWorld();

	ID3D11ShaderResourceView* GetTexture();

private:
	ID3D11Buffer* VertexBuffer;
	ID3D11Buffer* IndexBuffer;

	ID3D11Device* _dev;
	ID3D11DeviceContext* _devcon;

	XMMATRIX* Matrices;
	XMMATRIX World;

	XMMATRIX TranslationMatrix, RotationMatrix, ScalingMatrix;

	TextureClass* Texture;
	ShaderClass* shader;

	bool CreateTestCube(ID3D11Device* dev);
};


#endif