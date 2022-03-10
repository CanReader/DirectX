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

	Models = std::vector<ModelClass*>();

	Models.push_back(new ModelClass((LPCSTR)"Src/IMG/braynzar.jpg", XMFLOAT3(-0.5, 0, 0)));
	Models.push_back(new ModelClass((LPCSTR)"Src/IMG/anan.jpg", XMFLOAT3(0.5, 0, 0)));

	Light = new PointLight(XMFLOAT3(0.25f,0.5f,-1.0f), XMFLOAT4(0.2f,0.2f,0.2f, 1.0f), XMFLOAT4(1, 1, 1, 1));

	if (!d3d->InitializeDirect3D(hWnd, Width, Height, FullScreen))
		return false;

	IterateModels(Models)
		if (!i->Initialize(d3d->GetDevice(), d3d->GetDeviceContext()))
			return false;

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
}

void Graphics::UpdateScene(float dt)
{
	RenderTestCube(*Models[1],0);
	RenderTestCube(*Models[0], 1);

	ModelClass* mo = Models[1];
	ModelClass* mt = Models[0];

	Light->SetAmbient(XMFLOAT4(0.001f,0.001f,0.001f,1));
	Light->SetDirection(XMFLOAT3(0.25f,sin(dt),-1));

}

void Graphics::RenderTestCube(ModelClass& model, int Dir)
{
	XMMATRIX Matrices[3] =
	{
		model.GetWorld(),
		Camera->GetView(),
		d3d->GetProjection()
	};

	model.SetLighting(*Light);
	model.SetMatrices(Matrices);
	model.Render();
}

void Graphics::SetFullscreen(bool FullScren)
{
	d3d->SetFullScreen(FullScren);
}
