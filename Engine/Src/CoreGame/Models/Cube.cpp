#include "Cube.h"
#include <D3DX11.h>

Cube::Cube()
{
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

bool Cube::Initialize()
{
    HRESULT hr;

    //Initialize the layout of buffer
    D3D11_INPUT_ELEMENT_DESC Colorlayout[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };

    D3D11_INPUT_ELEMENT_DESC Texturelayout[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"Tex", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };

    //Define vertecies of object
    Vertex CubeVertecies[] =
    {
    Vertex(-1.0f, -1.0f, +1.0f, 1.0f, 0.0f, 0.0f, 1.0f),
    Vertex(-1.0f, +1.0f, +1.0f, 0.0f, 1.0f, 0.0f, 1.0f),
    Vertex(+1.0f, +1.0f, +1.0f, 0.0f, 0.0f, 1.0f, 1.0f),
    Vertex(+1.0f, -1.0f, +1.0f, 1.0f, 1.0f, 0.0f, 1.0f),
    
    Vertex(-1.0f, -1.0f, -1.0f, 0.0f, 1,1,1),
    Vertex(-1.0f, +1.0f, -1.0f, 1.0f, 1,1,1),
    Vertex(+1.0f, +1.0f, -1.0f, 1.0f, 1,1,1),
    Vertex(+1.0f, -1.0f, -1.0f, 1.0f, 1,1,1),
    };

    //Define indecies
    DWORD indicies[] =
    { 
        // front face
   0, 1, 2,
   0, 2, 3,

   // back face
   4, 6, 5,
   4, 7, 6,

   // left face
   4, 5, 1,
   4, 1, 0,

   // right face
   3, 2, 6,
   3, 6, 7,

   // top face
   1, 5, 6,
   1, 6, 2,

   // bottom face
   4, 0, 3,
   4, 3, 7
    };

    //Before using vertex shader, compile file
    ID3D10Blob* errorBlob = nullptr;
    hr = D3DX11CompileFromFile("ColorShader.hlsl", nullptr, nullptr, "VS", "vs_4_0", D3D10_SHADER_DEBUG, 0, nullptr, &vsBlob, &errorBlob, &hr);

    //Some error handling
    if (FAILED(hr))
        if (errorBlob)
        {
            char* compileErrors = static_cast<char*>(errorBlob->GetBufferPointer());
            std::cerr << "Shader compilation failed with error:\n" << compileErrors << std::endl;
            return false;
        }
        else
            ENDSTR(hr,"HELP");

        //Create the vertex shader
    hr = dev->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), NULL, &vs);
    ENDSTR(hr, "Failed to create vertex shader!");


    //Before using vertex shader, compile file
    D3DX11CompileFromFile("ColorShader.hlsl", 0, 0, "PS", "ps_4_0", 0, 0, 0, &psBlob, 0, &hr);
    ENDSTR(hr, "Failed to compile the pixel shader file!");
    
    //Create the pixel shader
    hr = dev->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), NULL, &ps);
    ENDSTR(hr, "Failed to create pixel shader!");

    //Initialize the resource and add the vertecies
    D3D11_SUBRESOURCE_DATA sdata = { 0 };
    sdata.pSysMem = CubeVertecies;
    UINT laysize = ARRAYSIZE(layout);

    //Create the input layout that is gonna defines how the buffer send
    hr = dev->CreateInputLayout(layout, laysize, vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &lay);

    ENDSTR(hr, "Failed to create input layout!");
    
    devcon->IASetInputLayout(lay);

    //Create the vertex buffer
    D3D11_BUFFER_DESC bDesc;
    ZeroMemory(&bDesc,sizeof(bDesc));

    bDesc.Usage = D3D11_USAGE_DEFAULT;
    bDesc.ByteWidth = sizeof(Vertex) * 8;
    bDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bDesc.MiscFlags = 0;
    bDesc.CPUAccessFlags = 0;

    hr = dev->CreateBuffer(&bDesc, &sdata, &VertexBuffer);

    ENDSTR(hr,"Failed to create vertex buffer!")
    
    //Initialize the index buffer descriptipn
    D3D11_BUFFER_DESC iDesc;
    ZeroMemory(&iDesc,sizeof(D3D11_BUFFER_DESC));

    iDesc.Usage = D3D11_USAGE_DEFAULT;
    iDesc.ByteWidth = sizeof(DWORD) * IndexCount;
    iDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    iDesc.MiscFlags = 0;
    iDesc.CPUAccessFlags = 0;
    
    //Create input layout for index buffer
    D3D11_SUBRESOURCE_DATA idata = {0};
    idata.pSysMem = indicies;

    //Create Index buffer
    hr = dev->CreateBuffer(&iDesc,&idata,&IndexBuffer);
    
    ENDSTR(hr, "Failed to create index buffer!")

    //Initialize the MVP buffer description
    D3D11_BUFFER_DESC cbDesc;
    ZeroMemory(&cbDesc,sizeof(D3D11_BUFFER_DESC));
    cbDesc.Usage = D3D11_USAGE_DEFAULT;
    cbDesc.ByteWidth = sizeof(cbObject);
    cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbDesc.MiscFlags = 0;
    cbDesc.CPUAccessFlags = 0;

    hr = dev->CreateBuffer(&cbDesc,nullptr,&WVPBuffer);

    ENDSTR(hr,"Failed to create Constant Buffer!");

    ConstantBuffer = std::make_unique<cbObject>();

    return true;
}

void Cube::Render(float t)
{
    if (devcon == nullptr)
        return;

    UINT stride = sizeof(Vertex);
    UINT offset = 0;

    worldMatrix = worldMatrix * XMMatrixRotationAxis(XMVectorSet(1,1,1,1), t);
    
    ConstantBuffer->WMP = XMMatrixTranspose(worldMatrix * viewMatrix * projMatrix);

    devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    devcon->UpdateSubresource(WVPBuffer,0,nullptr,ConstantBuffer.get(), 0, 0);
    devcon->VSSetConstantBuffers(0,1,&WVPBuffer);
    devcon->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);
    devcon->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT,0);
    devcon->VSSetShader(vs, NULL, 0);
    devcon->PSSetShader(ps, NULL, 0);
    devcon->DrawIndexed(IndexCount, 0,0);
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
