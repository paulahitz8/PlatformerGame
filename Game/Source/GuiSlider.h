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

	bool Update(Input* input, float dt, Render* render);
	bool Draw(Render* render);

	int volume;
	int unit;
	int mouseX, mouseY;

private:

	// GuiSlider specific properties
	// Maybe some animation properties for state change?
	SDL_Rect slider;
	int value;

	int minValue;
	int maxValue;

	bool canClick = true;
	unsigned int click;
};

#endif // __GUISLIDER_H__
