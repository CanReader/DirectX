#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <Windows.h>

#include "Direct11.h"
#include "../CoreGame/Object.h"
#include "../CoreGame/Models/Cube.h"


#define Iterate(Models) for(auto& i : Models)

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

	void SetFullscreen(bool);

private:
	std::vector<Object*> Objects;

	//Classes
private:
	Direct11* d3d = nullptr;

};

#endif