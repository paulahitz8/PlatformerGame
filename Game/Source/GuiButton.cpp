#include "GuiButton.h"
#include "Render.h"
#include "App.h"
#include "Audio.h"

GuiButton::GuiButton(uint32 id, SDL_Rect bounds, const char* text, bool drawBasic, bool drawSettings, bool drawCredits) : GuiControl(GuiControlType::BUTTON, id)
{
	this->bounds = bounds;
	this->text = text;
	this->drawSettings = drawSettings;
	this->drawBasic = drawBasic;
	this->drawCredits = drawCredits;
	click = app->audio->LoadFx("Assets/Audio/Fx/Button.wav");
}

GuiButton::~GuiButton()
{

}

bool GuiButton::Update(Input* input, float dt, Render* render)
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
				NotifyObserver();
			}
		}
		else state = GuiControlState::NORMAL;
	}

	return false;
}

bool GuiButton::Draw(Render* render)
{
	// Draw the right button depending on state
	switch (state)
	{
	case GuiControlState::DISABLED: 
	{
		render->DrawRectangle(bounds, 100, 100, 100, 255);
		if (drawBasic)
		{

		}
		if (drawSettings)
		{

		}
		if (drawCredits)
		{

		}
		break;
	}
	case GuiControlState::NORMAL: render->DrawRectangle(bounds, 0, 255, 0, 0);
		break;
	case GuiControlState::FOCUSED: render->DrawRectangle(bounds, 255, 255, 255, 160);
		break;
	case GuiControlState::PRESSED: render->DrawRectangle(bounds, 255, 255, 255, 255);
		break;
	case GuiControlState::SELECTED: render->DrawRectangle(bounds, 0, 255, 0, 255);
		break;
	default:
		break;
	}

	return false;
}
