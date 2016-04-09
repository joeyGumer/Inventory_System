#ifndef _GUISLOT_H_
#define _GUISLOT_H_

#include "GuiElements.h"

class GuiItem;
class j1Module;

class GuiSlot : public GuiElement
{
public:
	GuiSlot(iPoint p, SDL_Rect r, GuiElement* parent, j1Module* listener);
	~GuiSlot();

	void Update(GuiElement* hover, GuiElement* focus);
	void Draw();

public:
	iPoint coords;
	GuiItem* inventory_item;
};

#endif _GUISLOT_H_