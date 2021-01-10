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
	bool drawBasic = false;
	bool checked = false;

private:

	int timerCheckbox = 0;
};

#endif // __GUICHECKBOX_H__
