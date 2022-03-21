#include "CameraClass.h"

CameraClass::CameraClass() : Position(XMVectorSet(0,0,0,0) ),
 Target(XMVectorSet(0, 0, 0, 0)), Rotation{XMFLOAT3(0,0,0)}
{
ViewMatrix = XMMatrixLookAtLH(Position, Target, XMVectorSet(0, 1.0f, 0, 0));
}

CameraClass::~CameraClass()
{
}

void CameraClass::SetPosition(XMVECTOR Position)
{
	this->Position = Position;
}

void CameraClass::SetRotation(XMFLOAT3 NewRotation)
{
	this->Rotation = Rotation;
}

XMVECTOR CameraClass::GetPosition()
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

void CameraClass::Update()
{
}

void CameraClass::Render()
{
}
