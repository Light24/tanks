#pragma once
#include "window.h"
#include "engine.h"
#include "widget-templates.h"
#include "widget-game-editor.h"

class WindowEditor : public Window
{
public:
	WindowEditor(Engine *in_Engine, const sf::Vector2f &in_Pos, const sf::Vector2f &in_Size);
	~WindowEditor();

public:
	virtual void HandleEvent(const sf::Event &in_Event) override;

private:
	Object *onMoveBeginListener(Object *in_Object, const sf::Event &in_Event);
	void onMovingEndListener(Object *in_Object, const sf::Event &in_Event);
	void onMoveListener(Object *in_Object, const sf::Event &in_Event);

	void loadLevel();
	void saveLevel();


	const void setShiftPressed(bool isPressed);
	bool isShiftPressed() const;

private:
	Engine *m_Engine;

	WidgetGameEditor *m_WidgetGameEditor;
	WidgetTemplates *m_WidgetTemplates;

	bool m_IsShiftPressed;
};
