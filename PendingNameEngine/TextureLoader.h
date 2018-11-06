#ifndef __TEXTURE_LOADER_H__
#define __TEXTURE_LOADER_H__

#include "Module.h"
#include "Globals.h"

#include <list>
class ComponentMaterial;

class TextureLoader : public Module
{
public:
	TextureLoader(bool start_enabled);
	~TextureLoader();

	bool Init();
	bool CleanUp();

	ComponentMaterial* LoadTexFromPath(const char* full_path);
	//void SwapTexture(const char* _new_path);

	int getILversion() const;


};
#endif // !__TEXTURE_LOADER_H__
