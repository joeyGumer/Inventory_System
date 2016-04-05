#ifndef _j1HUD_H_
#define _j1HUD_H_

#include "j1Module.h"
#include <vector>
#include <list>

using namespace std;

#define STAT_LOCAL_Y 33
#define STAT_TEX_Y 196
#define STAT_MAX_H float(78)


enum GUI_Event;
class GuiElement;
class GuiImage;
class GuiLabel;
class GuiInventory;
class hudElement;
class hudBelt;


class j1HUD : public j1Module
{
public:
	j1HUD();

	~j1HUD();
	//Called before fist frame
	bool Start();

	//Called before each loop iteration
	bool PreUpdate();

	//Called each frame
	bool Update(float dt);

	//Called after each loop iteration
	bool PostUpdate();
	
	//Called before quitting
	bool CleanUp();

	//Called when there's a GUI event
	void OnEvent(GuiElement* element, GUI_Event even);

	//Utils
	void ActivateMenu();

private:
	
	bool main_menu = false;

	//In game menu elements -------
	GuiImage* options = NULL;
	GuiImage* saveandexit = NULL;
	GuiImage* returntogame = NULL;

	

	//Inventory
	GuiInventory* main_inventory;

public:
	//HUD main belt
	hudBelt* belt = NULL;

	list<GuiElement*> HUD_elements;
	vector<hudElement*> hud_gui_elements;
};

#endif _j1HUD_H_