#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "Globals.h"
#include <string>

class Material {
public:

	Material();
	virtual ~Material();

	uint GetID()const;
	uint GetWidth() const;
	uint GetHeight() const;
	int GetFormat() const;
	const char* GetName() const;
	std::string GetPath() const;

	void SetID(uint id);
	void SetWidth(uint w);
	void SetHeight(uint h);
	void SetFormat(const int& format);
	void SetName(const char* n);
	

public:

	uint id_texture = 0;

	uint texture_width = 0;
	uint texture_height = 0;

	int texture_format = 0;
	const char* name = nullptr;
	std::string path;
};
#endif // !_MATERIAL_H_
