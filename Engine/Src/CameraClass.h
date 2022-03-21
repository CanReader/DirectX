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

	void SetPosition(XMVECTOR);
	void SetRotation(XMFLOAT3);

	XMVECTOR GetPosition();
	XMFLOAT3 GetRotation();

	void SetView(XMMATRIX&);
	XMMATRIX GetView();

	void Update();

	void Render();
private:
	XMVECTOR Target;
	XMVECTOR Up;

	XMVECTOR Position;
	XMFLOAT3 Rotation;
	XMMATRIX ViewMatrix;

public:

private:
};


#endif // !CAMERACLASS_H_