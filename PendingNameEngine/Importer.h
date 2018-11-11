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
	void LoadMesh(const aiScene* _scene, const aiNode * node, GameObject* parent_go, const std::vector<Material*>& mats);

	void BinarySave(Mesh* mesh);
	void* BinaryLoad(const char* file_path);

public:
	std::string tex_path;
private:
	uint num_mesh = 0;
};

#endif // !__IMPORTER_H__

