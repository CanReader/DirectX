#include "TextureClass.h"

TextureClass::TextureClass() : Texture{0} {}

TextureClass::~TextureClass(){}

bool TextureClass::Initialize(ID3D11Device* dev, LPCSTR file)
{
	D3DX11_IMAGE_INFO info;
	info.ImageFileFormat = D3DX11_IFF_JPG;

	D3DX11_IMAGE_LOAD_INFO info1;
	info1.pSrcInfo = &info;
	info1.Usage = D3D11_USAGE_STAGING;
	info1.Format = DXGI_FORMAT_FROM_FILE;
	info1.CpuAccessFlags = D3D11_CPU_ACCESS_READ;

	//HRESULT hr = D3DX11CreateShaderResourceViewFromFile(dev,(LPCSTR)file,&info1,NULL,&Texture,NULL);

	HRESULT hr = D3DX11CreateTextureFromFile(dev,(LPCSTR)file,NULL,NULL,&TextResource,NULL);

	END(hr)

	D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
	ZeroMemory(&srvd,sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	srvd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvd.Texture2D.MipLevels = 1;
	srvd.Texture2D.MostDetailedMip = 0;

	hr = dev->CreateShaderResourceView(TextResource,&srvd,&Texture);

	END(hr)

	return true;
}

void TextureClass::Render()
{
}

void TextureClass::Shutdown()
{
	if (Texture)
		Texture->Release();
	Texture = 0;
}

ID3D11ShaderResourceView* TextureClass::GetTexture()
{
	return Texture;
}



