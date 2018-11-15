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

	std::string GetPath() const;

	void SetID(uint id);
	void SetWidth(uint w);
	void SetHeight(uint h);
	void SetFormat(const int& format);

	

public:

	uint id_texture = 0;

	uint texture_width = 0;
	uint texture_height = 0;

	int texture_format = 0;
	
	std::string path = "";
	std::string ext = "";
};
#endif // !_MATERIAL_H_
