#include "GuiItem.h"
#include "j1App.h"
#include "j1Input.h"
#include "GuiSlot.h"
#include "GuiInventory.h"
#include "j1Gui.h"
#include "j1Render.h"



GuiItem::GuiItem(int s, iPoint* coord, SDL_Rect r) 
	:GuiElement({ 0, 0 }, r, GUI_ITEM, NULL, NULL)
	, image({ 0, 0 }, r, this, NULL)
{
	size = s;
	coords = new iPoint[size];
	reference_slot = NULL;
	inventory = NULL;
	pivot = { ITEM_SECTION_SIZE / 2, ITEM_SECTION_SIZE / 2 };

	for (int i = 0; i < s; i++)
	{
		coords[i] = coord[i];
	}

	draggable = true;
}

GuiItem::~GuiItem()
{
	delete[] coords;
}

void GuiItem::Draw()
{
	image.Draw();
}

void GuiItem::DrawDebug()
{
	image.DrawDebug();

	iPoint tmp = GetPivotPosition();
	
	App->render->DrawQuad({ tmp.x, tmp.y, 2, 2 }, 0, 255, 0, 1000, true, false);

}

void GuiItem::Update(GuiElement* hover, GuiElement* focus, GuiItem* dragged_item)
{
	if (!dragged_item)
	{
		if (CheckCollision(App->input->GetMousePosition()))
		{
			inventory->SetSlotsState(this, GREEN);
			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
			{
				dragging = true;
				//NOT sure if using this here
				App->gui->dragged_item = this;
				FreeSlots();
			}
		}
	}


	if (dragging)
	{
		iPoint tmp = App->input->GetMousePosition();
		tmp.x -= GetLocalRect().w / 2;
		tmp.y -= GetLocalRect().h / 2;

		SetLocalPosition(tmp);
	}
}

iPoint GuiItem::GetPivotPosition()
{
	iPoint ret = pivot;
	ret += GetScreenPosition();

	return ret;
}

void GuiItem::FreeSlots()
{
	for (int i = 0; i < size; i++)
	{
		GuiSlot* slot = inventory->GetSlotFromCoord(reference_slot->coords + coords[i]);
		if (slot)
			slot->inventory_item = NULL;
	}
}
