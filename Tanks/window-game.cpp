#include "window-game.h"
#include "widget-game.h"
#include "widget-game-statistic.h"
#include "dialog-game-result.h"

WindowGame::WindowGame(Engine *in_Engine, const sf::Vector2f &in_Pos, const sf::Vector2f &in_Size) : Window(in_Pos, in_Size), m_LevelCompleate(false), m_LevelFailed(false)
{
	m_Engine = in_Engine;

	WidgetGame *widgetGame = new WidgetGame(in_Engine, sf::Vector2f(in_Engine->GetSize().x * 0.1, 0), sf::Vector2f(in_Engine->GetSize().x * 0.8, in_Engine->GetSize().y));
	AddWidget(widgetGame);

	WidgetGameStatistic *widgetGameStatistic = new WidgetGameStatistic(sf::Vector2f(in_Engine->GetSize().x * 0.9, 0), sf::Vector2f(in_Engine->GetSize().x * 0.1, in_Engine->GetSize().y));
	AddWidget(widgetGameStatistic);

	widgetGame->SetPlayerHealthListener([this, widgetGameStatistic](size_t in_Health) -> void { widgetGameStatistic->OnPlayerHealthChanged(in_Health);  OnPlayerHealthChanged(in_Health); });
}

WindowGame::~WindowGame()
{
}


void WindowGame::Update(const sf::Time &in_Time)
{
	if (m_LevelCompleate || m_LevelFailed)
		return;

	Window::Update(in_Time);
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

void WindowGame::OnPlayerHealthChanged(const size_t in_HealthCount)
{
	if (in_HealthCount != 0)
		return;

	m_LevelFailed = true;

	sf::Vector2f size(600, 400);
	DialogGameResult *dialogGameResult = new DialogGameResult(false, sf::Vector2f((GetSize().x - size.x) / 2, (GetSize().y - size.y) / 2), size);
	AddWidget(dialogGameResult, true);
}

void WindowGame::OnEnemyCountChanged(const size_t in_EnemyCount)
{
	if (in_EnemyCount != 0)
		return;

	m_LevelCompleate = true;

	sf::Vector2f size(600, 400);
	DialogGameResult *dialogGameResult = new DialogGameResult(true, sf::Vector2f((GetSize().x - size.x) / 2, (GetSize().y - size.y) / 2), size);
	AddWidget(dialogGameResult, true);
}
