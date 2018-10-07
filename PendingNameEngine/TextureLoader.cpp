#include "Application.h"
#include "TextureLoader.h"
#include "Globals.h"
#include "OpenGL.h"
#include "DevIL/include/il.h"
#include "DevIL/include/ilut.h"

#pragma comment( lib, "DevIL/libx86/DevIL.lib" )
#pragma comment( lib, "DevIL/libx86/ILU.lib" )
#pragma comment( lib, "DevIL/libx86/ILUT.lib" )

TextureLoader::TextureLoader(bool start_enabled)
{
	ilInit();
	iluInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);
}

TextureLoader::~TextureLoader()
{
	ilShutDown();
}

bool TextureLoader::Init()
{
	bool ret = true;

	LOG("Init DevIL");
	CONSOLELOG("Init DevIL");

	return ret;
}

bool TextureLoader::CleanUp()
{
	bool ret = true;
	LOG("Cleaning textures up");
	return ret;
}

bool TextureLoader::Import(const std::string & full_path)
{
	return false;
}

void TextureLoader::LoadTexture()
{
}

int TextureLoader::getILversion() const
{
	return IL_VERSION;
}
