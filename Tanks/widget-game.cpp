#include "widget-game.h"
#include "config.h"

WidgetGame::WidgetGame(Engine *in_Engine, const sf::Vector2f &in_Pos, const sf::Vector2f &in_Size) : Container(in_Pos, in_Size)
{
	const ConfigManager *configManager = in_Engine->GetConfigManager();

	createWorldWalls(configManager);

	GameObject *gameObject = configManager->Create_Object(Object_Type_Tank);
	m_Player = new Player(gameObject);

	AddWidget(gameObject);
}


WidgetGame::~WidgetGame()
{
}

void WidgetGame::createWorldWalls(const ConfigManager *configManager)
{
	GameObject *wall;

	wall = configManager->Create_Object(Object_Type_Invulnerable_Wall);
	wall->SetPos(sf::Vector2f(0, 0));
	wall->SetSize(sf::Vector2f(0, GetSize().y));
	AddWidget(wall);

	wall = configManager->Create_Object(Object_Type_Invulnerable_Wall);
	wall->SetPos(sf::Vector2f(0, GetSize().y));
	wall->SetSize(sf::Vector2f(GetSize().x, 0));
	AddWidget(wall);

	wall = configManager->Create_Object(Object_Type_Invulnerable_Wall);
	wall->SetPos(sf::Vector2f(0, 0));
	wall->SetSize(sf::Vector2f(GetSize().x, 0));
	AddWidget(wall);

	wall = configManager->Create_Object(Object_Type_Invulnerable_Wall);
	wall->SetPos(sf::Vector2f(GetSize().x, 0));
	wall->SetSize(sf::Vector2f(0, GetSize().y));
	AddWidget(wall);
}

void WidgetGame::Draw(sf::RenderWindow *in_RenderWindow)
{
	Container::Draw(in_RenderWindow);
}

void WidgetGame::Update(const sf::Time &in_Time)
{
	for (size_t i = 0; i != GetWidgetsCount(); ++i)
	{
		GameObject *gameObject = GetWidget(i);

		GameObject *nearestX = GetNearestIntersectX(gameObject, in_Time);
		if (nearestX)
		{
			gameObject->SetVelocity(sf::Vector2f(0, 0));
		}

		GameObject *nearestY = GetNearestIntersectY(gameObject, in_Time);
		if (nearestY)
		{
			gameObject->SetVelocity(sf::Vector2f(0, 0));
		}

		gameObject->SetPos(sf::Vector2f(gameObject->GetPos().x + gameObject->GetVelocity().x * in_Time.asMilliseconds(), gameObject->GetPos().y + gameObject->GetVelocity().y * in_Time.asMilliseconds()));
	}

	Container::Update(in_Time);
}

void WidgetGame::HandleEvent(const sf::Event &in_Event)
{
	m_Player->HandleEvent(in_Event);
	Container::HandleEvent(in_Event);
}

GameObject *WidgetGame::GetNearestIntersectX(const GameObject *in_Object, const sf::Time in_Time) const
{
	if (in_Object->GetVelocity().x == 0)
		return NULL;

	GameObject *intersectX(NULL);
	for (size_t i = 0; i != GetWidgetsCount(); ++i)
	{
		GameObject *object = GetWidget(i);
		if (intersectX &&
			fabs(in_Object->GetPos().x - object->GetPos().x) > fabs(in_Object->GetPos().x - intersectX->GetPos().x))
			continue;

		if (!in_Object->CheckIntersectX(object, in_Time))
			continue;

		intersectX = object;
	}

	return intersectX;
}

GameObject *WidgetGame::GetNearestIntersectY(const GameObject *in_Object, const sf::Time in_Time) const
{
	if (in_Object->GetVelocity().y == 0)
		return NULL;

	GameObject *intersectY(NULL);
	for (size_t i = 0; i != GetWidgetsCount(); ++i)
	{
		GameObject *object = GetWidget(i);
		if (intersectY &&
			fabs(in_Object->GetPos().x - object->GetPos().x) > fabs(in_Object->GetPos().x - intersectY->GetPos().x))
			continue;

		if (!in_Object->CheckIntersectY(object, in_Time))
			continue;

		intersectY = object;
	}

	return intersectY;
}
