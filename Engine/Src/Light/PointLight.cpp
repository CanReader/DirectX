#include "PointLight.h"

PointLight::PointLight()
{
	this->LightType = TYPE_LIGHT::POINT;
}

PointLight::PointLight(XMFLOAT4 Ambient, XMFLOAT4 Diffuse, XMFLOAT3 Position)
{
	this->SetDiffuse(Diffuse);
	this->SetAmbient(Ambient);

	this->Position = Position;
	this->Range = 100.0f;
	this->att = XMFLOAT3(0.0f,0.2f,0.0f);

	this->LightType = TYPE_LIGHT::POINT;
}

PointLight::PointLight(XMFLOAT4 Ambient, XMFLOAT4 Diffuse, XMFLOAT3 Position, float Range)
{
	this->SetDiffuse(Diffuse);
	this->SetAmbient(Ambient);

	this->Position = Position;
	this->Range = Range;

	this->LightType = TYPE_LIGHT::POINT;
}

void PointLight::SetBuffer(D3D11_MAPPED_SUBRESOURCE& map)
{
	auto* lbuffr = (PointLight::Buffer*)map.pData;
	lbuffr->Ambient = this->Ambient;
	lbuffr->DiffuseColor = this->Diffuse;
	lbuffr->Position = this->Position;
	lbuffr->range = this->Range;
	lbuffr->att = XMFLOAT3(0.0f,0.3f,0);
}

void PointLight::SetPosition(XMFLOAT3 Position)
{
	this->Position = Position;
}

void PointLight::SetAtt(XMFLOAT3 att)
{
	this->att = att;
}

void PointLight::SetRange(float Range)
{
	this->Range = Range;
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
