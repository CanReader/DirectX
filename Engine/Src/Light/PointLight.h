#ifndef POINTLIGHT_H_
#define POINTLIGHT_H_

#include "LightClass.h"

class PointLight : public LightClass
{
public:
	struct Buffer
	{
		XMFLOAT4 Ambient;
		XMFLOAT4 DiffuseColor;
		XMFLOAT3 Position;
		float range;
		XMFLOAT3 att;
		float padding3;
	};

public:
	PointLight();
	PointLight(XMFLOAT4 Ambient, XMFLOAT4 Diffuse,XMFLOAT3 Position);
	PointLight(XMFLOAT4 Ambient, XMFLOAT4 Diffuse,XMFLOAT3 Position, float Range);
	PointLight(XMFLOAT4 Ambient, XMFLOAT4 Diffuse);
	PointLight(PointLight&);

	void SetBuffer(D3D11_MAPPED_SUBRESOURCE&) override;
	void SetPosition(XMFLOAT3);
	void SetAtt(XMFLOAT3);
	void SetRange(float);

	TYPE_LIGHT GetLight() override;
	float GetRange();
	XMFLOAT3 GetPosition();
	XMFLOAT3 GetAtt();

private:
	TYPE_LIGHT LightType;

	XMFLOAT3 Position;
	float Range;
	XMFLOAT3 att;
};


#endif // !SPOTLIGHT_H_