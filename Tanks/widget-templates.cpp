#include "widget-templates.h"
#include "game-object.h"


WidgetTemplates::WidgetTemplates(Engine *in_Engine, const sf::Vector2f &in_Pos, const sf::Vector2f &in_Size) : ContainerMoving<Object>(in_Pos, in_Size)
{
	m_Engine = in_Engine;

	in_Engine->GetConfigManager()->EnumeratePrototypes([this, &in_Engine](const GameObject *in_Object) -> bool {
		// Special object
		if (in_Object->GetSubtype() == Object_Subtype::Object_Subtype_Invulnerable_Wall)
			return false;

		GameObject *gameObject = in_Engine->GetConfigManager()->Create_Object(in_Object->GetSubtype());
		if (!gameObject)
			return false;

		AddWidget(gameObject);
		return false;
	});

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

#define OBJECTS_OFFSET_X 10
#define OBJECTS_OFFSET_Y 10

void WidgetTemplates::AddWidget(Object *in_Widget)
{
	sf::Vector2f pos = in_Widget->GetPos();
	if (GetWidgetsCount())
	{
		const Object *object = GetWidget(GetWidgetsCount() - 1);
		pos = object->GetPos();
		if ((object->GetPos().x + object->GetSize().x + OBJECTS_OFFSET_X) + in_Widget->GetSize().x < GetSize().x)
		{
			pos.x = (object->GetPos().x + object->GetSize().x + OBJECTS_OFFSET_X);
		}
		else
		{
			pos.x = 0;
			pos.y = (object->GetPos().y + object->GetSize().y + OBJECTS_OFFSET_Y);
		}
	}
	in_Widget->SetPos(pos);

	ContainerMoving::AddWidget(in_Widget);
}
