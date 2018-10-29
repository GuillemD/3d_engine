#include "Application.h"
#include "TextureLoader.h"
#include "ComponentMaterial.h"
#include "Material.h"
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

ComponentMaterial* TextureLoader::LoadTexFromPath(const char* full_path)
{
	
	CONSOLELOG("Importing texture %s", full_path);

	ILuint image_id;
	GLuint tex_id;
	ILenum error;
	
	ilGenImages(1, &image_id);
	ilBindImage(image_id);
	
	ILboolean imageloaded = true;

	imageloaded = ilLoadImage(full_path);

	ComponentMaterial* cmp_material = new ComponentMaterial();
	cmp_material->SetActive(true);
	cmp_material->mat = new Material();

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
			
		}
		cmp_material->mat->texture_width = ilGetInteger(IL_IMAGE_WIDTH);
		cmp_material->mat->texture_height = ilGetInteger(IL_IMAGE_HEIGHT);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		glGenTextures(1, &tex_id);

		glBindTexture(GL_TEXTURE_2D, tex_id);

		cmp_material->mat->id_texture = tex_id;

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT),
			0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());


		CONSOLELOG("Image width: %d", ilGetInteger(IL_IMAGE_WIDTH));
		CONSOLELOG("Image height: %d", ilGetInteger(IL_IMAGE_HEIGHT));


		CONSOLELOG("Texture %s loaded correctly", full_path);


	}
	else
	{
		tex_id = 0;
		error = ilGetError();
		CONSOLELOG("DevIL: Unable to load image correctly. Error: %s. Texture_id set to %d", iluErrorString(error), tex_id);
		
	}

	return cmp_material;
	
}


int TextureLoader::getILversion() const
{
	return IL_VERSION;
}
