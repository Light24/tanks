#pragma once
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
	virtual void Draw(sf::RenderWindow *in_RenderWindow) override;
	virtual void Update(const sf::Time &in_Time) override;
	virtual void HandleEvent(const sf::Event &in_Event) override;

public:
	void createWorldWalls(const ConfigManager *configManager);

private:
	GameObject *GetNearestIntersectX(const GameObject *in_Object, const sf::Time in_Time) const;
	GameObject *GetNearestIntersectY(const GameObject *in_Object, const sf::Time in_Time) const;

private:
	ArtificialIntelligence in_ArtificialIntelligence;
	Player *m_Player;
};
