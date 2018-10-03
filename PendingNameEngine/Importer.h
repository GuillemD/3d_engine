#ifndef __IMPORTER_H__
#define __IMPORTER_H__


#include "Assimp.h"
#include "OpenGL.h"


class Importer 
{
public:
	Importer();
	virtual ~Importer();

	bool Init();
	bool CleanUp();
	bool Import(const char* full_path);
	void LoadMesh(const aiMesh* mesh);

private:

};

#endif // !__IMPORTER_H__

