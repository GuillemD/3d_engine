#ifndef __IMPORTER_H__
#define __IMPORTER_H__


#include "Module.h"
#include "Assimp.h"
#include "OpenGL.h"



class Importer : public Module
{
public:
	Importer(bool start_enabled);
	~Importer();

	bool Init(rapidjson::Document& document);
	bool CleanUp();

	bool Import(const std::string &full_path);
	void LoadMesh(const aiScene* _scene, const aiMesh* mesh);


};

#endif // !__IMPORTER_H__

