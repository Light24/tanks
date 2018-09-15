#include "engine.h"
#include "SFML/System/Time.hpp"
#include "window-game.h"
#include "menu-window.h"
#include "texture-manager.h"

#include <stdio.h>

Engine::Engine(void) : m_Size(1600, 800)
{
	// TextureManager::GetInstance()->SetTextureDir("C:/C++/Tanks/x64/Debug/");
	TextureManager::GetInstance()->SetTextureDir("data/images/");

	m_Window = new sf::RenderWindow(sf::VideoMode(GetSize().x, GetSize().y), "Tanks");

	GetConfigManager()->LoadGameObjects("objects.txt");
}

Engine::~Engine(void)
{
	if (m_Window)
	{
		delete m_Window;
		m_Window = NULL;
	}

	for (size_t i = 0; i != m_Windows.size(); ++i)
		delete m_Windows[i];
	m_Windows.clear();

	destroyObjectsDeffered();
}

void Engine::Update(const sf::Time &in_Time)
{
	if (!m_Windows.size())
		return;

	auto window = m_Windows[m_Windows.size() - 1];
	window->Update(in_Time);
	/*
	for (size_t i = 0; i != m_Windows.size(); ++i)
	{
		auto window = m_Windows[i];
		window->Update(in_Time);
	}
	*/
}

void Engine::HandleEvents()
{
	sf::Event event;
	while (m_Window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_Window->close();

		if (!m_Windows.size())
			continue;

		auto window = m_Windows[m_Windows.size() - 1];
		window->HandleEvent(event);
		/*
		for (size_t i = 0; i != m_Windows.size(); ++i)
		{
			auto window = m_Windows[i];
			window->HandleEvent(event);
		}
		*/
	}
}

void Engine::Draw()
{
	m_Window->clear();
	if (m_Windows.size())
	{
		auto window = m_Windows[m_Windows.size() - 1];
		window->Draw(m_Window);
	}
	/*for (size_t i = 0; i != m_Windows.size(); ++i)
	{
		m_Window->setView(m_Window->getDefaultView());

		auto window = m_Windows[i];
		window->Draw(m_Window);
	}*/
	m_Window->display();
}

void Engine::Execute()
{
	/*Window *gameWindow = new WindowGame(this, sf::Vector2f(0, 0), GetSize());
	gameWindow->SetTexture("background.png");
	ChangeWindow(gameWindow);*/

	Window *menuWindow = new MenuWindow(this, sf::Vector2f(0, 0), GetSize());
	menuWindow->SetTexture("background.png");
	AddWindow(menuWindow);

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
	return ConfigManager::GetInstance();
}

void Engine::Close()
{
	m_Window->close();
}

void Engine::AddWindow(Window *in_Window)
{
	m_Windows.push_back(in_Window);
}

void Engine::RemoveWindow(Container *in_Window)
{
	int num = -1;
	for (size_t i = 0; i != m_Windows.size(); ++i)
	{
		if (m_Windows[i] != in_Window)
			continue;

		num = i;
		break;
	}
	if (num == -1)
		return;

	for (size_t i = num; i != (m_Windows.size() - 1); ++i)
		m_Windows[i] = m_Windows[i + 1];

	m_Windows.pop_back();
	m_DestroyableObjects.push_back(in_Window);
}

void Engine::ChangeWindow(Window *in_Window)
{
	if (m_Windows.size())
		RemoveWindow(m_Windows[m_Windows.size() - 1]);

	AddWindow(in_Window);
}

void Engine::destroyObjectsDeffered()
{
	if (!m_DestroyableObjects.size())
		return;

	for (size_t i = 0; i != m_DestroyableObjects.size(); ++i)
		delete m_DestroyableObjects[i];
	m_DestroyableObjects.clear();
}
