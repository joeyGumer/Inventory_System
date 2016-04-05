#include "j1HUD.h"
#include "j1App.h"
#include "j1Gui.h"
#include "j1Player.h"
#include "j1Game.h"
#include "j1SceneManager.h"
#include "snIntro.h"
#include "hudElement.h"
#include "hudBelt.h"


//NOTE : provisional
#include "j1Input.h"

//Constructor
j1HUD::j1HUD() : j1Module()
{
	belt = new hudBelt();

	hud_gui_elements.push_back(belt);
}

j1HUD::~j1HUD()
{}

bool j1HUD::Start()
{
	for (int i = 0; i < hud_gui_elements.size(); i++)
	{
		hud_gui_elements[i]->Start();
	}
	//Initializating the main HUD elements
	//NOTE: totally have to change this system...
		main_menu = false;

		//Menu
		options = App->gui->AddGuiImage({ 310, 130 }, { 395, 71, 194, 31 }, NULL, this);
		options->interactable = true;
		options->active = false;
		HUD_elements.push_back(options);

		saveandexit = App->gui->AddGuiImage({ 145, 200 }, { 460, 0, 534, 35 }, NULL, this);
		saveandexit->interactable = true;
		saveandexit->active = false;
		HUD_elements.push_back(saveandexit);

		returntogame = App->gui->AddGuiImage({ 195, 270 }, { 994, 0, 438, 35 }, NULL, this);
		returntogame->interactable = true;
		returntogame->active = false;
		HUD_elements.push_back(returntogame);

		//Debug labels
		//NOTE : coming soon
		/*life_debug = App->gui->AddGuiLabel("", NULL, { 0, 0 }, life, this);
		life_debug->Center(true, true);
		life_debug->debug = true;

		mana_debug = App->gui->AddGuiLabel("", NULL, { 0, 0 }, mana, this);
		mana_debug->Center(true, true);
		mana_debug->debug = true;*/

		//Inventory
		main_inventory = App->gui->AddGuiInventory({ 500, 300 }, { 1144, 843, 291, 117 }, 10, 4, 29, 29, { 0, 0 }, NULL, this);

	return true;
}

//Called before each loop iteration
bool j1HUD::PreUpdate()
{

	for (int i = 0; i < hud_gui_elements.size(); i++)
	{
		hud_gui_elements[i]->PreUpdate();
	}

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		ActivateMenu();
	}


	if (main_menu == true)
	{
		ActivateMenu();
		App->sm->ChangeScene(App->sm->intro);
	}

	return true;
}

//Called each frame
bool j1HUD::Update(float dt)
{	
	for (int i = 0; i < hud_gui_elements.size(); i++)
	{
		hud_gui_elements[i]->Update(dt);
	}


	return true;
}

//Called after each loop iteration
bool j1HUD::PostUpdate()
{
	for (int i = 0; i < hud_gui_elements.size(); i++)
	{
		hud_gui_elements[i]->PostUpdate();
	}

	return true;
}

bool j1HUD::CleanUp()
{
	for (list<GuiElement*>::iterator item = HUD_elements.begin(); item != HUD_elements.end(); item++)
	{
		for (list<GuiElement*>::iterator item2 = App->gui->gui_elements.begin(); item2 != App->gui->gui_elements.end(); item2++)
		{
			if ((*item2) == (*item))
			{
				RELEASE(*item2);
				App->gui->gui_elements.erase(item2);
				break;
			}
		}
	}

	HUD_elements.clear();

	for (int i = 0; i < hud_gui_elements.size(); i++)
	{
		hud_gui_elements[i]->CleanUp();
	}

	return true;
}

void j1HUD::OnEvent(GuiElement* element, GUI_Event even)
{

	//Game menu --------------------------------
	//SaveAndExit button -----------------------------------------------------------------------------
	if (saveandexit == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
			main_menu = true;
			break;
		}
	}

	//ReturnToGame button -----------------------------------------------------------------------------
	if (returntogame == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
			ActivateMenu();
			break;
		}
	}
}



void j1HUD::ActivateMenu()
{
	options->active = !options->active;
	returntogame->active = !returntogame->active;
	saveandexit->active = !saveandexit->active;


	App->game->pause = !App->game->pause;
}