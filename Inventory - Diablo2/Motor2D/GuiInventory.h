#ifndef _GUIINVENTORY_H_
#define _GUIINVENTORY_H_

#include "GuiElements.h"
#include "p2Point.h"
#include "GuiSlot.h"
#include "GuiItem.h"
#include <vector>
#include <list>

using namespace std;


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
	void Update(GuiElement* hover, GuiElement* focus);

	//Blit to screen
	void Draw();

	//Draws debug elements
	void DrawDebug();

	//Translates from slot coord to local coords
	iPoint SlotToInventory(iPoint pos);
	iPoint InventoryToSlot(iPoint pos);

	//Checks if there's space for an item and then adds it
	bool AddItem(GuiItem* item);

	//Checks if there's space for an item
	bool CheckFreeSpace(GuiItem* item);
	/*
	--------Attributes
	*/


private:
	
	int columns;
	int rows;
	int slot_width;
	int slot_height;

	GuiImage image;
	
	vector<GuiSlot> slots;
	list<GuiItem*> items;
	//NOTE: thinking of puting a list of ocupied slots and a list of free slots for optimization when searching free space or drawin slots

}





#endif _GUIINVENTORY_H_