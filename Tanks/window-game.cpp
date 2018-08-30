#include "window-game.h"
#include "widget-game.h"

WindowGame::WindowGame(Engine *in_Engine, const sf::Vector2f &in_Pos, const sf::Vector2f &in_Size) : Window<Widget>(in_Pos, in_Size)
{
	WidgetGame *widgetGame = new WidgetGame(in_Engine, sf::Vector2f(100, 100), sf::Vector2f(200, 200));
	AddWidget(widgetGame);
}


WindowGame::~WindowGame()
{
}