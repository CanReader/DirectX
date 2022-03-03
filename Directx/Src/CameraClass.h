#ifndef CAMERACLASS_H_
#define CAMERACLASS_H_



#include <d3dx9math.h>
#include <xnamath.h>

class CameraClass
{
public:
	CameraClass();
	CameraClass(const CameraClass&);
	~CameraClass();

	void SetPosition(XMFLOAT3);
	void SetRotation(XMFLOAT3);

	XMFLOAT3 GetPosition();
	XMFLOAT3 GetRotation();

	void SetView(XMMATRIX&);
	XMMATRIX GetView();

	void Render();
private:
	XMFLOAT3 Position;
	XMFLOAT3 Rotation;
	XMMATRIX ViewMatrix;

public:

private:
};


#endif // !CAMERACLASS_H_