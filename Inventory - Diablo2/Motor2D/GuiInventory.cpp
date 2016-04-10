#include "GuiInventory.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Input.h"
#include "j1Gui.h"


//Constructor
GuiInventory::GuiInventory(iPoint p, SDL_Rect r,int col, int row, int slot_w, int slot_h, GuiElement* par, j1Module* list)
:GuiElement(p, r, GUI_INVENTORY, par, list), 
	image({ 0, 0 }, r, this, NULL),
	columns(col), rows(row), slot_width(slot_w), slot_height(slot_h)
{
	//Creation of all the slots
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			iPoint pos = { j, i };
			pos = SlotToInventory(pos);
			SDL_Rect rect = { pos.x, pos.y, slot_w, slot_w };
			GuiSlot tmp({ j, i }, rect, this, list);
			slots.push_back(tmp);
		}
	}
}

//Destructor
GuiInventory::~GuiInventory()
{

}

//Called each loop iteration
void GuiInventory::Update(GuiElement* hover, GuiElement* focus)
{
	//Create this varaible to check if the dragged_item changes
	GuiItem* drag_item = App->gui->dragged_item;

	//Update the slots
	for (int i = 0; i < slots.size(); i++)
	{
		slots[i].Update(hover, focus);
	}
	//---

	//Update the items
	list<GuiItem*>::iterator it = items.begin();
	for (; it != items.end(); it++)
	{
		(*it)->Update(hover, focus);
	}
	//---

	//Checks the activity of the dragged_item
	if (this == hover && App->gui->dragged_item && drag_item == App->gui->dragged_item)
	{
		CheckDraggedItem(drag_item);
	}
}

//Checks the activy of the dragged item over the inventory
void GuiInventory::CheckDraggedItem(GuiItem* drag_item)
{
	//Item that can be exchanged
	GuiItem* extra_item = NULL;
	iPoint coord = GetCoordFromItem(drag_item);

	//Cheks if the drag_item is placeable
	if (IsPlaceable(drag_item, coord, true, &extra_item))
	{
		//According to if there's an item to be exchanged, the slots give us feedback
		if (!extra_item)
			SetSlotsState(drag_item, GREEN);
		else
			SetSlotsState(extra_item, YELLOW);

		//If left mouse button pressed while being able to place, add the item
		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
		{
			GuiSlot* slot = GetSlotFromCoord(coord);

			//According to if there's an exchange item, it does an exchange or just adds the item
			if (extra_item)
				Exchange(drag_item, slot, extra_item);

			else
				AddItem(drag_item, slot);
		}
	}
}

//Blit to screen
void GuiInventory::Draw()
{
	image.Draw();

	list<GuiItem*>::iterator it = items.begin();
	for (; it != items.end(); it++)
	{
		(*it)->Draw();
	}

	for (int i = 0; i < slots.size(); i++)
	{
		slots[i].Draw();
	}
}

//Draws debug elements
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

//From slot coordinate to local position in the inventory
iPoint GuiInventory::SlotToInventory(iPoint pos)
{
	iPoint ret = { 0, 0 };

	ret.x = pos.x * slot_width;
	ret.y = pos.y * slot_height;

	return ret;

}

//From local position in the inventory to the slot coordinate
iPoint GuiInventory::InventoryToSlot(iPoint pos)
{
	iPoint ret = { 0, 0 };

	ret.x = pos.x / slot_width;
	ret.y = pos.y / slot_height;

	return ret;
}

//From a screen point to the slot coordinate
iPoint GuiInventory::ScreenToSlot(iPoint pos)
{
	iPoint ret = pos;

	ret -= GetScreenPosition();

	return InventoryToSlot(ret);
}

//Adds item to the inventory
void GuiInventory::AddItem(GuiItem* item, GuiSlot* new_slot)
{
	AssignItemToSlots(item, new_slot->coords);

	item->reference_slot = new_slot;
	item->SetLocalPosition(item->reference_slot->GetScreenPosition());

	if (item->inventory != this)
	{
		if (item->inventory)
			item->inventory->items.remove(item);
		
		items.push_back(item);
		item->inventory = this;
	}

	if (item == App->gui->dragged_item)
	{
		App->gui->dragged_item = NULL;
	}

}

//Checks if there's space for an item and then adds it
bool GuiInventory::AutomaticAddItem(GuiItem* item)
{
	for (int i = 0; i < slots.size(); i++)
	{
		if (slots[i].inventory_item == NULL)
		{
			if (IsPlaceable(item, slots[i].coords, false))
			{
				AddItem(item, &slots[i]);
				return true;
			}
		}
	}

	return false;
}

//Frees and Item from the inventory
void GuiInventory::FreeItem(GuiItem* item)
{
	item->FreeSlots();
	App->gui->dragged_item = item;
}

//Places an item in exchange of another
void GuiInventory::Exchange(GuiItem* enter_item, GuiSlot* enter_slot, GuiItem* exit_item)
{
	FreeItem(exit_item);
	AddItem(enter_item, enter_slot);
}

//Asigns the item to the group of slots that it will occupy
void GuiInventory::AssignItemToSlots(GuiItem* item, iPoint& coord)
{
	for (int i = 0; i < item->size; i++)
	{
		GuiSlot* tmp = GetSlotFromCoord(coord + item->coords[i]);
		if (tmp)
			tmp->inventory_item = item;
	}
}

//Checks if there's space for an item
bool GuiInventory::IsPlaceable(GuiItem* item, iPoint& coord, bool exchange, GuiItem** extra_item)
{
	//The way to check if a space is placeable is different according to the permission to do or not an exchange:

	//Placing in case there's no need to do an exchange
	if (exchange == false)
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
	//-----

	//Placing in case there's permission to do an exchange
	else
	{
		for (int i = 0; i < item->size; i++)
		{
			GuiSlot* tmp = GetSlotFromCoord(coord + item->coords[i]);

			if (tmp == NULL || tmp->inventory_item)
			{
				if (tmp && tmp->inventory_item)
				{
					if ((*extra_item) == NULL)
					{
						*extra_item = tmp->inventory_item;
					}
					else if (*extra_item != tmp->inventory_item)
					{
						SetSlotsState(item, RED);
						return false;
					}
				}
				else if (!tmp)
				{
					return false;
				}
			}
		}
		return true;
	}
	//--------------
}

//Returns a pointer to the slot giving it's coord in the inventory
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

//Returns the Coord that the item would have if placed on the inventory;
iPoint GuiInventory::GetCoordFromItem(GuiItem* item)
{
	iPoint ret = item->GetPivotPosition();
	ret = ScreenToSlot(ret);
	
	return ret;
}

//Checks if the coord exists in the inventory space
bool GuiInventory::CoordExist(iPoint& coord)
{
	if (coord.x >= 0 && coord.x < columns && coord.y >= 0 && coord.y < rows)
	{
		return true;
	}

	return false;
}

//Deletes all items (only for this prototype)
void GuiInventory::CleanItems()
{
	list<GuiItem*>::iterator it = items.begin();
	for (; it != items.end(); it++)
	{
		RELEASE(*it);
	}

	items.clear();
}

//Slot coloring
void GuiInventory::SetSlotsState(GuiItem* item, SLOT_STATE state)
{
	for (int i = 0; i < item->size; i++)
	{
		GuiSlot* slot = GetSlotFromCoord(item->coords[i] + GetCoordFromItem(item));
		if (slot)
			slot->state = state;
	}
}