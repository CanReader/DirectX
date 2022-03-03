#include "ShaderClass.h"

ShaderClass::ShaderClass(LPCSTR File) : vs{ 0 }, ps{ 0 }, lay{ 0 }, ConstantBuffer{ 0 }, LightBuffer{0}, Sample{0}
{
	ShaderFile = File;
}

ShaderClass::ShaderClass() : vs{ 0 }, ps{ 0 }, lay{ 0 }, ConstantBuffer{ 0 }, LightBuffer{ 0 }, Sample{ 0 }
{
	ShaderFile = NULL;
}

ShaderClass::~ShaderClass()
{
}

bool ShaderClass::Initialize(ID3D11Device* dev, ID3D11DeviceContext* devcon)
{
	_dev = dev;
	_devcon = devcon;

	if (ShaderFile)
	{
	 if (!CreateShaders(ShaderFile))
		 return false;
	}
	else
	{
		if (!CreateShaders("Src/Shaders/ColorShader.hlsl"))
			return false;
	}

	//Create Constant buffer
	if (!CreateConstantBufferAndSampler())
		return false;

	return true;
}

void ShaderClass::Shutdown()
{
	ReleaseInterface(vs)
	ReleaseInterface(ps)
	ReleaseInterface(lay)
	ReleaseInterface(ConstantBuffer)
	ReleaseInterface(Sample)
	ReleaseInterface(LightBuffer);
}

void ShaderClass::Render(int IndexNumber, ID3D11ShaderResourceView* text)
{
	_devcon->IASetInputLayout(lay);

	SetShaderParameters();

	_devcon->VSSetConstantBuffers(0,1,&ConstantBuffer);
	_devcon->PSSetConstantBuffers(0,1,&ConstantBuffer);
	_devcon->PSSetConstantBuffers(1,1,&LightBuffer);
	_devcon->VSSetShader(vs,NULL,0);
	_devcon->PSSetShader(ps,NULL,0);
	_devcon->PSSetShaderResources(0,1,&text);
	_devcon->PSSetSamplers(0,1,&Sample);
	_devcon->DrawIndexed(IndexNumber,0,0);
}

void ShaderClass::SetMatrices(XMMATRIX Matrices[])
{
	this->Matrices = Matrices;
}

void ShaderClass::SetLight(LightClass& Light)
{
	this->Light = &Light;
}

bool ShaderClass::CreateShaders(LPCSTR ShaderFile)
{
	ID3D10Blob* vsblob;
	ID3D10Blob* psblob;
	ID3D10Blob* errorblob;

	//Create Vertex shader
	HRESULT hr = D3DX11CompileFromFile(ShaderFile, NULL, NULL, "VS", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &vsblob, &errorblob, 0);

	if (FAILED(hr))
		if (errorblob)
			DX_FATAL((const char*)(errorblob->GetBufferPointer()));
		else
			MessageBox(NULL,"Failed to find specified shader file","Fatal error" ,MB_OK | MB_ICONERROR);

	END(hr)

		hr = _dev->CreateVertexShader(vsblob->GetBufferPointer(), vsblob->GetBufferSize(), NULL, &vs);

	END(hr)

		//Create Pixel shader
		 hr = D3DX11CompileFromFile(ShaderFile, NULL, NULL, "PS", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &psblob, &errorblob, 0);

	if (FAILED(hr))
		if (errorblob)
			DX_FATAL("ShaderClass", (const char*)(errorblob->GetBufferPointer()));
		else
			MessageBox(NULL,"Failed to find specified shader file","Fatal error" ,MB_OK | MB_ICONERROR);

	hr = _dev->CreatePixelShader(psblob->GetBufferPointer(), psblob->GetBufferSize(), NULL, &ps);

	END(hr)

		//Create input layout
		D3D11_INPUT_ELEMENT_DESC iedesc[] =
	{

{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"TEXCOORD",0,DXGI_FORMAT_R32G32B32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0}
	};

	 hr = _dev->CreateInputLayout(iedesc, sizeof(iedesc) / sizeof(iedesc[0]), vsblob->GetBufferPointer(), vsblob->GetBufferSize(),&lay);

	 END(hr)

     return true;
}

bool ShaderClass::CreateConstantBufferAndSampler()
{
	MatrixBuffer buffr;
	buffr.world =      XMMatrixIdentity();
	buffr.view =       XMMatrixIdentity();
	buffr.projection = XMMatrixIdentity();

	D3D11_BUFFER_DESC constdesc;
	constdesc.Usage = D3D11_USAGE_DYNAMIC;
	constdesc.ByteWidth = sizeof(MatrixBuffer);
	constdesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constdesc.StructureByteStride = 0;
	constdesc.MiscFlags = 0;
	constdesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA constsub;
	constsub.pSysMem = &buffr;

	HRESULT hr = _dev->CreateBuffer(&constdesc,&constsub,&ConstantBuffer);

	END(hr)

	D3D11_BUFFER_DESC ldesc;
	ldesc.Usage = D3D11_USAGE_DYNAMIC;
	ldesc.ByteWidth = sizeof(LightShaderBuffer);
	ldesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	ldesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	ldesc.MiscFlags = 0;
	ldesc.StructureByteStride = 0;

	hr = _dev->CreateBuffer(&ldesc,NULL,&LightBuffer);

	END(hr)

	D3D11_SAMPLER_DESC sampdesc;
	ZeroMemory(&sampdesc,sizeof(D3D11_SAMPLER_DESC));
	sampdesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampdesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampdesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampdesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampdesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampdesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampdesc.MinLOD = 0;
	sampdesc.MaxLOD = D3D11_FLOAT32_MAX;

	hr = _dev->CreateSamplerState(&sampdesc,&Sample);

	END(hr)

	return true;
}

void ShaderClass::SetShaderParameters()
{
	XMMATRIX world = XMMatrixTranspose(Matrices[0]);
	XMMATRIX view = XMMatrixTranspose(Matrices[1]);
	XMMATRIX proj = XMMatrixTranspose(Matrices[2]);

	D3D11_MAPPED_SUBRESOURCE map;

	_devcon->Map(ConstantBuffer,0,D3D11_MAP_WRITE_DISCARD,0,&map);

	MatrixBuffer* buffr = (MatrixBuffer*)map.pData;

	buffr->world = world;
	buffr->view = view;
	buffr->projection = proj;

	_devcon->Unmap(ConstantBuffer,0);
	
	_devcon->Map(LightBuffer,0,D3D11_MAP_WRITE_DISCARD,0,&map);

	LightShaderBuffer* lbuffr = (LightShaderBuffer*)map.pData;

	lbuffr->Direction = Light->GetDirection();
	lbuffr->Ambient = Light->GetAmbient();
	lbuffr->DiffuseColor = Light->GetDiffuse();

	_devcon->Unmap(LightBuffer,0);
}
