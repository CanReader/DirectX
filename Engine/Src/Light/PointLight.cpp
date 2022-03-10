#include "PointLight.h"

PointLight::PointLight()
{
	this->LightType = TYPE_LIGHT::POINT;
}

PointLight::PointLight(XMFLOAT3 Direction, XMFLOAT4 Ambient, XMFLOAT4 Diffuse, XMFLOAT3 Position)
{
	this->SetDirection(Direction);
	this->SetAmbient(Ambient);
	this->SetDiffuse(Diffuse);

	this->Position = Position;

	this->LightType = TYPE_LIGHT::POINT;
}

PointLight::PointLight(XMFLOAT3 Direction, XMFLOAT4 Ambient, XMFLOAT4 Diffuse)
{
	this->SetDirection(Direction);
	this->SetAmbient(Ambient);
	this->SetDiffuse(Diffuse);

	this->Position = XMFLOAT3(0,0,0);

	this->LightType = TYPE_LIGHT::POINT;
}

void PointLight::SetBuffer(LightClass::Buffer&)
{
}

void PointLight::SetPosition(XMFLOAT3 Position)
{
	this->Position = Position;
}

void PointLight::SetAtt(XMFLOAT3 att)
{
	this->att = att;
}

TYPE_LIGHT PointLight::GetLight()
{
	return LightType;
}

XMFLOAT3 PointLight::GetPosition()
{
	return Position;
}

XMFLOAT3 PointLight::GetAtt()
{
	return att;
}
