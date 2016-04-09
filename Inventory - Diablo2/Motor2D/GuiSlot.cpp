#include "GuiSlot.h"
#include "j1App.h"
#include "j1Render.h"
#include "GuiSlot.h"

GuiSlot::GuiSlot(iPoint p, SDL_Rect r, GuiElement* par, j1Module* list)
	:GuiElement({ r.x, r.y }, r, GUI_SLOT, par, list),
	coords(p), inventory_item(NULL)
{

}

GuiSlot::~GuiSlot()
{}

void GuiSlot::Update(GuiElement* hover, GuiElement* focus)
{
}

void GuiSlot::Draw()
{
	if (inventory_item)
	{
		SDL_Rect r = GetScreenRect();
		App->render->DrawQuad(r, 0, 0, 100, 50, true, false);
	}
}