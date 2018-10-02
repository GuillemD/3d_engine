#ifndef __IMPORTER_H__
#define __IMPORTER_H__

#include "Globals.h"
#include "Assimp.h"
#include "OpenGL.h"

class Importer 
{
public:
	Importer();
	virtual ~Importer();

	bool Init();
	bool CleanUp();
	bool Import();
};

#endif // !__IMPORTER_H__

