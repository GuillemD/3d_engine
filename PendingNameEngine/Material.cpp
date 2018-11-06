#include "Material.h"

Material::Material()
{
}

Material::~Material()
{
}

uint Material::GetID() const
{
	return id_texture;
}

uint Material::GetWidth() const
{
	return texture_width;
}

uint Material::GetHeight() const
{
	return texture_height;
}
