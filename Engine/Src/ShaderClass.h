#ifndef SHADERCLASS_H_
#define SHADERCLASS_H_

#include <d3d11.h>
#include <D3DX11.h>
#include <xnamath.h>
#include <D3Dcompiler.h>
#include <filesystem>
#include "Light/LightClass.h"

#include "Debugger.h"

#define ReleaseInterface(i) if(i) i->Release(); i = 0;
#define END(hr) if(FAILED(hr)) return false;

class ShaderClass
{
private:
	struct MatrixBuffer
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};

	struct LightShaderBuffer
	{
		XMFLOAT3 Direction;
		float padding;
		XMFLOAT4 Ambient;
		XMFLOAT4 DiffuseColor;
	};

public:
	ShaderClass();
	ShaderClass(LPCSTR File);
	ShaderClass(const ShaderClass&);
	~ShaderClass();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*);
	void Shutdown();
	void Render(int, ID3D11ShaderResourceView*);

	void SetMatrices(XMMATRIX[]);
	void SetLight(LightClass&);

private:
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool CreateShaders(LPCSTR);
	bool CreateConstantBufferAndSampler();

	void SetShaderParameters();

private:
	LPCSTR ShaderFile;

	XMMATRIX* Matrices;

	ID3D11Device* _dev;
	ID3D11DeviceContext* _devcon;

	ID3D11VertexShader* vs;
	ID3D11PixelShader* ps;
	ID3D11InputLayout* lay;
	ID3D11Buffer* ConstantBuffer;
	ID3D11Buffer* LightBuffer;
	ID3D11SamplerState* Sample;

	LightClass* Light;
};


#endif // !1