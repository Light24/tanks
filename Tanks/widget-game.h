#pragma once
#include <functional>

#include "widget.h"
#include "game-object.h"
#include "widget-game.h"
#include "engine.h"

#include "artificial-intelligence.h"

class WidgetGame : public Container
{
public:
	WidgetGame(Engine *in_Engine, const sf::Vector2f &in_Pos, const sf::Vector2f &in_Size);
	virtual ~WidgetGame();

public:
	void SetPlayerHealthListener(GameObject::ObjectHealthListener in_PlayerHealthListener) { m_Player->GetObject()->SetPlayerHealthListener(in_PlayerHealthListener); }

	typedef std::function<void(const size_t in_Health)> EnemyCountListener;
	void SetEnemyCountListener(EnemyCountListener in_EnemyCountListener) { m_EnemyCountListener = in_EnemyCountListener; }

public:
	virtual void Draw(sf::RenderWindow *in_RenderWindow) override;
	virtual void Update(const sf::Time &in_Time) override;
	virtual void HandleEvent(const sf::Event &in_Event) override;

	virtual void AddWidget(Object *in_Widget, bool in_Top = false) override;
	virtual bool RemoveWidget(Object *in_Widget, bool in_Deleting = true) override;

private:
	void createWorldWalls(const ConfigManager *configManager);

private:
	GameObject *GetNearestIntersectX(const GameObject *in_Object, const sf::Time in_Time) const;
	GameObject *GetNearestIntersectY(const GameObject *in_Object, const sf::Time in_Time) const;

private:
	ArtificialIntelligence in_ArtificialIntelligence;
	Player *m_Player;

	EnemyCountListener m_EnemyCountListener;

	size_t m_EnemyCount;
};
