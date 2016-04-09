#include "GuiInventory.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Gui.h"

GuiInventory::GuiInventory(iPoint p, SDL_Rect r,int col, int row, int slot_w, int slot_h, iPoint offset, GuiElement* par, j1Module* list)
:GuiElement(p, r, GUI_INVENTORY, par, list), image({ 0, 0 }, r, this, NULL),
columns(col), rows(row), slot_width(slot_w), slot_height(slot_h)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			iPoint coord = { j, i };
			iPoint pos = SlotToInventory(coord);
			SDL_Rect rect = { pos.x, pos.y, slot_w, slot_w };
			GuiSlot tmp({ j, i }, rect, this, list);
			slots.push_back(tmp);
		}
	}
}

GuiInventory::~GuiInventory()
{}

void GuiInventory::Update(GuiElement* hover, GuiElement* focus)
{
	int ret = 9;
	ret++;
}
void GuiInventory::Draw()
{
	image.Draw();

	for (int i = 0; i < slots.size(); i++)
	{
		slots[i].Draw();
	}

	list<GuiItem*>::iterator it = items.begin();
	for (; it != items.end(); it++)
	{
		(*it)->Draw();
	}
}

void GuiInventory::DrawDebug()
{
	image.DrawDebug();

	for (int i = 0; i < slots.size(); i++)
	{
		slots[i].DrawDebug();
	}

}

iPoint GuiInventory::SlotToInventory(iPoint pos)
{
	iPoint ret = { 0, 0 };

	ret.x = pos.x * slot_width;
	ret.y = pos.y * slot_height;

	return ret;

}

iPoint GuiInventory::InventoryToSlot(iPoint pos)
{
	iPoint ret = { 0, 0 };

	ret.x = pos.x / slot_width;
	ret.y = pos.y / slot_height;

	return ret;
}

bool GuiInventory::AddItem(GuiItem* item)
{
	for (int i = 0; i < slots.size(); i++)
	{
		if (slots[i].inventory_item == NULL)
		{
			//Provisional for one sized Items
			for (int j = 0; j < item->size; j++)
			{
				item->ocupied_slots[j] = &slots[i];
				slots[i].inventory_item = item;
			}

			item->SetLocalPosition(slots[i].GetScreenPosition());
			items.push_back(item);

			return true;
		}
	}

	return false;
}