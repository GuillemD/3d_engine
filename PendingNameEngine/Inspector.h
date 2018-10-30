#ifndef _INSPECTOR_H_
#define _INSPECTOR_H_
#include "Panel.h"
#include "ImGui\imgui.h"

class Inspector : public Panel {
public:
	Inspector();
	~Inspector();

	void ShowElement();

};


#endif // !_INSPECTOR_H_

