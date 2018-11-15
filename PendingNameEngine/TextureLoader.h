#ifndef __TEXTURE_LOADER_H__
#define __TEXTURE_LOADER_H__

#include "Module.h"
#include "Globals.h"

#include <list>
class ComponentMaterial;
class Material;

class TextureLoader : public Module
{
public:
	TextureLoader(bool start_enabled);
	~TextureLoader();

	bool Init();
	bool CleanUp();

	void SaveDDS();
	ComponentMaterial* LoadTexFromPath(const char* full_path);
	Material* LoadMaterial(const char* full_path);
	
	int getILversion() const;
	std::string GetExtension(const char* path);
	std::string GetPath(const char* path);
private:

	uint num_tex = 0;


};
#endif // !__TEXTURE_LOADER_H__
