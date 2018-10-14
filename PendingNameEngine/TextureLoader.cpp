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
	current = "";
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

uint TextureLoader::LoadTexFromPath(const char* full_path)
{
	
	CONSOLELOG("Importing texture %s", full_path);

	ILuint image_id;
	GLuint tex_id;
	ILenum error;
	
	ilGenImages(1, &image_id);
	ilBindImage(image_id);
	
	ILboolean imageloaded = true;

	imageloaded = ilLoadImage(full_path);

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
			tex_id = 0;
			CONSOLELOG("DevIL failed to convert image %s. Error: %s", full_path, iluErrorString(ilGetError()));
			return tex_id;
		}
		int width = ilGetInteger(IL_IMAGE_WIDTH);
		int height = ilGetInteger(IL_IMAGE_HEIGHT);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		glGenTextures(1, &tex_id);

		glBindTexture(GL_TEXTURE_2D, tex_id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
			0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());


		CONSOLELOG("Image width: %d", ilGetInteger(IL_IMAGE_WIDTH));
		CONSOLELOG("Image height: %d", ilGetInteger(IL_IMAGE_HEIGHT));


		CONSOLELOG("Texture %s loaded correctly", full_path);
		

		for (std::list<Mesh*>::iterator it = App->scene_loader->scene_objects.begin(); it != App->scene_loader->scene_objects.end(); it++)
		{
			(*it)->id_texture = tex_id;
		}

	}
	else
	{
		tex_id = 0;
		error = ilGetError();
		CONSOLELOG("DevIL: Unable to load image correctly. Error: %s. Texture_id set to %d", iluErrorString(error), tex_id);
		return tex_id;
	}

	return tex_id;
	
}

/*void TextureLoader::SwapTexture(const char* _new_path)
{
	if (current != new_path)
	{
		GLuint new_id = LoadTexFromPath(_new_path);

		for (std::list<Mesh*>::iterator it = App->scene_loader->scene_objects.begin(); it != App->scene_loader->scene_objects.end(); it++)
		{
			(*it)->id_texture = new_id;
		}

		current = new_path;
		new_path = "";
	}
	else {
		CONSOLELOG("Texture already in use");
	}
	
}*/


int TextureLoader::getILversion() const
{
	return IL_VERSION;
}
