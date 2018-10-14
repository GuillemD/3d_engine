#ifndef __TEXTURE_LOADER_H__
#define __TEXTURE_LOADER_H__

#include "Module.h"
#include "Globals.h"

#include <list>

class TextureLoader : public Module
{
public:
	TextureLoader(bool start_enabled);
	~TextureLoader();

	bool Init();
	bool CleanUp();

	uint LoadTexFromPath(const char* full_path);
	void SwapTexture(const char* _new_path);

	int getILversion() const;

	const char* current = "";
	const char* new_path = "";
	

};
#endif // !__TEXTURE_LOADER_H__
