#include "ModelClass.h"

ModelClass::ModelClass(LPCSTR TextureFile, XMFLOAT3 Location) : World{ XMMatrixIdentity() }, Texture{ new TextureClass() }, shader{ new ShaderClass("Src/Shaders/TextureShader.hlsl") }, VertexBuffer{ 0 }, IndexBuffer{ 0 }, TranslationMatrix{ XMMatrixTranslation(0,0,0) }, RotationMatrix{ XMMatrixRotationX(0) }, ScalingMatrix{ XMMatrixScaling(1,1,1) }
{
    this->TextureFile = TextureFile;
    Translate(Location);
}

ModelClass::ModelClass(LPCSTR TextureFile) : World{ XMMatrixIdentity() }, Texture{ new TextureClass() }, shader{ new ShaderClass("Src/Shaders/TextureShader.hlsl") }, VertexBuffer{ 0 }, IndexBuffer{ 0 }, TranslationMatrix{ XMMatrixTranslation(0,0,0) }, RotationMatrix{ XMMatrixRotationX(0) }, ScalingMatrix{ XMMatrixScaling(1,1,1) }
{
    this->TextureFile = TextureFile;
}

ModelClass::ModelClass(XMFLOAT3 Location) : World{ XMMatrixIdentity() }, Texture{ new TextureClass() }, shader{ new ShaderClass() }, VertexBuffer{ 0 }, IndexBuffer{ 0 }, TranslationMatrix{ XMMatrixTranslation(0,0,0) }, RotationMatrix{ XMMatrixRotationX(0) }, ScalingMatrix{ XMMatrixScaling(1,1,1) }
{
    Translate(Location);
}

ModelClass::~ModelClass()
{
}

bool ModelClass::Initialize(ID3D11Device* dev, ID3D11DeviceContext* devcon)
{
    _dev = dev;
    _devcon = devcon;

    Texture->Initialize(_dev, TextureFile);

    CreateTestCube(dev);

    if (!shader->Initialize(dev, devcon))
        return false;

    return true;
}

void ModelClass::Render()
{
    World = TranslationMatrix * RotationMatrix * ScalingMatrix;

    unsigned int stride = sizeof(Vertex);
    unsigned int offset = 0;

    _devcon->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);
    _devcon->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
    _devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    if (!Matrices)
    {
        DX_WARN("It is not possible to display object without matrices!");
        return;
    }

    shader->SetMatrices(Matrices);
    shader->Render(36, GetTexture());
}

void ModelClass::Shutdown()
{
    if (VertexBuffer)
        VertexBuffer->Release();

    if (IndexBuffer)
        IndexBuffer->Release();

    Texture->Shutdown();
    delete Texture;
    Texture = 0;

    shader->Shutdown();
    delete shader;
    shader = 0;
}

XMFLOAT3 ModelClass::GetPos()
{
    return XMFLOAT3(World._41, World._42, World._43);
}

void ModelClass::Translate(XMFLOAT3 Position)
{
    TranslationMatrix = XMMatrixTranslation(Position.x, Position.y, Position.z);
}

void ModelClass::Translate(FLOAT x, FLOAT y, FLOAT z)
{
    TranslationMatrix = XMMatrixTranslation(x, y, z);
}

void ModelClass::RotatePitchYawRoll(FLOAT Pitch, FLOAT Yaw, FLOAT Roll)
{
    RotationMatrix = XMMatrixRotationRollPitchYaw(Pitch, Yaw, Roll);
}

void ModelClass::RotateX(float Angle)
{
    RotationMatrix = XMMatrixRotationX(Angle * XM_PI / 180);
}

void ModelClass::RotateY(float Angle)
{
    RotationMatrix = XMMatrixRotationY(Angle * XM_PI / 180);
}

void ModelClass::RotateZ(float Angle)
{
    RotationMatrix = XMMatrixRotationZ(Angle * XM_PI / 180);
}

void ModelClass::Scale(XMFLOAT3 Scale)
{
    ScalingMatrix = XMMatrixScaling(Scale.x, Scale.y, Scale.z);
}

void ModelClass::Scale(FLOAT value)
{
    ScalingMatrix = XMMatrixScaling(value, value, value);
}

void ModelClass::Scale(FLOAT x, FLOAT y, FLOAT z)
{
    ScalingMatrix = XMMatrixScaling(x, y, z);
}

void ModelClass::SetMatrices(XMMATRIX* Matrices)
{
    this->Matrices = Matrices;
}

void ModelClass::SetLighting(LightClass& Light)
{
    shader->SetLight(Light);
}

XMMATRIX ModelClass::GetWorld()
{
    return World;
}

ID3D11ShaderResourceView* ModelClass::GetTexture()
{
    return Texture->GetTexture();
}

bool ModelClass::CreateTestCube(ID3D11Device* dev)
{

    Vertex vertices[] =
    {
        //Front face
        {XMFLOAT3(-0.5f, -0.5f, 1) ,XMFLOAT2(1,1),XMFLOAT3(0,0,-1.0f)}, //Top left 0
        {XMFLOAT3(-0.5f,  0.5f, 1)  ,XMFLOAT2(1,0),XMFLOAT3(0,0,-1.0f)}, //Bottom left 1
        {XMFLOAT3(0.5f,  0.5f,  1) ,XMFLOAT2(0,0),XMFLOAT3(0,0,-1.0f)}, //Bottom right 2
        {XMFLOAT3(0.5f, -0.5f,  1)  ,XMFLOAT2(0,1),XMFLOAT3(0,0,-1.0f)}, //Top right 3

        //Back face
        {XMFLOAT3(-0.5f, -0.5f, 2) ,XMFLOAT2(1,1),XMFLOAT3(0,0,-1.0f)}, //Top left 4 
        {XMFLOAT3(-0.5f,  0.5f, 2)  ,XMFLOAT2(1,0),XMFLOAT3(0,0,-1.0f)}, //Bottom left 5
        {XMFLOAT3(0.5f,  0.5f, 2) ,XMFLOAT2(0,0),XMFLOAT3(0,0,-1.0f)}, //Bottom right 6
        {XMFLOAT3(0.5f, -0.5f, 2)  ,XMFLOAT2(0,1),XMFLOAT3(0,0,-1.0f)}, //Top right 7

        //Left face
        {XMFLOAT3(-0.5f, -0.5f, 1) ,XMFLOAT2(0,1),XMFLOAT3(0,0,-1.0f)}, //Top right 8
        {XMFLOAT3(-0.5f,  0.5f, 1)  ,XMFLOAT2(0,0),XMFLOAT3(0,0,-1.0f)}, //Bottom right 9
        {XMFLOAT3(-0.5f,  0.5f, 2)  ,XMFLOAT2(1,0),XMFLOAT3(0,0,-1.0f)}, //Bottom left 10
        {XMFLOAT3(-0.5f, -0.5f, 2) ,XMFLOAT2(1,1),XMFLOAT3(0,0,-1.0f)}, //Top left 11

        //Right face
        {XMFLOAT3(0.5f, -0.5f,  1)  ,XMFLOAT2(0,1),XMFLOAT3(0,0,-1.0f)}, //Top left 12
        {XMFLOAT3(0.5f,  0.5f,  1) ,XMFLOAT2(0,0),XMFLOAT3(0,0,-1.0f)}, //Bottom left 13
        {XMFLOAT3(0.5f,  0.5f, 2) ,XMFLOAT2(1,0),XMFLOAT3(0,0,-1.0f)}, //Bottom right 14
        {XMFLOAT3(0.5f, -0.5f, 2)  ,XMFLOAT2(1,1),XMFLOAT3(0,0,-1.0f)}, //Top right 15

        //Bottom face
        {XMFLOAT3(-0.5f, -0.5f, 2) ,XMFLOAT2(0,1),XMFLOAT3(0,0,-1.0f)}, //Top left 16
        {XMFLOAT3(-0.5f, -0.5f, 1) ,XMFLOAT2(0,0),XMFLOAT3(0,0,-1.0f)}, //Bottom left 17
        {XMFLOAT3(0.5f, -0.5f,  1)  ,XMFLOAT2(1,0),XMFLOAT3(0,0,-1.0f)}, //Bottom right 18
        {XMFLOAT3(0.5f, -0.5f, 2)  ,XMFLOAT2(1,1),XMFLOAT3(0,0,-1.0f)}, //Top right 19

        //Top face
        {XMFLOAT3(-0.5f, 0.5f, 2) ,XMFLOAT2(1,1),XMFLOAT3(0,0,-1.0f)}, //Top left 20
        {XMFLOAT3(-0.5f, 0.5f, 1) ,XMFLOAT2(1,0),XMFLOAT3(0,0,-1.0f)}, //Bottom left 21
        {XMFLOAT3(0.5f, 0.5f,  1)  ,XMFLOAT2(0,0),XMFLOAT3(0,0,-1.0f)}, //Bottom right 22
        {XMFLOAT3(0.5f, 0.5f, 2)  ,XMFLOAT2(0,1),XMFLOAT3(0,0,-1.0f)}, //Top right 23

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

    D3D11_BUFFER_DESC vdesc = {};
    vdesc.ByteWidth = sizeof(vertices);
    vdesc.Usage = D3D11_USAGE_DEFAULT;
    vdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vdesc.CPUAccessFlags = 0;
    vdesc.StructureByteStride = sizeof(Vertex);
    vdesc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA vsub;
    vsub.pSysMem = vertices;
    vsub.SysMemPitch = 0;
    vsub.SysMemSlicePitch = 0;

    HRESULT hr = dev->CreateBuffer(&vdesc, &vsub, &VertexBuffer);
    END(hr)

        D3D11_BUFFER_DESC idesc = {};
    idesc.ByteWidth = sizeof(Indices);
    idesc.Usage = D3D11_USAGE_DEFAULT;
    idesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    idesc.CPUAccessFlags = 0;
    idesc.StructureByteStride = 0;
    idesc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA isub;
    isub.pSysMem = Indices;
    isub.SysMemPitch = 0;
    isub.SysMemSlicePitch = 0;

    hr = dev->CreateBuffer(&idesc, &isub, &IndexBuffer);

    END(hr)

        return true;
}

