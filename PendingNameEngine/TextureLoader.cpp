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

	App->CreateNewDirectory("Assets\\Textures");
	App->CreateNewDirectory("Library\\Textures");
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



void TextureLoader::SaveDDS()
{
	ILuint		size;
	ILubyte*	data;

	ilSetInteger(IL_DXTC_FORMAT, IL_DXT5);

	size = ilSaveL(IL_DDS, NULL, 0);
	if (size > 0)
	{
		data = new ILubyte[size];
		if (ilSaveL(IL_DDS, data, size) > 0)
		{
			char file[69];
			sprintf_s(file, "Library\\Textures\\Texture_%d.dds", num_tex++);
			FILE* tex_file = fopen(file, "wb");
			fwrite(data, sizeof(ILubyte), size, tex_file);
			fclose(tex_file);


		}
	}
}

ComponentMaterial* TextureLoader::LoadTexFromPath(const char* full_path)
{
	
	CONSOLELOG("Importing texture %s", full_path);

	ILuint image_id;
	GLuint tex_id;
	ILenum error;
	
	ilGenImages(1, &image_id);
	ilBindImage(image_id);
	
	ComponentMaterial* cmp_material = new ComponentMaterial();
	cmp_material->SetActive(true);
	cmp_material->mat = new Material();

	

	if (ilLoad(IL_TYPE_UNKNOWN, full_path)) {
		ILinfo info;
		iluGetImageInfo(&info);

		if (info.Origin == IL_ORIGIN_UPPER_LEFT)
		{
			iluFlipImage();
		}

		ILboolean converted = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);
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

		ilDeleteImage(ilGetInteger(IL_ACTIVE_IMAGE));


	}
	else
	{
		tex_id = 0;
		error = ilGetError();
		CONSOLELOG("DevIL: Unable to load image correctly. Error: %s. Texture_id set to %d", iluErrorString(error), tex_id);
		
	}

	return cmp_material;
	
}

Material * TextureLoader::LoadMaterial(const char * full_path)
{
	CONSOLELOG("Importing texture %s", full_path);

	ILuint image_id;
	GLuint tex_id;
	ILenum error;

	ilGenImages(1, &image_id);
	ilBindImage(image_id);

	Material* m = new Material();

	if (ilLoad(IL_TYPE_UNKNOWN, full_path)) {
		ILinfo info;
		iluGetImageInfo(&info);

		if (info.Origin == IL_ORIGIN_UPPER_LEFT)
		{
			iluFlipImage();
		}

		ILboolean converted = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);
		if (!converted)
		{
			tex_id = 0;
			CONSOLELOG("DevIL failed to convert image %s. Error: %s", full_path, iluErrorString(ilGetError()));

		}
		m->texture_width = ilGetInteger(IL_IMAGE_WIDTH);
		m->texture_height = ilGetInteger(IL_IMAGE_HEIGHT);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		glGenTextures(1, &tex_id);

		glBindTexture(GL_TEXTURE_2D, tex_id);

		m->id_texture = tex_id;
		m->ext = GetExtension(full_path);
		m->path = GetPath(full_path);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT),
			0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());


		CONSOLELOG("Image width: %d", ilGetInteger(IL_IMAGE_WIDTH));
		CONSOLELOG("Image height: %d", ilGetInteger(IL_IMAGE_HEIGHT));

		SaveDDS();

		CONSOLELOG("Texture %s loaded correctly", full_path);

		ilDeleteImage(ilGetInteger(IL_ACTIVE_IMAGE));


	}
	else
	{
		tex_id = 0;
		error = ilGetError();
		CONSOLELOG("DevIL: Unable to load image correctly. Error: %s. Texture_id set to %d", iluErrorString(error), tex_id);

	}

	return m;
}


int TextureLoader::getILversion() const
{
	return IL_VERSION;
}

std::string TextureLoader::GetExtension(const char * path)
{
	std::string _path = path;
	std::string ext;

	uint dot = _path.find_last_of(".");
	ext = _path.substr(dot + 1);

	return ext;
}

std::string TextureLoader::GetPath(const char * path)
{
	std::string _path = path;
	std::string rel_path;

	uint slash = _path.find_last_of("\\");
	rel_path = _path.substr(0, slash + 1);

	return rel_path;
}
