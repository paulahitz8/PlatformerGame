#include "GuiCheckBox.h"
#include "App.h"
#include "Audio.h"

GuiCheckBox::GuiCheckBox(uint32 id, SDL_Rect bounds, const char* text) : GuiControl(GuiControlType::CHECKBOX, id)
{
	this->bounds = bounds;
	this->text = text;
	click = app->audio->LoadFx("Assets/Audio/Fx/Button.wav");

	timerCheckbox = 0;
	canClick = true;
	drawBasic = false;
	checked = false;
}

GuiCheckBox::~GuiCheckBox()
{}

bool GuiCheckBox::Update(Input* input, float dt, Render* render, bool drawBasic)
{
	this->drawBasic = drawBasic;

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
				if (canClick)
				{
					canClick = false;
					app->audio->PlayFx(click);
				}
				state = GuiControlState::PRESSED;
			}

			// If mouse button pressed -> Generate event!
			if (input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP)
			{
				canClick = true;
				if (timerCheckbox > 5)
				{
					checked = !checked;
					timerCheckbox = 0;
				}

				NotifyObserver();
			}
		}
		else state = GuiControlState::NORMAL;

		timerCheckbox++;
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
		render->DrawRectangle(bounds, 100, 100, 100, 255);

	} break;
	case GuiControlState::NORMAL:
	{
		if (drawBasic) render->DrawRectangle(bounds, 209, 37, 0, 255);
		else
		{
			if (checked)
			{
				render->DrawRectangle(bounds, 255, 255, 255, 255);
			}
			else render->DrawRectangle(bounds, 0, 255, 0, 0);
		}
	} break;
	case GuiControlState::FOCUSED: 
		if (drawBasic) render->DrawRectangle(bounds, 255, 193, 52, 255);
		else
		{
			if (checked)
			{
				render->DrawRectangle(bounds, 255, 255, 255, 255);
			}
			render->DrawRectangle(bounds, 255, 255, 255, 160);
		}
		break;
	case GuiControlState::PRESSED: 
		if (drawBasic) render->DrawRectangle(bounds, 186, 255, 37, 255);
		else
		{
			if (checked)
			{
				render->DrawRectangle(bounds, 255, 255, 255, 255);
			}
			render->DrawRectangle(bounds, 255, 255, 255, 255);
		}
		break;
	case GuiControlState::SELECTED: render->DrawRectangle(bounds, 0, 255, 0, 255);
		break;
	default:
		break;
	}

	return false;
}
