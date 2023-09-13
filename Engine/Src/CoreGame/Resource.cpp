/*
#include "Resource.h"
#include <filesystem>

Resource::Resource(const wchar_t* file_path, ResourceManager* ResManager): filePath(file_path), manager(ResManager){}

Resource::~Resource()
{
}

const std::wstring Resource::getPath()
{
	return filePath;
}

ResourceManager::ResourceManager(){}

ResourceManager::~ResourceManager(){}

Resource* ResourceManager::CreateResourceFromFile(wchar_t* FilePath)
{
	std::wstring fullpath = std::filesystem::absolute(FilePath);

	auto it = m_Resources.find(fullpath);

	if (it != m_Resources.end())
		return it->second;

	Resource* rawResource = CreateResourceFromFileConcrete(FilePath);

	if (rawResource)
	{
		Resource* res(rawResource);
		m_Resources[FilePath] = rawResource;
		return rawResource;
	}

	return nullptr;
}

*/