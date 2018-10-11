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
	aiDetachAllLogStreams();
	ilShutDown();
	return ret;
}

uint TextureLoader::LoadTexFromPath(const std::string & full_path)
{

	CONSOLELOG("Importing texture %s", full_path.c_str());
	ILuint image_id;
	ilGenImages(1, &image_id);
	ilBindImage(image_id);
	GLuint texture_id;

	ILboolean imageloaded = ilLoadImage(full_path.c_str());

	if (imageloaded) {
		ILinfo info;
		iluGetImageInfo(&info);

		if (info.Origin == IL_ORIGIN_UPPER_LEFT)
		{
			iluFlipImage();
		}

		ILboolean converted = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
		if (!converted)
		{
			CONSOLELOG("DevIL failed to convert image %s. Error: %s", full_path.c_str(), iluErrorString(ilGetError()));
		}
		int width = ilGetInteger(IL_IMAGE_WIDTH);
		int height = ilGetInteger(IL_IMAGE_HEIGHT);
		int format = ilGetInteger(IL_IMAGE_FORMAT);
		
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glGenTextures(1, &texture_id);
		glBindTexture(GL_TEXTURE_2D, texture_id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width , height,
			0, format, GL_UNSIGNED_BYTE, ilGetData());


		CONSOLELOG("Image width: %d", ilGetInteger(IL_IMAGE_WIDTH));
		CONSOLELOG("Image height: %d", ilGetInteger(IL_IMAGE_HEIGHT));

		
	}
	else
	{
		texture_id = 0;
		CONSOLELOG("DevIL: Unable to load image correctly. Texture_id set to %d", texture_id);
		return texture_id;
	}
	ilDeleteImages(1, &image_id);
	CONSOLELOG("Texture %s loaded correctly", full_path.c_str());

	return texture_id;
}

void TextureLoader::SwapTexture(const std::string & new_path)
{
	GLuint new_id = LoadTexFromPath(new_path);
	
	for (std::list<Mesh*>::iterator it = App->scene_intro->scene_objects.begin(); it != App->scene_intro->scene_objects.end(); it++)
	{
		(*it)->id_texture = new_id;
	}
}


int TextureLoader::getILversion() const
{
	return IL_VERSION;
}
