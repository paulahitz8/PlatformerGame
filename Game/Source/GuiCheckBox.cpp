#include "GuiCheckBox.h"

GuiCheckBox::GuiCheckBox(uint32 id, SDL_Rect bounds, const char* text) : GuiControl(GuiControlType::CHECKBOX, id)
{
	this->bounds = bounds;
	this->text = text;
}

GuiCheckBox::~GuiCheckBox()
{
}

bool GuiCheckBox::Update(Input* input, float dt, Render* render)
{
	if (state != GuiControlState::DISABLED)
	{

		input->GetMousePosition(mouseX, mouseY);
		mouseY += 500;

		// Check collision between mouse and button bounds
		if ((mouseX > bounds.x + render->camera.x) && (mouseX < (bounds.x + bounds.w) + render->camera.x) &&
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
				checked = !checked;
				NotifyObserver();
			}
		}
		else state = GuiControlState::NORMAL;
	}

	return false;
}

bool GuiCheckBox::Draw(Render* render)
{
	// Draw the right button depending on state
	switch (state)
	{
	case GuiControlState::DISABLED:
	{
		if (checked) render->DrawRectangle(bounds, 100, 100, 100, 255);
		else render->DrawRectangle(bounds, 100, 100, 100, 255);
	} break;
	case GuiControlState::NORMAL:
	{
		if (checked) render->DrawRectangle(bounds, 0, 255, 0, 255);
		else render->DrawRectangle(bounds, 0, 255, 0, 255);
	} break;
	case GuiControlState::FOCUSED: render->DrawRectangle(bounds, 255, 255, 0, 255);
		break;
	case GuiControlState::PRESSED: render->DrawRectangle(bounds, 0, 255, 255, 255);
		break;
	case GuiControlState::SELECTED: render->DrawRectangle(bounds, 0, 255, 0, 255);
		break;
	default:
		break;
	}

	return false;
}
