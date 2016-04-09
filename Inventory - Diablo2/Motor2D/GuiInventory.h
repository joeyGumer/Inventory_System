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
	void Update(GuiElement* hover, GuiElement* focus, GuiItem* dragged_item);

	//Blit to screen
	void Draw();
	
	//Draws debug elements
	void DrawDebug();
	
	void CleanItems();

	//Translates from slot coord to local coords
	iPoint SlotToInventory(iPoint pos);
	iPoint InventoryToSlot(iPoint pos);
	iPoint ScreenToSlot(iPoint pos);

	//Checks if there's space for an item and then adds it
	bool AutomaticAddItem(GuiItem* item);
	bool AddItem(GuiItem* item, GuiSlot* new_slot);

	//Checks if there's space for an item
	bool IsPlaceable(GuiItem* item, iPoint& coord);

	//Asignes the item to the group of slots that it will occupy
	void AssignItemToSlots(GuiItem* item, iPoint& coord);

	//Returns a pointer to the slot giving it's coord in the inventory
	GuiSlot* GetSlotFromCoord(iPoint& coord);

	//Returns the Coord that the item would have if placed on the inventory;
	iPoint	GetCoordFromItem(GuiItem* item);

	//Checks if the coord exists in the inventory space
	bool CoordExist(iPoint& coord);
	
	//Slot coloring
	void SetSlotsAvaliable(GuiItem* item);
	
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

public:
	list<GuiItem*> items;
	//NOTE: thinking of puting a list of ocupied slots and a list of free slots for optimization when searching free space or drawin slots

}

#endif _GUIINVENTORY_H_