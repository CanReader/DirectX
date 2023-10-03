#include "Cube.h"
#include <D3DX11.h>

Cube::Cube()
{
    ConstantBuffer = std::make_unique<cbObject>();
    worldMatrix = XMMatrixIdentity();

    
    XMVECTOR camPos = XMVectorSet(0,0,-5,0);
    XMVECTOR camFocus = XMVectorSet(0,0,0,0);
    XMVECTOR camUp = XMVectorSet(0,5,0,0);

    viewMatrix = XMMatrixLookAtLH(camPos,camFocus,camUp);
    projMatrix = XMMatrixPerspectiveFovLH(0.4f*XM_PI,(float)1920/1080,1.0f,1000.0f);
}

Cube::Cube(float x, float y, float z)
{
    worldMatrix = XMMatrixIdentity();

    worldMatrix *= XMMatrixTranslation(x,y,z);

    XMVECTOR camPos = XMVectorSet(0, 0, -5, 0);
    XMVECTOR camFocus = XMVectorSet(0, 0, 0, 0);
    XMVECTOR camUp = XMVectorSet(0, 5, 0, 0);

    viewMatrix = XMMatrixLookAtLH(camPos, camFocus, camUp);
    projMatrix = XMMatrixPerspectiveFovLH(0.4f * XM_PI, (float)1920 / 1080, 1.0f, 1000.0f);
}

Cube::Cube(Vertex* Vertecies)
{
    worldMatrix = XMMatrixIdentity();

    worldMatrix *= XMMatrixTranslation(0,0,0);

    XMVECTOR camPos = XMVectorSet(0, 0, -5, 0);
    XMVECTOR camFocus = XMVectorSet(0, 0, 0, 0);
    XMVECTOR camUp = XMVectorSet(0, 5, 0, 0);

    viewMatrix = XMMatrixLookAtLH(camPos, camFocus, camUp);
    projMatrix = XMMatrixPerspectiveFovLH(0.4f * XM_PI, (float)1920 / 1080, 1.0f, 1000.0f);

    this->vertices = Vertecies;
}

bool Cube::Initialize()
{
    if(vertices == nullptr)
    vertices =
    new Vertex[24]{
        // Front Face
        Vertex(-1.0f, -1.0f, -1.0f, 0.0f, 1.0f),
        Vertex(-1.0f,  1.0f, -1.0f,0.0f, 0.0f),
        Vertex(1.0f,  1.0f, -1.0f, 1.0f, 0.0f),
        Vertex(1.0f, -1.0f, -1.0f, 1.0f, 1.0f),

        // Back Face
        Vertex(-1.0f, -1.0f, 1.0f, 1.0f, 1.0f),
        Vertex(1.0f, -1.0f, 1.0f, 0.0f, 1.0f),
        Vertex(1.0f,  1.0f, 1.0f, 0.0f, 0.0f),
        Vertex(-1.0f,  1.0f, 1.0f, 1.0f, 0.0f),

        // Top Face
        Vertex(-1.0f, +1.0f, -1.0f, +0.0f, +1.0f),//8
        Vertex(-1.0f, +1.0f, +1.0f, +0.0f, +0.0f),
        Vertex(+1.0f, +1.0f, -1.0f, +1.0f, +1.0f),
        Vertex(+1.0f, +1.0f, +1.0f, +1.0f, +0.0f),
        
        // Bottom Face
        Vertex(-1.0f, -1.0f, -1.0f, +0.0f, +1.0f),//8
        Vertex(-1.0f, -1.0f, +1.0f, +0.0f, +0.0f),
        Vertex(+1.0f, -1.0f, -1.0f, +1.0f, +1.0f),
        Vertex(+1.0f, -1.0f, +1.0f, +1.0f, +0.0f),

        //Left Face
        Vertex(-1.0f, +1.0f, -1.0f, +0.0f, 1.0f),//16
        Vertex(-1.0f, -1.0f, -1.0f, +0.0f, 0.0f),
        Vertex(-1.0f, +1.0f, +1.0f, +1.0f, 1.0f),
        Vertex(-1.0f, -1.0f, +1.0f, +1.0f, 0.0f),

        //Right Face
        Vertex(+1.0f, +1.0f, -1.0f, +0.0f, 1.0f),//16
        Vertex(+1.0f, -1.0f, -1.0f, +0.0f, 0.0f),
        Vertex(+1.0f, +1.0f, +1.0f, +1.0f, 1.0f),
        Vertex(+1.0f, -1.0f, +1.0f, +1.0f, 0.0f),
    };

    indices = new int[IndexCount]{
        // Front Face
        0,  1,  2,
        2,  0,  3,

        // Back Face
        4,  5,  6,
        4,  6,  7,

        //Top
        8, 9, 10,
        9, 10, 11,

        //Bottom
        12, 13, 14,
        13, 14, 15,

        //Left
        16, 17, 18,
        17, 18, 19,

        //Right
        20, 21, 22,
        21, 22, 23
    };

    CompileShader();
    
    if (!CreateBuffers())
        ENDSTR(E_FAIL,"Failed to create buffers! The object will not be drawen!!");

    if (!InitializeTexture())
        ENDSTR(E_FAIL,"Failed to initialize textures!");

    delete layoutDesc;
    delete vertices;
    delete indices;

    return true;
}

void Cube::Render()
{
    bool noRender = 
        !devcon ||
        !IndexBuffer ||
        !VertexBuffer ||
        !vs || !ps ||
        ConstantBuffer == nullptr;

    if (noRender)
        return;

    UINT stride = sizeof(Vertex);
    UINT offset = 0;

    ConstantBuffer->WMP = XMMatrixTranspose(worldMatrix * viewMatrix * projMatrix);

    if (Texture && samplerState)
    {
        devcon->PSSetShaderResources(0,1,&Texture);
        devcon->PSSetSamplers(0,1,&samplerState);
    }

    devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    devcon->UpdateSubresource(WVPBuffer,0,nullptr,ConstantBuffer.get(), 0, 0);
    devcon->VSSetConstantBuffers(0,1,&WVPBuffer);
    devcon->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);
    devcon->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT,0);
    devcon->VSSetShader(vs, NULL, 0);
    devcon->PSSetShader(ps, NULL, 0);
    devcon->DrawIndexed(IndexCount, 0,0);
}

void Cube::Update(float t)
{
}

void Cube::Shutdown()
{
    if(lay)
        lay->Release();

    if (vs)
        vs->Release();

    if (ps)
        ps->Release();

    if (VertexBuffer)
        VertexBuffer->Release();

    if (vsBlob)
        vsBlob->Release();

    if (psBlob)
        psBlob->Release();

    if(ConstantBuffer)
        ConstantBuffer.release();
}

void Cube::SetDevice(ID3D11Device* dev, ID3D11DeviceContext* devcon)
{
    this->dev = dev;
    this->devcon = devcon;
}

bool Cube::InitializeTexture()
{
    HRESULT hr;

    hr = D3DX11CreateShaderResourceViewFromFileA(dev,TexturePath,NULL,NULL,&Texture,NULL);

    ENDSTR(hr, "Failed to create a shader resource!");

    D3D11_SAMPLER_DESC SamplerDesc;
    ZeroMemory(&SamplerDesc,sizeof(D3D11_SAMPLER_DESC));

    SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    SamplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    SamplerDesc.MinLOD = 0;
    SamplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

    hr = dev->CreateSamplerState(&SamplerDesc,&samplerState);

    ENDSTR(hr,"Failed to create a sampler state");

    return true;
}

void Cube::CompileShader()
{
    if (!CompileTextureShader())
    {
        DX_ERROR("Failed to create a texture shader! Color shader is using instead");
        CompileColorShader();
    }
}

bool Cube::CompileColorShader()
{
    layoutDesc = new D3D11_INPUT_ELEMENT_DESC[2]
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };

    //Before using vertex shader, compile file
    ID3D10Blob* errorBlob = nullptr;
    HRESULT hr = D3DX11CompileFromFile("ColorShader.hlsl", nullptr, nullptr, "VS", "vs_4_0", D3D10_SHADER_DEBUG, 0, nullptr, &vsBlob, &errorBlob, &hr);

    //Some error handling
    if (FAILED(hr))
        if (errorBlob)
        {
            char* compileErrors = static_cast<char*>(errorBlob->GetBufferPointer());
            std::cerr << "Shader compilation failed with error:\n" << compileErrors << std::endl;

            return false;
        }
        else
            ENDSTR(hr, "HELP");

    //Create the vertex shader
    hr = dev->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), NULL, &vs);
    ENDSTR(hr, "Failed to create vertex shader!");


    //Before using vertex shader, compile file
    D3DX11CompileFromFile("ColorShader.hlsl", 0, 0, "PS", "ps_4_0", 0, 0, 0, &psBlob, 0, &hr);
    ENDSTR(hr, "Failed to compile the pixel shader file!");

    //Create the pixel shader
    hr = dev->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), NULL, &ps);
    ENDSTR(hr, "Failed to create pixel shader!");

    return true;
}

bool Cube::CompileTextureShader()
{
    layoutDesc = new D3D11_INPUT_ELEMENT_DESC[2]
    {
    {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
    {"TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };

    //Before using vertex shader, compile file
    ID3D10Blob* errorBlob = nullptr;
    HRESULT hr = D3DX11CompileFromFile("TextureShader.hlsl", nullptr, nullptr, "VS", "vs_4_0", D3D10_SHADER_DEBUG, 0, nullptr, &vsBlob, &errorBlob, &hr);

    //Some error handling
    if (FAILED(hr))
        if (errorBlob)
        {
            char* compileErrors = static_cast<char*>(errorBlob->GetBufferPointer());
            std::cerr << "Shader compilation failed with error:\n" << compileErrors << std::endl;

            return false;
        }
        else
            ENDSTR(hr, "HELP");

    //Create the vertex shader
    hr = dev->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), NULL, &vs);
    ENDSTR(hr, "Failed to create vertex shader!");


    //Before using vertex shader, compile file
    D3DX11CompileFromFile("TextureShader.hlsl", 0, 0, "PS", "ps_4_0", 0, 0, 0, &psBlob, 0, &hr);
    ENDSTR(hr, "Failed to compile the pixel shader file!");

    //Create the pixel shader
    hr = dev->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), NULL, &ps);
    ENDSTR(hr, "Failed to create pixel shader!");

    return true;
}

bool Cube::CreateInputLayout(D3D11_SUBRESOURCE_DATA* SubData)
{
    //Initialize the resource and add the vertecies
    SubData->pSysMem = vertices;

    //Create the input layout that is gonna defines how the buffer send
    HRESULT hr = dev->CreateInputLayout(layoutDesc, 2, vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &lay);

    ENDSTR(hr, "Failed to create input layout!");

    devcon->IASetInputLayout(lay);

    return true;
}

bool Cube::CreateBuffers()
{
    D3D11_SUBRESOURCE_DATA VertexData = { 0 };
    if (!CreateInputLayout(&VertexData))
        ENDSTR(E_FAIL,"Failed to create an input layout! The object will not be drawen..");

    D3D11_SUBRESOURCE_DATA IndexData = { 0 };
    IndexData.pSysMem = indices;


    //Create the vertex buffer
    D3D11_BUFFER_DESC VertexDesc;
    ZeroMemory(&VertexDesc, sizeof(D3D11_BUFFER_DESC));

    VertexDesc.Usage = D3D11_USAGE_DEFAULT;
    VertexDesc.ByteWidth = sizeof(Vertex) * IndexCount;
    VertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;


    HRESULT hr = dev->CreateBuffer(&VertexDesc, &VertexData, &VertexBuffer);

    ENDSTR(hr, "Failed to create vertex buffer!")

        //Initialize the index buffer descriptipn
    D3D11_BUFFER_DESC IndexDesc;
    ZeroMemory(&IndexDesc, sizeof(D3D11_BUFFER_DESC));

    IndexDesc.Usage = D3D11_USAGE_DEFAULT;
    IndexDesc.ByteWidth = sizeof(DWORD) * IndexCount;
    IndexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    IndexDesc.MiscFlags = 0;
    IndexDesc.CPUAccessFlags = 0;

   
    //Create Index buffer
    hr = dev->CreateBuffer(&IndexDesc, &IndexData, &IndexBuffer);

    ENDSTR(hr, "Failed to create index buffer!")

        //Initialize the MVP buffer description
    D3D11_BUFFER_DESC cbDesc;
    ZeroMemory(&cbDesc, sizeof(D3D11_BUFFER_DESC));
    cbDesc.Usage = D3D11_USAGE_DEFAULT;
    cbDesc.ByteWidth = sizeof(cbObject);
    cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbDesc.MiscFlags = 0;
    cbDesc.CPUAccessFlags = 0;

    hr = dev->CreateBuffer(&cbDesc, nullptr, &WVPBuffer);

    ENDSTR(hr, "Failed to create Constant Buffer!");

    return true;
}

