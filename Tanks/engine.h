#pragma once
#include "game-object.h"
#include "config.h"
#include "player.h"
#include "window.h"

class Engine
{
public:
	Engine(void);
	~Engine(void);

public:
	void Execute();

	void Update(const sf::Time &in_Time);
	void HandleEvents();
	void Draw();

	sf::Vector2f GetSize() const;
	void SetSize(const sf::Vector2f &in_Size);

	ConfigManager *GetConfigManager();

private:
	sf::Vector2f m_Size;

	sf::RenderWindow *m_Window;
	std::vector<Window<Widget> *> m_Windows;
	ConfigManager m_ConfigManager;
};

