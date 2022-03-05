#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <Windows.h>

#include "Direct11.h"
#include "CameraClass.h"
#include "ModelClass.h"

#define IterateModels(Models) for(auto& i : Models)

class Graphics
{
	//Variables
public:
	bool Windowed = false;
	bool vsync = false;
	
	float Screen_Depth = 1000.0f;
	float Screen_Far = 0.1f;

	int Width = 0;
	int Height = 0;
private:
	
	//Methods
public:
	Graphics();
	Graphics(const Graphics&);
	~Graphics();

	bool Initialize(HWND,int,int,bool);
	void Render();
	void Shutdown();

	void UpdateScene(float dt);

	void RenderTestCube(ModelClass&,int);

	void SetFullscreen(bool);

private:

	std::vector<ModelClass*> Models;

	//Classes
private:
	Direct11* d3d = nullptr;
	CameraClass* Camera;

	LightClass* Light;
};

#endif