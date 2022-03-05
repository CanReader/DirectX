#include "LightClass.h"

LightClass::LightClass()
{
}

LightClass::LightClass(XMFLOAT3 Direction, XMFLOAT4 Ambient, XMFLOAT4 Diffuse) 
{
	this->Direction = Direction;
	this->Ambient = Ambient;
	this->Diffuse = Diffuse;
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

XMFLOAT3 LightClass::GetDirection()
{
	return Direction;
}

XMFLOAT4 LightClass::GetAmbient()
{
	return Ambient;
}

XMFLOAT4 LightClass::GetDiffuse()
{
	return Diffuse;
}
