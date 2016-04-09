#ifndef _GUIITEM_H_
#define _GUIITEM_H_

#include "GuiElements.h";
#include "p2Point.h"

#define ITEM_SECTION_SIZE 29

class GuiSlot;
class GuiInventory;

class GuiItem : public GuiElement
{
public:
	GuiItem(int s, iPoint* coord, SDL_Rect r);
	~GuiItem();
	
	void Draw();
	void DrawDebug();
	void Update(GuiElement* hover, GuiElement* focus, GuiItem* dragged_item);
	
	iPoint GetPivotPosition();

	void FreeSlots();

public:

	int size;
	//NOTE: take good care of these
	iPoint* coords;
	iPoint pivot;
	GuiSlot* reference_slot;
	GuiInventory* inventory;
	//
	GuiImage image;

	bool dragging = false;
};

#endif _GUISLOT_H_