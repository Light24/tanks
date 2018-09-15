#pragma once
#include "window.h"
#include "SFML/Graphics.hpp"
#include "engine.h"

class Engine;
class WindowGame : public Window
{
public:
	WindowGame(Engine *in_Engine, const sf::Vector2f &in_Pos, const sf::Vector2f &in_Size);
	virtual ~WindowGame();

public:
	virtual void Update(const sf::Time &in_Time) override;
	virtual void HandleEvent(const sf::Event &in_Event) override;

	void OnPlayerHealthChanged(const size_t in_HealthCount);
	void OnEnemyCountChanged(const size_t in_EnemyCount);

private:
	Engine *m_Engine;

	bool m_LevelCompleate;
	bool m_LevelFailed;
};
