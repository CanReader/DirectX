#ifndef _LIGHTCLASS_H_
#define _LIGHTCLASS_H_

#include <d3d11.h>
#include <xnamath.h>

enum class TYPE_LIGHT
{
	NONE = 0,
	DIRECTIONAL = 1,
	POINT = 2,
	SPOT = 3,
};

class LightClass
{
public:
	struct Buffer
	{
		XMFLOAT3 Direction;
		float padding;
		XMFLOAT4 Ambient;
		XMFLOAT4 DiffuseColor;
	};

public:

	LightClass();
	LightClass(XMFLOAT3, XMFLOAT4, XMFLOAT4);
	LightClass(LightClass&);

	virtual void SetBuffer(LightClass::Buffer&);
	
	void SetDirection(XMFLOAT3);
	void SetAmbient(XMFLOAT4);
	void SetDiffuse(XMFLOAT4);

	virtual TYPE_LIGHT GetLight();
	XMFLOAT3 GetDirection();
	XMFLOAT4 GetDiffuse();
	XMFLOAT4 GetAmbient();


private:
	TYPE_LIGHT LightType;

	XMFLOAT3 Direction;
	XMFLOAT4 Ambient;
	XMFLOAT4 Diffuse;
};

#endif // !1