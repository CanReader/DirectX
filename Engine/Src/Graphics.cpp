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

	Models.push_back(new ModelClass((LPCSTR)"Src/IMG/braynzar.jpg", XMFLOAT3(0, 0, 0)));
	Models.push_back(new ModelClass((LPCSTR)"Src/IMG/anan.jpg", XMFLOAT3(0, 0, 0)));

	Light = new PointLight(XMFLOAT4(0.1f,0.1f,0.1f,1),XMFLOAT4(1,1,1,1),XMFLOAT3(0,0,0),100.0f);

	if (!d3d->InitializeDirect3D(hWnd, Width, Height, FullScreen))
		return false;

	IterateModels(Models)
		if (!i->Initialize(d3d->GetDevice(), d3d->GetDeviceContext()))
			std::cout << "Failed to create a model";
	
	inp = new InputClass();

	if (!inp->InitDevices(hWnd, (HINSTANCE)GetModuleHandle(NULL)))
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

	delete Light;
	Light = 0;

	delete inp;
	inp = 0;
}

void Graphics::UpdateScene(float dt)
{
	RenderTestCube(*Models[1],0);
	RenderTestCube(*Models[0], 1);

	ModelClass* mo = Models[1];
	ModelClass* mt = Models[0];

	PointLight* pl = (PointLight*)Light;

	pl->SetPosition(XMFLOAT3(0,-1,-1));

		mo->RotateY(dt*10000);
	if (inp->IsPressed(DIK_S))
		mo->RotateY(-dt*100);

	if (inp->IsPressed(DIK_LALT) && inp->IsPressed(DIK_F4))
		PostQuitMessage(0);
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

std::cout << "----------------------------------------------World------------------------------------------------\n"
<< model.GetWorld()._11 << " " << model.GetWorld()._12 << " " << model.GetWorld()._13 << " " << model.GetWorld()._14 << "\n"
<< model.GetWorld()._21 << " " << model.GetWorld()._22 << " " << model.GetWorld()._23 << " " << model.GetWorld()._24 << "\n"
<< model.GetWorld()._31 << " " << model.GetWorld()._32 << " " << model.GetWorld()._33 << " " << model.GetWorld()._34 << "\n"
<< model.GetWorld()._41 << " " << model.GetWorld()._42 << " " << model.GetWorld()._43 << " " << model.GetWorld()._44 << "\n"
"\n------------------------------------------------------------END------------------------------\n\n\n\n\n\n\n\n";

}

void Graphics::SetFullscreen(bool FullScren)
{
	d3d->SetFullScreen(FullScren);
}
