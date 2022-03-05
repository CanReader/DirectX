#ifndef _LIGHTCLASS_H_
#define _LIGHTCLASS_H_

#include <d3d11.h>
#include <xnamath.h>

class LightClass
{
public:
	LightClass();
	LightClass(XMFLOAT3, XMFLOAT4, XMFLOAT4);
	LightClass(LightClass&);
	~LightClass();

	void SetDirection(XMFLOAT3);
	void SetAmbient(XMFLOAT4);
	void SetDiffuse(XMFLOAT4);

	XMFLOAT3 GetDirection();
	XMFLOAT4 GetDiffuse();
	XMFLOAT4 GetAmbient();

private:
	XMFLOAT3 Direction;
	XMFLOAT4 Ambient;
	XMFLOAT4 Diffuse;
};

#endif // !1