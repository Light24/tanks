#pragma once
#include "widget.h"
#include "container-moving.h"
#include "engine.h"

class WidgetTemplates : public ContainerMoving<Object>
{
public:
	WidgetTemplates(Engine *in_Engine, const sf::Vector2f &in_Pos, const sf::Vector2f &in_Size);
	~WidgetTemplates();

private:
	Object *onMoveBegin(Object *in_Object, const sf::Event &in_Event);

private:
	Engine *m_Engine;
};
