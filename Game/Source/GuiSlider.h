#ifndef __GUISLIDER_H__
#define __GUISLIDER_H__

#include "GuiControl.h"

#include "Point.h"
#include "SString.h"

class GuiSlider : public GuiControl
{
public:

	GuiSlider(uint32 id, SDL_Rect bounds, const char* text);
	virtual ~GuiSlider();

	bool Update(Input* input, float dt, Render* render, bool drawBasic);
	bool Draw(Render* render);

	int volume;
	int unit;
	int mouseX, mouseY;

	bool drawBasic = false;

private:

	SDL_Rect slider;
	int value;

	bool canClick = true;
	unsigned int click;
};

#endif // __GUISLIDER_H__