#ifndef _GUIINVENTORY_H_
#define _GUIINVENTORY_H_

#include "GuiElements.h"
#include "p2Point.h"
#include <vector>

using namespace std;

//NOTE: Do the slot a Gui element?
struct Slot
{
	Slot(iPoint p, SDL_Rect r, GuiElement* father) : coords(p), local_rect(r), parent(father), free(true){}

	iPoint coords;
	SDL_Rect local_rect;
	bool free;
	GuiElement* parent;


	SDL_Rect GetScreenRect();
};


class GuiInventory : public GuiElement
{
	/*
	-------Methods
	*/
public:

	//Constructor
	GuiInventory(iPoint p, SDL_Rect r, int columns, int rows, int slot_w, int slot_h, iPoint offset = { 0, 0 }, GuiElement* par = NULL, j1Module* list = NULL);


	//Destructor
	~GuiInventory();

	//Called each loop iteration
	void Update();

	//Blit to screen
	void Draw();

	//Draws debug elements
	void DrawDebug();

	//Translates from slot coord to local coords
	iPoint SlotToInventory(iPoint pos);
	iPoint InventoryToSlot(iPoint pos);


	/*
	--------Attributes
	*/


private:
	
	int columns;
	int rows;
	int slot_width;
	int slot_height;

	GuiImage image;

	//vector or list?
	vector<Slot> slots;

}





#endif _GUIINVENTORY_H_