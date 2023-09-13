/*
#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include <string>
#include <map>

class ResourceManager
{
public:
	ResourceManager();
	virtual ~ResourceManager();

	Resource* CreateResourceFromFile(wchar_t* FilePath);
protected:
	virtual Resource* CreateResourceFromFileConcrete(wchar_t* FilePath) = 0;

	std::map<std::wstring, Resource*> m_Resources;
};

class Resource
{
public:
	Resource(const wchar_t* file_path, ResourceManager* manager);
	virtual ~Resource();

	const std::wstring getPath();
protected:
	const std::wstring filePath;
	ResourceManager* manager;

};


#endif // !_RESOURCE_H_
*/