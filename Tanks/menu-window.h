#pragma once
#include "container-moving.h"
#include "engine.h"
#include "button.h"

class MenuWindow : public Window
{
public:
	MenuWindow(Engine *in_Engine, const sf::Vector2f &in_Pos, const sf::Vector2f &in_Size);
	~MenuWindow();

private:
	void onStartClicked(Button *in_Button);
	void onEditorClicked(Button *in_Button);
	void onExitClicked(Button *in_Button);

private:
	Engine *m_Engine;
};
