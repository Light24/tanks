#include "widget-game-editor.h"

WidgetGameEditor::WidgetGameEditor(Engine *in_Engine, const sf::Vector2f &in_Pos, const sf::Vector2f &in_Size) : ContainerMoving<Object>(in_Pos, in_Size)
{
}

WidgetGameEditor::~WidgetGameEditor()
{
}

#include "game-object.h"
void WidgetGameEditor::SaveLevel(Engine *in_Engine)
{
	for (size_t i = 0; i != GetWidgetsCount(); ++i)
	{
		const Object *object = GetWidget(i);
		object->GetPos();
		object->GetSize();
	}

	Container<GameObject> *container = dynamic_cast<Container<GameObject> *>(this);
	in_Engine->GetConfigManager()->SaveLevel("level_0.lvl", container);
}
