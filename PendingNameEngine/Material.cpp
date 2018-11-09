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

int Material::GetFormat() const
{
	return texture_format;
}

const char * Material::GetName() const
{
	return name;
}

std::string Material::GetPath() const
{
	return path;
}

void Material::SetID(uint id)
{
	id_texture = id;
}

void Material::SetWidth(uint w)
{
	texture_width = w;
}

void Material::SetHeight(uint h)
{
	texture_height = h;
}

void Material::SetFormat(const int & format)
{
	texture_format = format;
}

void Material::SetName(const char * n)
{
	name = n;
}
