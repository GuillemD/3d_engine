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

	CONSOLELOG("Importing png %s", full_path.c_str());
	ILuint images;
	ilGenImages(1, &images);
	ilBindImage(images);

	ILboolean imageloaded=ilLoadImage(full_path.c_str());
	GLuint textures;
	


	if (imageloaded) {
		ILinfo info;
		iluGetImageInfo(&info);

		if (info.Origin == IL_ORIGIN_UPPER_LEFT)
		{
			iluFlipImage();
		}

		ILboolean converted = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
		
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glGenTextures(1, &textures);
		glBindTexture(GL_TEXTURE_2D, textures);

		for (std::list<Mesh*>::iterator it = App->scene_intro->scene_objects.begin(); it != App->scene_intro->scene_objects.end(); it++)
		{
			(*it)->data.id_texture=textures;
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,info.Width , info.Height,
			0, GL_RGB, GL_UNSIGNED_BYTE, ilGetData());


		CONSOLELOG("%d", ilGetInteger(IL_IMAGE_WIDTH));
		CONSOLELOG("%d", ilGetInteger(IL_IMAGE_HEIGHT));
	}
	CONSOLELOG("Png %s loaded correctly", full_path.c_str());
	return false;
}

void TextureLoader::LoadTexture()
{
}

int TextureLoader::getILversion() const
{
	return IL_VERSION;
}
