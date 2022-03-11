#include "LightClass.h"

LightClass::LightClass()
{
}

LightClass::LightClass(XMFLOAT3 Direction, XMFLOAT4 Ambient, XMFLOAT4 Diffuse) 
{
	this->Direction = Direction;
	this->Ambient = Ambient;
	this->Diffuse = Diffuse;

	this->LightType = TYPE_LIGHT::DIRECTIONAL;
}

void LightClass::SetDirection(XMFLOAT3 Direction)
{
	this->Direction = Direction;
}

void LightClass::SetAmbient(XMFLOAT4 Ambient) 
{
	this->Ambient = Ambient;
}

void LightClass::SetDiffuse(XMFLOAT4 Diffuse) 
{
	this->Diffuse = Diffuse;
}

TYPE_LIGHT LightClass::GetLight()
{
	return this->LightType;
}

XMFLOAT3 LightClass::GetDirection()
{
	return Direction;
}

XMFLOAT4 LightClass::GetAmbient()
{
	return Ambient;
}

void LightClass::SetBuffer(D3D11_MAPPED_SUBRESOURCE& map)
{
	auto* lbuffr = (Buffer*)map.pData;

	lbuffr->Direction = Direction;
	lbuffr->Ambient = Ambient;
	lbuffr->DiffuseColor = Diffuse;
}

XMFLOAT4 LightClass::GetDiffuse()
{
	return Diffuse;
}
