#include "GuiInventory.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Gui.h"
#include "j1Input.h"


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
{

}

void GuiInventory::Update(GuiElement* hover, GuiElement* focus, GuiItem* dragged_item)
{
	for (int i = 0; i < slots.size(); i++)
	{
		slots[i].Update(hover, focus, dragged_item);
	}

	list<GuiItem*>::iterator it = items.begin();
	for (; it != items.end(); it++)
	{
		(*it)->Update(hover, focus, dragged_item);
	}

	if (this == hover)
	{
		if (dragged_item)
		{
			GuiInventory* tmp = (GuiInventory*)hover;

			iPoint coord = tmp->GetCoordFromItem(dragged_item);
			if (tmp->IsPlaceable(dragged_item, coord))
			{
				SetSlotsAvaliable(dragged_item);
				if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
				{
						GuiSlot* slot = tmp->GetSlotFromCoord(coord);
						tmp->AddItem(dragged_item, slot);
						App->gui->dragged_item->dragging = false;
						App->gui->dragged_item = NULL;
				}
			}
		}

	}
}



void GuiInventory::Draw()
{
	image.Draw();

	list<GuiItem*>::iterator it = items.begin();
	for (; it != items.end(); it++)
	{
		if (!(*it)->dragging)
		{
			(*it)->Draw();
		}
	}

	for (int i = 0; i < slots.size(); i++)
	{
		slots[i].Draw();
	}
}

void GuiInventory::DrawDebug()
{
	image.DrawDebug();

	for (int i = 0; i < slots.size(); i++)
	{
		slots[i].DrawDebug();
	}
	
	list<GuiItem*>::iterator it = items.begin();
	for (; it != items.end(); it++)
	{
		(*it)->DrawDebug();
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

iPoint GuiInventory::ScreenToSlot(iPoint pos)
{
	iPoint ret = pos;

	ret -= GetScreenPosition();

	return InventoryToSlot(ret);
}

bool GuiInventory::AddItem(GuiItem* item, GuiSlot* new_slot)
{
	AssignItemToSlots(item, new_slot->coords);
	//In case was moved to the same list, stupid, but necessary
	//items.remove(item);
	//

	item->reference_slot = new_slot;
	item->SetLocalPosition(item->reference_slot->GetScreenPosition());

	if (item->inventory != this)
	{
		items.push_back(item);
		item->inventory = this;
	}

	return true;
}

bool GuiInventory::AutomaticAddItem(GuiItem* item)
{
	for (int i = 0; i < slots.size(); i++)
	{
		if (slots[i].inventory_item == NULL)
		{
			if (IsPlaceable(item, slots[i].coords))
			{
				AddItem(item, &slots[i]);
				return true;
			}
		}
	}

	return false;
}

void GuiInventory::AssignItemToSlots(GuiItem* item, iPoint& coord)
{
	for (int i = 0; i < item->size; i++)
	{
		GuiSlot* tmp = GetSlotFromCoord(coord + item->coords[i]);
		tmp->inventory_item = item;
	}
}

bool GuiInventory::IsPlaceable(GuiItem* item, iPoint& coord)
{

	for (int i = 0; i < item->size; i++)
	{
		GuiSlot* tmp = GetSlotFromCoord(coord + item->coords[i]);
		if (tmp == NULL || tmp->inventory_item)
		{
			return false;
		}
	}

	return true;
}

GuiSlot* GuiInventory::GetSlotFromCoord(iPoint& coord)
{
	if (CoordExist(coord))
	{
		for (int i = 0; i < slots.size(); i++)
		{
			if (slots[i].coords == coord)
			{
				return &slots[i];
			}
		}
	}

	return NULL;
}

iPoint GuiInventory::GetCoordFromItem(GuiItem* item)
{
	iPoint ret = item->GetPivotPosition();
	ret = ScreenToSlot(ret);
	
	return ret;
}

bool GuiInventory::CoordExist(iPoint& coord)
{
	if (coord.x >= 0 && coord.x < columns && coord.y >= 0 && coord.y < rows)
	{
		return true;
	}

	return false;
}

void GuiInventory::CleanItems()
{
	//NOTE: this is just because we are creating new items
	list<GuiItem*>::iterator it = items.begin();
	for (; it != items.end(); it++)
	{
		RELEASE(*it);
	}

	items.clear();
}

//Slot coloring
void GuiInventory::SetSlotsAvaliable(GuiItem* item)
{
	for (int i = 0; i < item->size; i++)
	{
		GuiSlot* slot = GetSlotFromCoord(item->coords[i] + GetCoordFromItem(item));
		slot->state = GREEN;
	}
}