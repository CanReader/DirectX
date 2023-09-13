#ifndef _CUBE_H_
#define _CUBE_H_

#include <D3D11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>	
#include <xnamath.h>
#include "../Object.h"
#include "../../Debugging/Log.h"

#define IndexCount 36

class Cube : public Object
{
public:
	Cube();
	Cube(float x, float y, float z);

	virtual bool Initialize() override;
	virtual void Render(float t) override;
	void Shutdown();

	void SetDevice(ID3D11Device* dev, ID3D11DeviceContext* devcon);

private:
	ID3D11Device* dev;
	ID3D11DeviceContext* devcon;

	ID3D11InputLayout* lay;

	ID3D11VertexShader* vs;
	ID3D11PixelShader* ps;

	ID3D11Buffer* WVPBuffer;
	ID3D11Buffer* VertexBuffer;
	ID3D11Buffer* IndexBuffer;

	ID3D10Blob* vsBlob;
	ID3D10Blob* psBlob;

	XMMATRIX worldMatrix;
	XMMATRIX viewMatrix;
	XMMATRIX projMatrix;

	struct Vertex
	{
		Vertex(XMFLOAT3 pos)
		{
			this->pos = pos;
		}

		Vertex(float x, float y, float z)
		{
			this->pos = XMFLOAT3(x, y, z);
			this->col = XMFLOAT4(1,0,1,1);
		}

		Vertex(XMFLOAT3 pos, XMFLOAT4 col)
		{
			this->pos = pos;
			this->col = col;
		}

		Vertex(float x, float y, float z, float r, float g, float b, float a)
		{
			pos = XMFLOAT3(x, y, z);
			col = XMFLOAT4(r, g, b, a);
		}

		XMFLOAT3 pos;
		XMFLOAT4 col;
	};

	struct cbObject
	{
		cbObject() : WMP(XMMatrixIdentity()){}

		XMMATRIX WMP;
	};

	std::unique_ptr<cbObject> ConstantBuffer;
};


#endif // !1