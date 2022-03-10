#ifndef POINTLIGHT_H_
#define POINTLIGHT_H_

#include "LightClass.h"

class PointLight : public LightClass
{
public:
	struct Buffer : public LightClass::Buffer
	{
		XMFLOAT3 Position;
		float padding2;
		XMFLOAT3 att;
		float padding3;
	};

public:
	PointLight();
	PointLight(XMFLOAT3 Direction, XMFLOAT4 Ambient, XMFLOAT4 Diffuse,XMFLOAT3 Position);
	PointLight(XMFLOAT3 Direction, XMFLOAT4 Ambient, XMFLOAT4 Diffuse);
	PointLight(PointLight&);

	void SetBuffer(LightClass::Buffer&) override;
	void SetPosition(XMFLOAT3);
	void SetAtt(XMFLOAT3);

	TYPE_LIGHT GetLight() override;
	XMFLOAT3 GetPosition();
	XMFLOAT3 GetAtt();

private:
	TYPE_LIGHT LightType;

	XMFLOAT3 Position;
	XMFLOAT3 att;
};


#endif // !SPOTLIGHT_H_