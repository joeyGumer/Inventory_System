#include "hudInventory.h"
#include "j1App.h"
#include "j1Gui.h"
#include "j1Input.h"
#include "GuiItem.h"
#include "GuiInventory.h"



//Constructor
//Don't now why the code makes me put semicolons everywhere
;
hudInventory::hudInventory() : hudElement()
{

}

//Destructor
hudInventory::~hudInventory()
{

}

//Called before fist frame
bool hudInventory::Start()
{

	background = App->gui->AddGuiImage({ 401, 0 }, { 1128, 588, 319, 430 }, NULL, this);
	inventory = App->gui->AddGuiInventory({ 16, 255 }, { 1144, 843, 290, 116 }, 10, 4, 29, 29, { 0, 0 }, background, this);

	return true;
}

//Called before each loop iteration
bool hudInventory::PreUpdate()
{
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		GuiItem* new_item;
		iPoint coords[1] = { { 0, 0 } };
		new_item = new GuiItem(1, coords, { 2285, 799, ITEM_SECTION_SIZE, ITEM_SECTION_SIZE });
		if (!inventory->AddItem(new_item))
		{
			delete new_item;
		}
	
	}
	return true;
}

//Called each frame
bool hudInventory::Update(float dt)
{
	return true;
}

//Called after each loop iteration
bool hudInventory::PostUpdate()
{
	return true;
}

//Called before quitting
bool hudInventory::CleanUp()
{
	return true;
}

//Called when there's a gui event
void hudInventory::OnEvent(GuiElement* element, GUI_Event even)
{

}
