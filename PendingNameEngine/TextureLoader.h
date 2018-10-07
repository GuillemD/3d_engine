#ifndef __TEXTURE_LOADER_H__
#define __TEXTURE_LOADER_H__

#include "Module.h"
#include "Globals.h"


class TextureLoader : public Module
{
public:
	TextureLoader(bool start_enabled);
	~TextureLoader();

	bool Init();
	bool CleanUp();

	bool Import(const std::string &full_path);
	void LoadTexture();
	int getILversion() const;

};
#endif // !__TEXTURE_LOADER_H__
