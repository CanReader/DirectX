#include "Graphics.h"

Graphics::Graphics() {}

Graphics::Graphics(const Graphics&) {}

Graphics::~Graphics() {}

bool Graphics::Initialize(HWND hWnd, int Width, int Height, bool FullScreen)
{
	this->Windowed = FullScreen;
	this->Width = Width;
	this->Height = Height;

	d3d = new Direct11();

	if (!d3d->InitializeDirect3D(hWnd, Width, Height, FullScreen))
		return false;

	Objects.push_back(new Cube());


	Iterate(Objects)
	{
		((Cube*)i)->SetDevice(d3d->GetDevice(),d3d->GetDeviceContext());
		i->Initialize();
	}
	
	DX_INFO("Direct3d is initialized!");
	OutputDebugString("Graphic class has been initialized!\n");
		
	return true;
}

void Graphics::Render()
{
	d3d->BeginScene(0.529f, 0.807f, 0.921f, 0);
	
	//Calculate delta time
	static float t = 0.0f;
	{
		static DWORD dwTimeStart = 0;
		DWORD dwTimeCur = GetTickCount();
		if (dwTimeStart == 0)
			dwTimeStart = dwTimeCur;
		t = (dwTimeCur - dwTimeStart) / 1000.0f;
	}

	Iterate(Objects)
		i->Render();

	UpdateScene(t);
	
	d3d->EndScene();
}

void Graphics::Shutdown()
{
	d3d->DeleteDirect3D();
	delete d3d;
	d3d = 0;
}

void Graphics::UpdateScene(float dt)
{
	Iterate(Objects)
		i->Update(dt);
}

void Graphics::SetFullscreen(bool FullScren)
{
	d3d->SetFullScreen(FullScren);
}
