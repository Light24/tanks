#include "widget-game-editor.h"

WidgetGameEditor::WidgetGameEditor(Engine *in_Engine, const sf::Vector2f &in_Pos, const sf::Vector2f &in_Size) : ContainerMoving<Object>(in_Pos, in_Size)
{
}

WidgetGameEditor::~WidgetGameEditor()
{
}

void WidgetGameEditor::SaveLevel(Engine *in_Engine)
{
	// in_Engine->GetConfigManager()->Save()
}
