#include "Interactive.h"
#include "p2Log.h"
#include "j1Fonts.h"
#include "j1Map.h"
#include "j1Render.h"
#include "j1Input.h"
#include "Window.h"
#include "j1Sceneswitch.h"
#include "j1Scene.h"
#include "j1IntroScene.h"


Interactive::Interactive()
{
}


Interactive::Interactive(SDL_Rect& pos, iPoint Interactiverelativepos, InteractiveType type, j1Module* callback) :  callback(callback), Interactiverelativepos(Interactiverelativepos)
{
	this->type = type;
	collider.x = pos.x + Interactiverelativepos.x;
	collider.y = pos.y + Interactiverelativepos.y;
	collider.w = pos.w;
	collider.h = pos.h;
}


Interactive::~Interactive()
{
}

bool Interactive::InteractivePreUpdate()
{
	bool ret = true;

	MoveCollider();
	if (!Unavalible)
	{
		SDL_Point mousePosition;

		App->input->GetMousePosition(mousePosition.x, mousePosition.y);

		if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN && hasFocus)
			ret = callback->OnEvent(this, EventTypes::PRESSED_ENTER);

		if (App->input->GetKey(SDL_SCANCODE_TAB) == KEY_DOWN)
			ret = callback->OnEvent(this, EventTypes::PRESSED_TAB);

		if (SDL_PointInRect(&mousePosition, &collider))
		{
			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN && ret)
				ret = callback->OnEvent(this, EventTypes::LEFT_MOUSE_PRESSED);
			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP && ret)
				ret = callback->OnEvent(this, EventTypes::LEFT_MOUSE_RELEASED);
			if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_DOWN && ret)
				ret = callback->OnEvent(this, EventTypes::RIGHT_MOUSE_PRESSED);
			if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_UP && ret)
				ret = callback->OnEvent(this, EventTypes::RIGHT_MOUSE_RELEASED);
			if (!isMouseInside && ret)
				ret = callback->OnEvent(this, EventTypes::MOUSE_HOVER_IN);

			isMouseInside = true;
		}
		else
		{
			if (isMouseInside && ret)
				ret = callback->OnEvent(this, EventTypes::MOUSE_HOVER_OUT);

			isMouseInside = false;
		}
	}

	else
	{
		if (isMouseInside && ret)
			ret = callback->OnEvent(this, EventTypes::MOUSE_HOVER_OUT);
		else
			ret = callback->OnEvent(this, EventTypes::DEFAULT_TYPE);
		isMouseInside = false;
	}

	return ret;
}

bool Interactive::InteractivePostUpdate()
{

	return true;
}

bool Interactive::InteractiveDraw(float dt)
{
	return true;
}

bool Interactive::InteractiveCleanUp()
{
	callback = nullptr;
	return true;
}

void Interactive::MoveCollider()
{
	if (!In_window)
	{
		collider.x = position.x + Interactiverelativepos.x;
		collider.y = position.y + Interactiverelativepos.y;
	}

	else if (In_window)
	{
		collider.x = position.x + Interactiverelativepos.x + winElement->relativePosition.x;
		collider.y = position.y + Interactiverelativepos.y + winElement->relativePosition.y;
	}
}


bool Interactive::OnEvent()
{
	switch (type)
	{
	case DEFAULT:
		break;
	case QUIT:
		return false;
		break;
	case CLOSE_WINDOW:
		window->active = false;
		break;
	case CONTINUE:
		App->sceneswitch->SwitchScene(App->scene, App->introscene);
		break;
	case NEWGAME:
		App->sceneswitch->SwitchScene(App->scene, App->introscene);
		break;
	case OPEN_SETTINGS:
		break;
	case OPEN_CREDITS:
		break;
	default:
		break;
	}
	return true;
}