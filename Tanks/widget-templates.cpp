#include "widget-templates.h"
#include "game-object.h"


WidgetTemplates::WidgetTemplates(Engine *in_Engine, const sf::Vector2f &in_Pos, const sf::Vector2f &in_Size) : ContainerMoving<Object>(in_Pos, in_Size)
{
	m_Engine = in_Engine;

	for (size_t objectNum = Object_Type::Object_Type_First; objectNum != Object_Type::Object_Type_Last; ++objectNum)
	{
		// Special object
		if (objectNum == Object_Type::Object_Type_Invulnerable_Wall)
			continue;

		GameObject *gameObject = in_Engine->GetConfigManager()->Create_Object((Object_Type) objectNum);
		AddWidget(gameObject);
	}

	AddMoveBeginListener(PREPARE_MOVE_BEGIN_LISTENER(this, &WidgetTemplates::onMoveBegin));
}


WidgetTemplates::~WidgetTemplates()
{
}

Object *WidgetTemplates::onMoveBegin(Object *in_Object, const sf::Event &in_Event)
{
	Object *clonedObject = dynamic_cast<GameObject *>(in_Object)->Clone();
	AddWidget(dynamic_cast<GameObject *>(clonedObject));

	return clonedObject;
}
