#ifndef __GUIBUTTON_H__
#define __GUIBUTTON_H__

#include "GuiControl.h"

#include "Point.h"
#include "SString.h"

class GuiButton : public GuiControl
{
public:

	GuiButton(uint32 id, SDL_Rect bounds, const char* text, bool drawBasic, bool drawSettings, bool drawCredits);
	virtual ~GuiButton();

	bool Update(Input* input, float dt, Render* render);
	bool Draw(Render* render);

	bool drawCredits = false;
	bool drawSettings = false;
	bool drawBasic = false;

	int mouseX, mouseY;
	unsigned int click;
	bool canClick = true;

private:

	// Gui Button specific properties
	// Maybe some animation properties for state change?
};

#endif // __GUIBUTTON_H__
