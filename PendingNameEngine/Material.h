#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "Globals.h"

class Material {
public:

	Material();
	~Material();

	uint GetID()const;
	uint GetWidth() const;
	uint GetHeight() const;

public:

	uint id_texture = 0;

	uint texture_width = 0;
	uint texture_height = 0;
};
#endif // !_MATERIAL_H_
