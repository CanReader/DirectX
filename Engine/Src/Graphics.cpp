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
	Camera = new CameraClass();
	inp = new InputClass();
	Models = std::vector<ModelClass*>();

	Models.push_back(new ModelClass((LPCSTR)"Src/IMG/anan.jpg"));

	if (!d3d->InitializeDirect3D(hWnd, Width, Height, FullScreen))
		return false;
	
	if (!inp->InitDevices(hWnd, (HINSTANCE)GetModuleHandle(NULL)))
		return false;
	
	Models[0]->Initialize(d3d->GetDevice(),d3d->GetDeviceContext());

	DX_INFO("Direct3d is initialized!");

	return true;
}

void Graphics::Render()
{
	d3d->BeginScene(0.529f, 0.807f, 0.921f, 0);
	
	static float t = 0.0f;
	{
		static DWORD dwTimeStart = 0;
		DWORD dwTimeCur = GetTickCount();
		if (dwTimeStart == 0)
			dwTimeStart = dwTimeCur;
		t = (dwTimeCur - dwTimeStart) / 1000.0f;
	}

	XMMATRIX matrices[3] =
	{
		XMMatrixIdentity(),
		Camera->GetView(),
		d3d->GetProjection()
	};

	Models[0]->Render(matrices);

	UpdateScene(t);
	
	d3d->EndScene();
}

void Graphics::Shutdown()
{
	d3d->DeleteDirect3D();
	delete d3d;
	d3d = 0;

	delete Camera;
	Camera = 0;

	IterateModels(Models)
		delete i;

	delete Light;
	Light = 0;

	delete inp;
	inp = 0;
}

void Graphics::UpdateScene(float dt)
{
}

void Graphics::RenderTestCube(ModelClass& model, int Dir)
{
}

void Graphics::SetFullscreen(bool FullScren)
{
	d3d->SetFullScreen(FullScren);
}
