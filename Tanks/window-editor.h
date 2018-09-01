#pragma once
#include "window.h"
#include "engine.h"
#include "widget-templates.h"
#include "widget-game-editor.h"

class WindowEditor : public Window<Widget>
{
public:
	WindowEditor(Engine *in_Engine, const sf::Vector2f &in_Pos, const sf::Vector2f &in_Size);
	~WindowEditor();

private:
	Object *onMoveBeginListener(Object *in_Object, const sf::Event &in_Event);
	void onMovingEndListener(Object *in_Object, const sf::Event &in_Event);
	void onMoveListener(Object *in_Object, const sf::Event &in_Event);

	void loadLevel();
	void saveLevel();

private:
	Engine *m_Engine;

	WidgetGameEditor *m_WidgetGameEditor;
	WidgetTemplates *m_WidgetTemplates;
};
