#include "GuiItem.h"


GuiItem::GuiItem(int s, iPoint* coord, SDL_Rect r) 
	:GuiElement({ 0, 0 }, r, GUI_ITEM, NULL, NULL)
	, image({ 0, 0 }, r, this, NULL)
{
	size = s;
	coords = new iPoint[size];
	ocupied_slots = new GuiSlot*[size];

	for (int i = 0; i < s; i++)
	{
		coords[i] = coord[i];
	}
}

GuiItem::~GuiItem()
{
	delete[] coords;
	delete[] ocupied_slots;
}

void GuiItem::Draw()
{
	image.Draw();
}

void GuiItem::Update(GuiElement* hover, GuiElement* focus)
{

}

iPoint GetSectionPivot()
{
	return{ 0, 0 };
}
