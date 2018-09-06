#include "window-game.h"
#include "widget-game.h"

WindowGame::WindowGame(Engine *in_Engine, const sf::Vector2f &in_Pos, const sf::Vector2f &in_Size) : Window(in_Pos, in_Size)
{
	m_Engine = in_Engine;

	WidgetGame *widgetGame = new WidgetGame(in_Engine, sf::Vector2f(in_Engine->GetSize().x * 0.1, 0), sf::Vector2f(in_Engine->GetSize().x - in_Engine->GetSize().x * 0.2, in_Engine->GetSize().y));
	AddWidget(widgetGame);
}

WindowGame::~WindowGame()
{
}


void WindowGame::HandleEvent(const sf::Event &in_Event)
{
	Window::HandleEvent(in_Event);

	if (in_Event.type == sf::Event::KeyPressed)
	{
		if (in_Event.key.code == sf::Keyboard::Escape)
		{
			m_Engine->RemoveWindow(this);
			return;
		}
	}
}
