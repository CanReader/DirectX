#ifndef _TEXTURECLASS_H_
#define _TEXTURECLASS_H_

#include <d3d11.h>
#include <D3DX11tex.h>

#define END(hr) if(FAILED(hr)) return false;

class TextureClass
{

public:
	TextureClass();
	TextureClass(const TextureClass&);
	~TextureClass();

	bool Initialize(ID3D11Device*, LPCSTR);
	void Render();
	void Shutdown();

	ID3D11ShaderResourceView* GetTexture();
private:
	ID3D11ShaderResourceView* Texture;
	ID3D11Resource* TextResource;

public:
private:

};


#endif // !_TEXTURECLASS_H_