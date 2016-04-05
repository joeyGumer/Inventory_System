#include "GuiInventory.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Gui.h"


SDL_Rect Slot::GetScreenRect()
{
	iPoint pos = parent->GetScreenPosition();

	SDL_Rect ret = local_rect;
	ret.x += pos.x - App->render->camera.x;
	ret.y += pos.y - App->render->camera.y;

	return ret;
}

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
			Slot tmp({ j, i }, rect, this);
			slots.push_back(tmp);
		}
	}
}

GuiInventory::~GuiInventory()
{}

void GuiInventory::Update()
{
	
}
void GuiInventory::Draw()
{
	image.Draw();
}

void GuiInventory::DrawDebug()
{
	image.DrawDebug();

	for (int i = 0; i < slots.size(); i++)
	{
		App->render->DrawQuad(slots[i].GetScreenRect(), 255, 0, 0, 1000, false);
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

	ret.x = pos.x * slot_width;
	ret.y = pos.y * slot_height;

	return ret;
}
