#include "CameraClass.h"

CameraClass::CameraClass() : Position{ XMFLOAT3(0,0,0) }, Rotation{XMFLOAT3(0,0,0)}
{
ViewMatrix = XMMatrixLookAtLH(XMVectorSet(0,0,-1.5f,0), XMVectorSet(0, 0, 0, 0), XMVectorSet(0, 1.0f, 0, 0));
}

CameraClass::~CameraClass()
{
}

void CameraClass::SetPosition(XMFLOAT3 Position)
{
	this->Position = Position;
}

void CameraClass::SetRotation(XMFLOAT3 NewRotation)
{
	this->Rotation = Rotation;
}

XMFLOAT3 CameraClass::GetPosition()
{
	return Position;
}

XMFLOAT3 CameraClass::GetRotation()
{
	return Rotation;
}

void CameraClass::SetView(XMMATRIX& view)
{
	ViewMatrix = view;
}

XMMATRIX CameraClass::GetView()
{
	return ViewMatrix;
}

void CameraClass::Render()
{
}
