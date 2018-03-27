#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "p2Point.h"
#include "SDL/include/SDL_rect.h"
#include <string>
#include <list>

struct SDL_Texture;

enum EventTypes
{
	DEFAULT_TYPE = -1,
	LEFT_MOUSE_PRESSED,
	LEFT_MOUSE_RELEASED,
	RIGHT_MOUSE_PRESSED,
	RIGHT_MOUSE_RELEASED,
	MOUSE_HOVER_IN,
	MOUSE_HOVER_OUT,
	PRESSED_ENTER,
	PRESSED_TAB
};


#define CURSOR_WIDTH 2
enum UIType
{
	NO_TYPE,
	INTERACTIVE,
	IMAGE,
	LABEL,
	INTERACTIVE_IMAGE,
	INTERACTIVE_LABELLED_IMAGE,
	INTERACTIVE_LABEL,
	LABELLED_IMAGE,
	UICLOCK,
	SCROLLBAR,
};

enum InteractiveType
{
	DEFAULT,
	QUIT,
	CONTINUE,
	NEWGAME,
	OPEN_SETTINGS,
	OPEN_CREDITS,
	CLOSE_WINDOW,
	EXIT_TO_MENU,
	SAVE_GAME,
	UNLOCKUI,
};

enum ScrollbarType
{
	SCROLLBAR_DEFAULT,
	MUSICVOLUME,
	SFXVOLUME,
};
// TODO 1: Create your structure of classes
class UIElement;
class Window;
struct WinElement;
class InheritedInteractive;
class InheritedLabel;
class InheritedImage;
class InteractiveImage;
class InteractiveLabel;
class InteractiveLabelledImage;
class LabelledImage;
class Scrollbar;
struct SDL_Rect;
struct SDL_Texture;
class Animation;
class LifeBar;
// ---------------------------------------------------
class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called after all Updates
	bool PostUpdate();

	bool Draw(float dt);

	// Called before quitting
	bool CleanUp();

	bool Save(pugi::xml_node&) const;
	bool  Load(pugi::xml_node&);

	// TODO 2: Create the factory methods

	InheritedInteractive* AddInteractive(SDL_Rect& position, iPoint positionOffset, SDL_Rect& size,	 InteractiveType type, j1Module* callback, bool draggable = false);
	InheritedLabel* AddLabel(SDL_Rect& position, iPoint positionOffset, std::string& fontPath, SDL_Color textColor, std::string& label, int size = 12, bool draggable = false);
	InheritedImage* AddImage(SDL_Rect& position, iPoint positionOffset, SDL_Rect& section, bool draggable = false);
	LifeBar* AddLifebar(SDL_Rect& position, iPoint positionOffset, SDL_Rect& section, bool draggable = false);

	InteractiveImage* AddInteractiveImage(SDL_Rect& position, iPoint positionOffsetA, iPoint positionOffsetB, SDL_Rect image_section, InteractiveType type, j1Module* callback, bool draggable = false);
	InteractiveLabel* AddInteractiveLabel(SDL_Rect& position, iPoint positionOffsetA, iPoint positionOffsetB, std::string& fontPath, SDL_Color textColor, std::string& label, int size, InteractiveType type, j1Module* callback, bool draggable = false);
	InteractiveLabelledImage* AddInteractiveLabelledImage(SDL_Rect& position, iPoint positionOffsetA, iPoint positionOffsetB, iPoint positionOffsetC, SDL_Rect& image_section, std::string& fontPath, SDL_Color& textColor, std::string& label, int size, InteractiveType type, j1Module* callback, bool draggable = false);
	LabelledImage* AddLabelledImage(SDL_Rect& position, iPoint positionOffsetA, iPoint positionOffsetB, std::string& fontPath, SDL_Color textColor, std::string& label, int size, SDL_Rect image_section, bool draggable = false);
	Scrollbar* AddScrollbar(SDL_Rect & scroller_image, bool moves_vertically, int min, SDL_Rect & pos, iPoint Sliderrelativepos, SDL_Rect image_section, ScrollbarType type, bool draggable);

	void DeleteElement(UIElement* element);

	UIElement* AddImage_From_otherFile(SDL_Rect& position, iPoint positionOffset, std::string& path, bool draggable = false);

	Window* AddWindow(SDL_Rect &window, bool draggable = false);
	// Gui creation functions

	void Load_UIElements(pugi::xml_node node, j1Module* callback);
	UIElement* Load_InteractiveLabelledImage_fromXML(pugi::xml_node	tmp, j1Module* callback);
	Window* Load_Window_fromXML(pugi::xml_node node, j1Module* callback);
	UIElement* Load_Image_fromXML(pugi::xml_node node);
	UIElement* Load_AlterantiveImage_fromXML(pugi::xml_node node);
	UIElement* Load_Label_fromXML(pugi::xml_node node);
	UIElement* Load_InteractiveImage_fromXML(pugi::xml_node node, j1Module* callback);
	UIElement* Load_Scrollbar_fromXML(pugi::xml_node node);
	UIElement* Load_LabelledImage_fromXML(pugi::xml_node node);
	void Load_LifeBar_formXML(pugi::xml_node node, LifeBar* imageData);
	Animation LoadPushbacks_fromXML(pugi::xml_node node);


	InteractiveType InteractiveType_from_int(int type);
	ScrollbarType ScrollbarType_from_int(int type);

	SDL_Texture* GetAtlas() const;

public:
	std::list<UIElement*>	elements;
	std::list<Window*>		window_list;
	bool					dragging_window = false;
	LabelledImage*			timeLabel = nullptr;
	std::string				buttonFX;

private:

	bool					debug = false;
	SDL_Texture*			atlas = nullptr;
	std::string				atlas_file_name;
	std::string				background;
	iPoint					mouseLastFrame;
};

#endif // __j1GUI_H__