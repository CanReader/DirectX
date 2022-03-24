#include "ModelClass.h"

ModelClass::ModelClass(LPCSTR Texture) : Texture(new TextureClass()), shader(new ShaderClass("Src/Shaders/TextureShader.hlsl"))
{
	this->TextureFile = Texture;
}

ModelClass::~ModelClass(){}

bool ModelClass::Initialize(ID3D11Device* dev, ID3D11DeviceContext* devcon)
{
	this->_dev = dev;
	this->_devcon = devcon;

    Texture->Initialize(dev,TextureFile);

    XMFLOAT3 Normal = XMFLOAT3(0, 0, -1);
    Vertex vertices[] =
    {
        //Front face
        {XMFLOAT3(-0.5f,-0.5f,+1) ,XMFLOAT2(1,1),Normal}, //Top left 0
        {XMFLOAT3(-0.5f,+0.5f,+1) ,XMFLOAT2(1,0),Normal}, //Bottom left 1
        {XMFLOAT3(+0.5f,+0.5f,+1) ,XMFLOAT2(0,0),Normal}, //Bottom right 2
        {XMFLOAT3(+0.5f,-0.5f,+1) ,XMFLOAT2(0,1),Normal}, //Top right 3

        //Back face
        {XMFLOAT3(-0.5f,-0.5f,+2) ,XMFLOAT2(1,1),Normal}, //Top left 4 
        {XMFLOAT3(-0.5f,+0.5f,+2) ,XMFLOAT2(1,0),Normal}, //Bottom left 5
        {XMFLOAT3(+0.5f,+0.5f,+2) ,XMFLOAT2(0,0),Normal}, //Bottom right 6
        {XMFLOAT3(+0.5f,-0.5f,+2) ,XMFLOAT2(0,1),Normal}, //Top right 7

        //Left face
        {XMFLOAT3(-0.5f,-0.5f,+1) ,XMFLOAT2(0,1),Normal}, //Top right 8
        {XMFLOAT3(-0.5f,+0.5f,+1) ,XMFLOAT2(0,0),Normal}, //Bottom right 9
        {XMFLOAT3(-0.5f,+0.5f,+2) ,XMFLOAT2(1,0),Normal}, //Bottom left 10
        {XMFLOAT3(-0.5f,-0.5f,+2) ,XMFLOAT2(1,1),Normal}, //Top left 11

        //Right face
        {XMFLOAT3(+0.5f,-0.5f,+1) ,XMFLOAT2(0,1),Normal}, //Top left 12
        {XMFLOAT3(+0.5f,+0.5f,+1) ,XMFLOAT2(0,0),Normal}, //Bottom left 13
        {XMFLOAT3(+0.5f,+0.5f,+2) ,XMFLOAT2(1,0),Normal}, //Bottom right 14
        {XMFLOAT3(+0.5f,-0.5f,+2) ,XMFLOAT2(1,1),Normal}, //Top right 15

        //Bottom face
        {XMFLOAT3(-0.5f,-0.5f,+2) ,XMFLOAT2(0,1),Normal}, //Top left 16
        {XMFLOAT3(-0.5f,-0.5f,+1) ,XMFLOAT2(0,0),Normal}, //Bottom left 17
        {XMFLOAT3(+0.5f,-0.5f,+1) ,XMFLOAT2(1,0),Normal}, //Bottom right 18
        {XMFLOAT3(+0.5f,-0.5f,+2) ,XMFLOAT2(1,1),Normal}, //Top right 19

        //Top face
        {XMFLOAT3(-0.5f,+0.5f,+2) ,XMFLOAT2(1,1),Normal}, //Top left 20
        {XMFLOAT3(-0.5f,+0.5f,+1) ,XMFLOAT2(1,0),Normal}, //Bottom left 21
        {XMFLOAT3(+0.5f,+0.5f,+1) ,XMFLOAT2(0,0),Normal}, //Bottom right 22
        {XMFLOAT3(+0.5f,+0.5f,+2) ,XMFLOAT2(0,1),Normal}, //Top right 23

    };

    int Indices[] =
    {
        //Front face
        0, 1, 2,
        0, 2, 3,

        // Back face
        5, 4, 6,
        6, 4, 7,

        // Left face
        9, 8, 10,
        10, 8, 11,

        // Right face
        12, 13, 14,
        12, 14, 15,

        // Top face
        21, 20, 22,
        22, 20, 23,

        // Bottom face
        16, 17, 18,
        16, 18, 19
    };

	//Vertex Buffer
    D3D11_BUFFER_DESC vdesc;
    vdesc.ByteWidth = sizeof(vertices);
    vdesc.Usage = D3D11_USAGE_DEFAULT;
    vdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vdesc.CPUAccessFlags = 0;
    vdesc.StructureByteStride = sizeof(Vertex);
    vdesc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA vdata;
    vdata.pSysMem = vertices;
    vdata.SysMemPitch = 0;
    vdata.SysMemSlicePitch = 0;

	HRESULT hr = dev->CreateBuffer(&vdesc,&vdata,&VertexBuffer);

    END(hr)

	//Index buffer
    D3D11_BUFFER_DESC idesc;
    idesc.ByteWidth = sizeof(Indices);
    idesc.Usage = D3D11_USAGE_DEFAULT;
    idesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    idesc.CPUAccessFlags = 0;
    idesc.StructureByteStride = sizeof(int);
    idesc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA idata;
    idata.pSysMem = Indices;
    idata.SysMemPitch = 0;
    idata.SysMemSlicePitch = 0;

	hr = dev->CreateBuffer(&idesc,&idata,&IndexBuffer);

    END(hr)

	if (!shader->Initialize(dev, devcon))
		return false;

	return true;
}

void ModelClass::Render(XMMATRIX* Matrices)
{
    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    _devcon->IASetVertexBuffers(0,1,&VertexBuffer,&stride,&offset);
    _devcon->IASetIndexBuffer(IndexBuffer,DXGI_FORMAT_R32_UINT,0);
    _devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    shader->Render(36,GetTexture(), Matrices);
}

void ModelClass::Shutdown()
{
    if (VertexBuffer)
    {
        VertexBuffer->Release();
        delete VertexBuffer;
    }

    if (IndexBuffer)
    {
        IndexBuffer->Release();
        delete IndexBuffer;
    }

    Texture->Shutdown();
    shader->Shutdown();
}

ID3D11ShaderResourceView* ModelClass::GetTexture()
{
    return Texture->GetTexture();
}
