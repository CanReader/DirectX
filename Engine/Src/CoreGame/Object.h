#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <Windows.h>
#include <d3d11.h>
#include <xnamath.h>


class Object
{
public:
	Object();

	virtual bool Initialize() = 0;
	virtual void Render() = 0;
	virtual void Update(float t) = 0;

	const char* GetName();

	struct Vertex
{
	Vertex(XMFLOAT3 pos)
	{
		this->pos = pos;
	}

	Vertex(float x, float y, float z)
	{
		this->pos = XMFLOAT3(x, y, z);
		this->col = XMFLOAT4(1, 0, 1, 1);
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

	Vertex(float x, float y, float z, float u, float v)
	{
		pos = XMFLOAT3(x, y, z);
		TextureUV = XMFLOAT2(u, v);
	}

	XMFLOAT3 pos;
	XMFLOAT2 TextureUV;
	XMFLOAT4 col;
};
protected:
	char* Name;
};


#endif // !_OBJECT_H_