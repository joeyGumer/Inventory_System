#include "GuiSlot.h"
#include "j1App.h"
#include "j1Render.h"
#include "GuiSlot.h"

GuiSlot::GuiSlot(iPoint p, SDL_Rect r, GuiElement* par, j1Module* list)
	:GuiElement({ r.x, r.y }, r, GUI_SLOT, par, list),
	coords(p), inventory_item(NULL), state(DEFAULT)
{

}

GuiSlot::~GuiSlot()
{}

void GuiSlot::Update(GuiElement* hover, GuiElement* focus, GuiItem* dragged_item)
{
	state = DEFAULT;
}

void GuiSlot::Draw()
{
	switch (state)
	{
	case DEFAULT:
		break;
	case GREEN:
		App->render->DrawQuad(GetScreenRect(), 0, 100, 0, 50, true, false);
		break;
	case YELLOW:
		App->render->DrawQuad(GetScreenRect(), 200, 200, 0, 50, true, false);
		break;
	case RED:
		App->render->DrawQuad(GetScreenRect(), 200, 0, 0, 50, true, false);
		break;
	}
}