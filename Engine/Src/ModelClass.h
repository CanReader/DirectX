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

class ModelClass
{
public:
	ModelClass(LPCSTR Texture);
	~ModelClass();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*);
	void Render(XMMATRIX*);
	void Shutdown();

	LPCSTR TextureFile;

	void SetMatrices(XMMATRIX*);
	void SetLighting(LightClass&);

	XMMATRIX GetWorld();

	ID3D11ShaderResourceView* GetTexture();

private:
	ID3D11Buffer* VertexBuffer;
	ID3D11Buffer* IndexBuffer;

	ID3D11Device* _dev;
	ID3D11DeviceContext* _devcon;

	//XMMATRIX* Matrices;
	XMMATRIX World;

	XMMATRIX TranslationMatrix, RotationMatrix, ScalingMatrix;

	TextureClass* Texture;
	ShaderClass* shader;

	bool CreateTestCube(ID3D11Device* dev);
};


#endif