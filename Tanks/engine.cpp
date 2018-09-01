#include "engine.h"
#include "SFML/System/Time.hpp"
#include "window-game.h"
#include "menu-window.h"
#include "texture-manager.h"

#include <stdio.h>

Engine::Engine(void) : m_Size(800, 400)
{
	TextureManager::GetInstance()->SetTextureDir("C:/C++/Tanks/x64/Debug/");

	m_Window = new sf::RenderWindow(sf::VideoMode(GetSize().x, GetSize().y), "Tanks");

	m_ConfigManager.LoadGameObjects("objects.txt");
}

Engine::~Engine(void)
{
	if (m_Window)
	{
		delete m_Window;
		m_Window = NULL;
	}
}

void Engine::Update(const sf::Time &in_Time)
{
	for (size_t i = 0; i != m_Windows.size(); ++i)
	{
		auto window = m_Windows[i];
		window->Update(in_Time);
	}
}

void Engine::HandleEvents()
{
	sf::Event event;
	while (m_Window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_Window->close();

		for (size_t i = 0; i != m_Windows.size(); ++i)
		{
			auto window = m_Windows[i];
			window->HandleEvent(event);
		}
	}
}

void Engine::Draw()
{
	m_Window->clear();
	for (size_t i = 0; i != m_Windows.size(); ++i)
	{
		m_Window->setView(m_Window->getDefaultView());

		auto window = m_Windows[i];
		window->Draw(m_Window);
	}
	m_Window->display();
}

void Engine::Execute()
{
	/*Window<Widget> *gameWindow = new WindowGame(this, sf::Vector2f(0, 0), GetSize());
	gameWindow->SetTexture("background.png");
	ChangeWindow(gameWindow);*/

	Window<Widget> *menuWindow = new MenuWindow(this, sf::Vector2f(0, 0), GetSize());
	menuWindow->SetTexture("background.png");
	ChangeWindow(menuWindow);

	sf::Clock clock;
	sf::Time lastTime = clock.getElapsedTime();
	do {
		sf::Time time = clock.getElapsedTime();
		if ((time - lastTime).asMilliseconds() == 0)
			continue;

		HandleEvents();
		Update(time - lastTime);
		Draw();

		destroyObjectsDeffered();
		lastTime = time;
	} while (m_Window->isOpen());
}

sf::Vector2f Engine::GetSize() const
{
	return m_Size;
}

void Engine::SetSize(const sf::Vector2f &in_Size)
{
	m_Size = in_Size;
}

ConfigManager *Engine::GetConfigManager()
{
	return &m_ConfigManager;
}

void Engine::Close()
{
	m_Window->close();
}

void Engine::ChangeWindow(Window<Widget> *in_Window)
{
	for (size_t i = 0; i != m_Windows.size(); ++i)
		m_DestroyableObjects.push_back(m_Windows[i]);
	m_Windows.clear();

	m_Windows.push_back(in_Window);
}

void Engine::destroyObjectsDeffered()
{
	if (!m_DestroyableObjects.size())
		return;

	for (size_t i = 0; i != m_DestroyableObjects.size(); ++i)
		delete m_DestroyableObjects[i];
	m_DestroyableObjects.clear();
}
