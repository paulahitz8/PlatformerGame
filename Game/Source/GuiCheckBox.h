#ifndef __GUICHECKBOX_H__
#define __GUICHECKBOX_H__

#include "GuiControl.h"

#include "Point.h"
#include "SString.h"

class GuiCheckBox : public GuiControl
{
public:

	GuiCheckBox(uint32 id, SDL_Rect bounds, const char* text);
	virtual ~GuiCheckBox();

	bool Update(Input* input, float dt, Render* render, bool drawBasic);
	bool Draw(Render* render);
	int mouseX, mouseY;

	unsigned int click;
	bool canClick = true;
	bool drawBasic;
	bool checked;

private:

	// GuiCheckBox specific properties
	// Maybe some animation properties for state change?
	//bool checked;

	SDL_Rect checkSeen = { 754, 954, 22, 22 };
};

#endif // __GUICHECKBOX_H__
