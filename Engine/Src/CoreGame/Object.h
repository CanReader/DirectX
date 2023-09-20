#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "Resource.h"
#include <Windows.h>
#include <d3d11.h>
#include <xnamath.h>

class Object
{
public:
	Object();

	virtual bool Initialize() = 0;
	virtual void Render() = 0;
	virtual void Update(float t) = 0;

	const char* GetName();
protected:
	char* Name;
};


#endif // !_OBJECT_H_