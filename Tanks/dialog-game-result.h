#pragma once
#include "window.h"
#include "button.h"

class DialogGameResult : public Window
{
public:
	DialogGameResult(const bool in_LevelComplete, const sf::Vector2f &in_Pos, const sf::Vector2f &in_Size);
	~DialogGameResult();

private:
	void OnExitListener(Button *in_Button);
	void OnNextLevelListener(Button *in_Button);
	void OnRestartListener(Button *in_Button);
};
