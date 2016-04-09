#ifndef _GUIITEM_H_
#define _GUIITEM_H_

#include "GuiElements.h";
#include "p2Point.h"

#define ITEM_SECTION_SIZE 29

class GuiSlot;

class GuiItem : public GuiElement
{
public:
	GuiItem(int s, iPoint* coord, SDL_Rect r);
	~GuiItem();
	
	void Draw();
	void Update(GuiElement* hover, GuiElement* focus);
	
	iPoint GetSectionPivot();

public:

	int size;
	//NOTE: take good care of these
	iPoint* coords;
	GuiSlot** ocupied_slots;
	//

	GuiImage image;
};

#endif _GUISLOT_H_