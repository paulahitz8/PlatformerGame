#include "GuiSlider.h"


GuiSlider::GuiSlider(uint32 id, SDL_Rect bounds, const char* text) : GuiControl(GuiControlType::SLIDER, id)
{
	this->bounds = bounds;
	this->text = text;
}

GuiSlider::~GuiSlider()
{
}

bool GuiSlider::Update(Input* input, float dt, Render* render)
{
	//float tmpValue = (float)maxValue / (float)(limits.w - bounds.w);
	//value = (bounds.x - limits.x) * tmpValue;

	if (state != GuiControlState::DISABLED)
	{

		input->GetMousePosition(mouseX, mouseY);
		mouseY += 500;

		int motionX = 0, motionY = 0;
		input->GetMouseMotion(motionX, motionY);

		unit = 319 / 100;
		volume = (mouseX - 493) / unit;
		value = round(value);

		bounds.x += render->camera.x;

		// Check collision between mouse and button bounds
		if ((mouseX > bounds.x) && (mouseX < (bounds.x + bounds.w)) &&
			(mouseY > bounds.y) && (mouseY < (bounds.y + bounds.h)))
		{
			state = GuiControlState::FOCUSED;

			if (input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
			{
				state = GuiControlState::PRESSED;
			}

			// If mouse button pressed -> Generate event!
			if (input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP)
			{
				NotifyObserver();
			}
		}
		else if (input->GetMouseButtonDown(SDL_BUTTON_LEFT) != KeyState::KEY_REPEAT)
		{
			state = GuiControlState::NORMAL;
		}

		if (state == GuiControlState::PRESSED && motionX != 0)
		{
			bounds.x = mouseX - (bounds.w / 2);
			NotifyObserver();
		}

		//if (bounds.x< 463)
		//{
		//	bounds.x = 463;
		//}
		//if (bounds.x>= 782 )
		//{
		//	bounds.x = 782;
		//}

		if (input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP)
		{
			state = GuiControlState::NORMAL;
		}

	}

	return false;
}

bool GuiSlider::Draw(Render* render)
{
	// Draw the right button depending on state
	switch (state)
	{
	case GuiControlState::DISABLED: render->DrawRectangle(bounds, 100, 100, 100, 255);
		break;
	case GuiControlState::NORMAL: render->DrawRectangle(bounds, 255, 255, 255, 255);
		break;
	case GuiControlState::FOCUSED: render->DrawRectangle(bounds, 255, 255, 255, 150);
		break;
	case GuiControlState::PRESSED: render->DrawRectangle(bounds, 255, 255, 255, 200);
		break;
	case GuiControlState::SELECTED: render->DrawRectangle(bounds, 0, 255, 0, 255);
		break;
	default:
		break;
	}

	return false;
}
