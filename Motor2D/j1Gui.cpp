#include "p2Defs.h"
#include "p2Log.h"
#include "p2Animation.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "j1IntroScene.h"
#include "j1Scene.h"
#include "Window.h"
#include "UIElement.h"
#include "Label.h"
#include "Image.h"
#include "j1Audio.h"
#include "Interactive.h"
#include "InteractiveImage.h"
#include "InteractiveLabel.h"
#include "InteractiveLabelledImage.h"
#include "LabelledImage.h"
#include "InheritedImage.h"
#include "InheritedInteractive.h"
#include "InheritedLabel.h"
#include "Scrollbar.h"
#include "LifeBar.h"

j1Gui::j1Gui() : j1Module()
{
	name = "gui";
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");

	buttonFX = conf.child("buttonFX").attribute("source").as_string("");
	atlas_file_name = conf.child("atlas").attribute("file").as_string("");
	background = conf.child("background").attribute("file").as_string("");

	return true;
}

// Called before the first frame
bool j1Gui::Start()
{
	App->audio->LoadFx(buttonFX.c_str());
	//atlas = App->tex->Load(atlas_file_name.GetString());
	App->input->GetMousePosition(mouseLastFrame.x, mouseLastFrame.y);

	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	for(std::list<UIElement*>::iterator it_e = elements.begin(); it_e != elements.end(); it_e++)
	{
		if ((*it_e)->active && (!(*it_e)->In_window || (*it_e)->window->active))
			if (!(*it_e)->PreUpdate()) return false;
	}

	for (std::list<Window*>::iterator it_w = window_list.begin(); it_w != window_list.end(); it_w++)
	{
		if ((*it_w)->active)
			if (!(*it_w)->PreUpdate()) return false;
	}

	return true;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
	if (App->input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN)
		debug = !debug;
	App->input->GetMousePosition(mouseLastFrame.x, mouseLastFrame.y);

	for (std::list<UIElement*>::iterator it = elements.begin(); it != elements.end(); it++)
	{
		if ((*it)->active && (!(*it)->In_window || (*it)->window->active))
			if (!(*it)->PostUpdate()) return false;
	}
	
	return true;
}

bool j1Gui::Draw(float dt)
{
	for (std::list<UIElement*>::iterator it = elements.begin(); it != elements.end(); it++)
	{
		if ((*it)->active && (!(*it)->In_window || (*it)->window->active))
		{
			(*it)->Draw(dt);

			if (debug) 
			{
				if (!(*it)->In_window) App->render->DrawQuad((*it)->position, Red, true, false);
				else
				{
					SDL_Rect tmp = { (*it)->position.x + (*it)->winElement->relativePosition.x,(*it)->position.y + (*it)->winElement->relativePosition.y,(*it)->position.w,(*it)->position.h };
					App->render->DrawQuad(tmp, Red, true, false);
				}
			}

		}
	}

	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");
	for (std::list<UIElement*>::iterator it = elements.begin(); it != elements.end(); it++)
	{
		(*it)->CleanUp();
		RELEASE(*it);
	}
	elements.clear();
	return true;
}

bool j1Gui::Save(pugi::xml_node &config) const
{
	return true;
}

bool j1Gui::Load(pugi::xml_node &config)
{
	return true;
}



InheritedImage* j1Gui::AddImage(SDL_Rect& position, iPoint positionOffset, SDL_Rect& section, bool draggable)
{
	InheritedImage* ret = new InheritedImage(position, positionOffset, section, draggable);
	elements.push_back(ret);
	return ret;
}

LifeBar* j1Gui::AddLifebar(SDL_Rect& position, iPoint positionOffset, SDL_Rect& section, bool draggable)
{
	LifeBar* ret = new LifeBar(position, positionOffset, section, draggable);
	elements.push_back(ret);
	return ret;
}



InheritedInteractive * j1Gui::AddInteractive(SDL_Rect & position, iPoint positionOffset, SDL_Rect & size, InteractiveType type, j1Module * callback, bool draggable)
{
	InheritedInteractive* ret = new InheritedInteractive(position, positionOffset, size, type, callback, draggable);
	elements.push_back(ret);
	return ret;
}

InheritedLabel* j1Gui::AddLabel(SDL_Rect& position, iPoint positionOffset, std::string& fontPath, SDL_Color textColor, std::string& label, int size, bool draggable)
{
	InheritedLabel* ret = new InheritedLabel(position, positionOffset, fontPath, textColor, label, size, draggable);
	elements.push_back(ret);

	return ret;
}



InteractiveImage * j1Gui::AddInteractiveImage(SDL_Rect & position, iPoint positionOffsetA, iPoint positionOffsetB, SDL_Rect image_section,InteractiveType type, j1Module * callback, bool draggable)
{
	InteractiveImage* ret = new InteractiveImage(position, positionOffsetA, positionOffsetB, image_section, type, callback, draggable);
	elements.push_back(ret);
	return ret;
}

InteractiveLabel * j1Gui::AddInteractiveLabel(SDL_Rect & position, iPoint positionOffsetA, iPoint positionOffsetB, std::string& fontPath, SDL_Color textColor, std::string& label, int size, InteractiveType type, j1Module * callback, bool draggable)
{
	InteractiveLabel* ret = new InteractiveLabel(position, positionOffsetA, positionOffsetB, fontPath, textColor, label, size, type, callback, draggable);
	elements.push_back(ret);
	return ret;
}



InteractiveLabelledImage* j1Gui::AddInteractiveLabelledImage(SDL_Rect & position, iPoint positionOffsetA, iPoint positionOffsetB, iPoint positionOffsetC, SDL_Rect & image_section, std::string& fontPath, SDL_Color & textColor, std::string& label, int size, InteractiveType type, j1Module * callback, bool draggable)
{
	InteractiveLabelledImage* ret = new InteractiveLabelledImage(position, positionOffsetA, positionOffsetB, positionOffsetC, image_section, fontPath, textColor, label, size, type, callback, draggable);
	elements.push_back(ret);
	return ret;
}


LabelledImage* j1Gui::AddLabelledImage(SDL_Rect & position, iPoint positionOffsetA, iPoint Imagerelativepos, std::string& fontPath, SDL_Color textColor, std::string& label, int size, SDL_Rect image_section, bool draggable)
{
	LabelledImage* ret = new LabelledImage(position, positionOffsetA, Imagerelativepos, fontPath, textColor, label, size, image_section, draggable);
	elements.push_back(ret);
	return ret;
}


Scrollbar * j1Gui::AddScrollbar(SDL_Rect & scroller_image, bool moves_vertically, int min, SDL_Rect & pos, iPoint Sliderrelativepos, SDL_Rect image_section, ScrollbarType type, bool draggable)
{
	Scrollbar* ret = new Scrollbar(scroller_image, moves_vertically, min, pos, Sliderrelativepos, image_section, type, draggable);
	elements.push_back(ret);
	return ret;
}

void j1Gui::DeleteElement(UIElement* element)
{
	element->CleanUp();
	elements.remove(element);
	RELEASE(element);
}

UIElement* j1Gui::AddImage_From_otherFile(SDL_Rect& position, iPoint positionOffset, std::string& path, bool draggable)
{
	UIElement* element = new InheritedImage(position, positionOffset, path, draggable);
	elements.push_back(element);

	return element;
}

Window * j1Gui::AddWindow(SDL_Rect &windowrect, bool draggable)
{
	Window* window = new Window(windowrect,draggable);
	window_list.push_back(window);

	return window;
}

void j1Gui::Load_UIElements(pugi::xml_node node, j1Module* callback)
{
	BROFILER_CATEGORY("UI", Profiler::Color::Chocolate);

	pugi::xml_node tmp;

	tmp = node.child("alternate_image");
	if (tmp)
	{
		Load_AlterantiveImage_fromXML(tmp);
		while (tmp = tmp.next_sibling("alternate_image"))
		{
			Load_AlterantiveImage_fromXML(tmp);
		}
	}
	tmp = node.child("interactivelabelledimage");

	tmp = node.child("image");

	if (tmp)
	{
		App->gui->Load_Image_fromXML(tmp);
		while (tmp = tmp.next_sibling("image"))
		{
			App->gui->Load_Image_fromXML(tmp);
		}
	}

	tmp = node.child("interactiveimage");
	if (tmp)
	{
		App->gui->Load_InteractiveImage_fromXML(tmp, callback);
		while (tmp = tmp.next_sibling("interactiveimage"))
		{
			App->gui->Load_InteractiveImage_fromXML(tmp, callback);
		}
	}

	tmp = node.child("labelledimage");
	if (tmp)
	{
		App->gui->Load_LabelledImage_fromXML(tmp);
		while (tmp = tmp.next_sibling("labelledimage"))
		{
			App->gui->Load_LabelledImage_fromXML(tmp);
		}
	}

	tmp = node.child("interactivelabelledimage");
	if (tmp)
	{
		App->gui->Load_InteractiveLabelledImage_fromXML(tmp, callback);
		while (tmp = tmp.next_sibling("interactivelabelledimage"))
		{
			App->gui->Load_InteractiveLabelledImage_fromXML(tmp, callback);
		}
	}

	tmp = node.child("scrollbar");
	if (tmp)
	{
		App->gui->Load_Scrollbar_fromXML(tmp);
		while (tmp = tmp.next_sibling("scrollbar"))
		{
			App->gui->Load_Scrollbar_fromXML(tmp);
		}
	}

}


UIElement* j1Gui::Load_InteractiveLabelledImage_fromXML(pugi::xml_node tmp, j1Module* callback)
{
	InteractiveLabelledImage* added = nullptr;
	
	SDL_Rect pos = { tmp.child("pos").attribute("x").as_int(), tmp.child("pos").attribute("y").as_int(), tmp.child("pos").attribute("w").as_int(), tmp.child("pos").attribute("h").as_int() };
	iPoint relativeposA = { tmp.child("relativeposA").attribute("x").as_int(),tmp.child("relativeposA").attribute("y").as_int() };
	iPoint relativeposB = { tmp.child("relativeposB").attribute("x").as_int(),tmp.child("relativeposB").attribute("y").as_int() };
	iPoint relativeposC = { tmp.child("relativeposC").attribute("x").as_int(),tmp.child("relativeposC").attribute("y").as_int() };
	SDL_Rect section = { tmp.child("imagesection").attribute("x").as_int(), tmp.child("imagesection").attribute("y").as_int(), tmp.child("imagesection").attribute("w").as_int(), tmp.child("imagesection").attribute("h").as_int() };
	std::string path = tmp.child("fontpath").attribute("path").as_string();
	std::string label = tmp.child("label").attribute("string").as_string();
	SDL_Color color = { tmp.child("color").attribute("r").as_int(), tmp.child("color").attribute("g").as_int(), tmp.child("color").attribute("b").as_int(), tmp.child("color").attribute("a").as_int() };
	int size = tmp.child("size").attribute("value").as_int();
	InteractiveType type = InteractiveType_from_int(tmp.child("type").attribute("value").as_int());
	bool draggable = tmp.child("draggable").attribute("value").as_bool();

	added = AddInteractiveLabelledImage(pos, relativeposA, relativeposB, relativeposC, section, path, color, label, size, type, callback, draggable);
	
	if (!tmp.child("active").attribute("value").as_bool(true))
		added->active = false;

	added->hover = { tmp.child("hover").attribute("x").as_int(), tmp.child("hover").attribute("y").as_int(), tmp.child("hover").attribute("w").as_int(), tmp.child("hover").attribute("h").as_int() };
	added->click = { tmp.child("click").attribute("x").as_int(), tmp.child("click").attribute("y").as_int(), tmp.child("click").attribute("w").as_int(), tmp.child("click").attribute("h").as_int() };
	added->inactive = { tmp.child("inactive").attribute("x").as_int(), tmp.child("inactive").attribute("y").as_int(), tmp.child("inactive").attribute("w").as_int(), tmp.child("inactive").attribute("h").as_int() };

	return added;
}

Window* j1Gui::Load_Window_fromXML(pugi::xml_node node, j1Module* callback)
{
	SDL_Rect collider = { node.child("collider").attribute("x").as_int(), node.child("collider").attribute("y").as_int(), node.child("collider").attribute("w").as_int(), node.child("collider").attribute("h").as_int() };

	bool draggable =  node.child("draggable").attribute("value").as_bool(false);
	Window* added = AddWindow(collider,draggable);
	if (!node.child("active").attribute("value").as_bool(true))
		added->active = false;

	return added;
}



UIElement* j1Gui::Load_Image_fromXML(pugi::xml_node node)
{
	SDL_Rect position = { node.child("position").attribute("x").as_int(), node.child("position").attribute("y").as_int(), node.child("position").attribute("w").as_int(), node.child("position").attribute("h").as_int() };
	iPoint relativePos = { node.child("relativePosition").attribute("x").as_int(),node.child("relativePosition").attribute("y").as_int() };
	SDL_Rect image_section = { node.child("image_section").attribute("x").as_int(), node.child("image_section").attribute("y").as_int(), node.child("image_section").attribute("w").as_int(), node.child("image_section").attribute("h").as_int() };
	bool draggable = node.child("draggable").attribute("value").as_bool();


	Image* added = AddImage(position, relativePos, image_section, draggable);

	added->active = node.child("active").attribute("value").as_bool(true);
	return added;
}

UIElement* j1Gui::Load_AlterantiveImage_fromXML(pugi::xml_node node)
{
	std::string path = node.child("path").attribute("string").as_string();
	SDL_Rect position = { node.child("position").attribute("x").as_int(), node.child("position").attribute("y").as_int(), node.child("position").attribute("w").as_int(), node.child("position").attribute("h").as_int() };
	iPoint relativePos = { node.child("relativePosition").attribute("x").as_int(),node.child("relativePosition").attribute("y").as_int() };
	bool draggable = node.child("draggable").attribute("value").as_bool();

	UIElement* added = AddImage_From_otherFile(position, relativePos, path, draggable);
	added->active = node.child("active").attribute("value").as_bool(true);
	return added;
}


UIElement * j1Gui::Load_Label_fromXML(pugi::xml_node node)
{
	InheritedLabel* ret;
	SDL_Rect position = { node.child("position").attribute("x").as_int(), node.child("position").attribute("y").as_int(), node.child("position").attribute("w").as_int(), node.child("position").attribute("h").as_int() };
	iPoint relativepos =  { node.child("relativePosition").attribute("x").as_int(),node.child("relativePosition").attribute("y").as_int() }; 
	std::string fontPath = node.child("fontpath").attribute("path").as_string();
	SDL_Color color = { node.child("color").attribute("r").as_int(), node.child("color").attribute("g").as_int(), node.child("color").attribute("b").as_int(), node.child("color").attribute("a").as_int() };
	std::string label = node.child("label").attribute("value").as_string();
	int size = node.child("size").attribute("value").as_int();
	bool draggable = node.child("draggable").attribute("value").as_bool();

	ret = AddLabel(position, relativepos, fontPath, color, label, size, draggable);

	if (!node.child("active").attribute("value").as_bool(true))
		ret->active = false;
	return ret;
}

UIElement * j1Gui::Load_InteractiveImage_fromXML(pugi::xml_node node, j1Module* callback)
{
	InteractiveImage* ret;
	SDL_Rect position = { node.child("position").attribute("x").as_int(), node.child("position").attribute("y").as_int(), node.child("position").attribute("w").as_int(), node.child("position").attribute("h").as_int() };
	iPoint relativeposA = { node.child("relativePositionA").attribute("x").as_int(),node.child("relativePosition").attribute("y").as_int() };
	iPoint relativeposB = { node.child("relativePositionB").attribute("x").as_int(),node.child("relativePosition").attribute("y").as_int() };
	SDL_Rect image_section = { node.child("imagesection").attribute("x").as_int(), node.child("imagesection").attribute("y").as_int(), node.child("imagesection").attribute("w").as_int(), node.child("imagesection").attribute("h").as_int() };
	bool draggable = node.child("draggable").attribute("value").as_bool();
	InteractiveType type = InteractiveType_from_int(node.child("type").attribute("value").as_int());
	ret = AddInteractiveImage(position, relativeposA, relativeposB, image_section, type, callback, draggable);
	ret->hover = { node.child("hover").attribute("x").as_int(), node.child("hover").attribute("y").as_int(), node.child("hover").attribute("w").as_int(), node.child("hover").attribute("h").as_int() };
	ret->click = { node.child("click").attribute("x").as_int(), node.child("click").attribute("y").as_int(), node.child("click").attribute("w").as_int(), node.child("click").attribute("h").as_int() };
	ret->inactive = { node.child("inactive").attribute("x").as_int(), node.child("inactive").attribute("y").as_int(), node.child("inactive").attribute("w").as_int(), node.child("inactive").attribute("h").as_int() };
	
	if (!node.child("active").attribute("value").as_bool(true))
		ret->active = false;
	return ret;
}

UIElement * j1Gui::Load_Scrollbar_fromXML(pugi::xml_node node)
{
	Scrollbar* ret;
	SDL_Rect scroller_image = { node.child("scrollerimage").attribute("x").as_int(), node.child("scrollerimage").attribute("y").as_int(), node.child("scrollerimage").attribute("w").as_int(), node.child("scrollerimage").attribute("h").as_int() };
	bool moves_vertically = node.child("movesvertically").attribute("value").as_bool();
	int min = node.child("min").attribute("value").as_int();
	SDL_Rect position = { node.child("position").attribute("x").as_int(), node.child("position").attribute("y").as_int(), node.child("position").attribute("w").as_int(), node.child("position").attribute("h").as_int() };
	iPoint sliderrelativepos = { node.child("sliderrelativepos").attribute("x").as_int(),node.child("sliderrelativepos").attribute("y").as_int() };
	SDL_Rect image_section = { node.child("imagesection").attribute("x").as_int(), node.child("imagesection").attribute("y").as_int(), node.child("imagesection").attribute("w").as_int(), node.child("imagesection").attribute("h").as_int() };
	ScrollbarType type = ScrollbarType_from_int(node.child("type").attribute("value").as_int(0));
	bool draggable = node.child("draggable").attribute("value").as_bool();
	ret = AddScrollbar(scroller_image, moves_vertically, min, position, sliderrelativepos, image_section,type, draggable);
	if (!node.child("active").attribute("value").as_bool(true))
		ret->active = false;
	return ret;
}

UIElement * j1Gui::Load_LabelledImage_fromXML(pugi::xml_node node)
{
	LabelledImage* ret;
	SDL_Rect position = { node.child("position").attribute("x").as_int(), node.child("position").attribute("y").as_int(), node.child("position").attribute("w").as_int(), node.child("position").attribute("h").as_int() };
	iPoint labeloffset = { node.child("labelrelativepos").attribute("x").as_int(),node.child("labelrelativepos").attribute("y").as_int() };
	iPoint imageoffset = { node.child("imageoffset").attribute("x").as_int(),node.child("imageoffset").attribute("y").as_int() };
	std::string fontpath = node.child("fontpath").attribute("string").as_string();
	SDL_Color color = { node.child("color").attribute("r").as_int(), node.child("color").attribute("g").as_int(), node.child("color").attribute("b").as_int(), node.child("color").attribute("a").as_int() };
	std::string label = node.child("label").attribute("string").as_string();
	int size = node.child("size").attribute("value").as_int();
	SDL_Rect imagesection = { node.child("imagesection").attribute("x").as_int(), node.child("imagesection").attribute("y").as_int(), node.child("imagesection").attribute("w").as_int(), node.child("imagesection").attribute("h").as_int() };
	bool draggable = node.child("draggable").attribute("value").as_bool();
	
	ret = AddLabelledImage(position, labeloffset, imageoffset, fontpath, color, label, size, imagesection, draggable);
	if (!node.child("active").attribute("value").as_bool(true))
		ret->active = false;

	if (node.child("isTimeLabel").attribute("value").as_bool(false))
		timeLabel = ret;

	return ret;
}

void j1Gui::Load_LifeBar_formXML(pugi::xml_node node, LifeBar* imageData)
{
	imageData->threeLivesImageSection = { node.child("threeLives").attribute("x").as_int(), node.child("threeLives").attribute("y").as_int(), node.child("threeLives").attribute("w").as_int(), node.child("threeLives").attribute("h").as_int() };
	imageData->twoLivesImageSection = { node.child("twoLives").attribute("x").as_int(), node.child("twoLives").attribute("y").as_int(), node.child("twoLives").attribute("w").as_int(), node.child("twoLives").attribute("h").as_int() };
	imageData->lastLifeImageSection = { node.child("lastLife").attribute("x").as_int(), node.child("lastLife").attribute("y").as_int(), node.child("lastLife").attribute("w").as_int(), node.child("lastLife").attribute("h").as_int() };

}

Animation j1Gui::LoadPushbacks_fromXML(pugi::xml_node node)
{
	Animation ret;
	pugi::xml_node tmp = node.child("pushback");

	while (tmp)
	{
		ret.PushBack({ tmp.attribute("x").as_int(), tmp.attribute("y").as_int(), tmp.attribute("w").as_int(), tmp.attribute("h").as_int() });
		tmp = tmp.next_sibling("pushback");
	}
	
	ret.speed = node.child("speed").attribute("value").as_float();
	ret.loop = node.child("loop").attribute("value").as_bool();
	

	return ret;
}

InteractiveType j1Gui::InteractiveType_from_int(int type)
{
	InteractiveType ret;
	switch (type)
	{
	case(1):
		ret = QUIT;
		break;
	case(2):
		ret = CONTINUE;
		break;
	case(3):
		ret = NEWGAME;
		break;
	case(4):
		ret = OPEN_SETTINGS;
		break;
	case(5):
		ret = OPEN_CREDITS;
		break;
	case(6):
		ret = CLOSE_WINDOW;
		break;	
	case(7):
		ret = EXIT_TO_MENU;
		break;
	case(8):
		ret = SAVE_GAME;
		break;
	case(9):
		ret = UNLOCKUI;
		break;
	default:
		ret = DEFAULT;
	};
	return ret;
}

ScrollbarType j1Gui::ScrollbarType_from_int(int type)
{
	ScrollbarType ret;

	switch (type)
	{
	case(1):
		ret = MUSICVOLUME;
		break;
	case(2):
		ret = SFXVOLUME;
		break;
	default:
		ret = SCROLLBAR_DEFAULT;
		break;
	}
	return ret;
}


// const getter for atlas
 SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}
