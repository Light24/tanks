#include "widget-game.h"
#include "config.h"

WidgetGame::WidgetGame(Engine *in_Engine, const sf::Vector2f &in_Pos, const sf::Vector2f &in_Size) : Container(in_Pos, in_Size), m_EnemyCountListener(NULL), m_EnemyCount(0)
{
	const ConfigManager *configManager = in_Engine->GetConfigManager();

	createWorldWalls(configManager);

	in_Engine->GetConfigManager()->LoadLevel("data/levels/level_0.lvl", this);

	GameObject *playerOwnedObject(NULL);
	for (size_t i = 0; i != GetWidgetsCount(); ++i)
	{
		if (dynamic_cast<GameObject *>(GetWidget(i))->GetSubtype() == Object_Subtype_Player)
		{
			playerOwnedObject = dynamic_cast<GameObject *>(GetWidget(i));
			break;
		}
	}
	m_Player = new Player(playerOwnedObject);
}


WidgetGame::~WidgetGame()
{
}

void WidgetGame::createWorldWalls(const ConfigManager *configManager)
{
	GameObject *wall;

	wall = configManager->Create_Object(Object_Subtype_Invulnerable_Wall);
	wall->SetPos(sf::Vector2f(0, 0));
	wall->SetSize(sf::Vector2f(0, GetSize().y));
	AddWidget(wall);

	wall = configManager->Create_Object(Object_Subtype_Invulnerable_Wall);
	wall->SetPos(sf::Vector2f(0, GetSize().y));
	wall->SetSize(sf::Vector2f(GetSize().x, 0));
	AddWidget(wall);

	wall = configManager->Create_Object(Object_Subtype_Invulnerable_Wall);
	wall->SetPos(sf::Vector2f(0, 0));
	wall->SetSize(sf::Vector2f(GetSize().x, 0));
	AddWidget(wall);

	wall = configManager->Create_Object(Object_Subtype_Invulnerable_Wall);
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
	Container::Update(in_Time);

	for (size_t i = 0; i != GetWidgetsCount(); ++i)
	{
		GameObject *gameObject = (GameObject *) GetWidget(i);
		if (!gameObject->IsAlive())
			continue;

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

		if (nearestX)
		{
			gameObject->OnIntersect(nearestX);
			nearestX->OnIntersect(gameObject);
		}
		if (nearestY)
		{
			gameObject->OnIntersect(nearestY);
			nearestY->OnIntersect(gameObject);
		}
	}

	in_ArtificialIntelligence.Update(this, in_Time);

	for (size_t i = 0; i != GetWidgetsCount(); ++i)
	{
		GameObject *gameObject = (GameObject *)GetWidget(i);
		if (!gameObject->IsNeedRemove())
			continue;

		RemoveWidget(gameObject);
		--i;
	}
}

void WidgetGame::HandleEvent(const sf::Event &in_Event)
{
	Container::HandleEvent(in_Event);
	m_Player->HandleEvent(in_Event);
}

void WidgetGame::AddWidget(Object *in_Widget, bool in_Top)
{
	if (dynamic_cast<GameObject *>(in_Widget)->GetType() == Object_Type_Tank)
	{
		++m_EnemyCount;
		if (m_EnemyCountListener)
			m_EnemyCountListener(m_EnemyCount);
	}

	Container::AddWidget(in_Widget, in_Top);
}

bool WidgetGame::RemoveWidget(Object *in_Widget, bool in_Deleting)
{
	if (dynamic_cast<GameObject *>(in_Widget)->GetType() == Object_Type_Tank)
	{
		--m_EnemyCount;
		if (m_EnemyCountListener)
			m_EnemyCountListener(m_EnemyCount);
	}

	return Container::RemoveWidget(in_Widget, in_Deleting);;
}

GameObject *WidgetGame::GetNearestIntersectX(const GameObject *in_Object, const sf::Time in_Time) const
{
	if (in_Object->GetVelocity().x == 0)
		return NULL;

	GameObject *intersectX(NULL);
	for (size_t i = 0; i != GetWidgetsCount(); ++i)
	{
		GameObject *object = (GameObject *) GetWidget(i);
		if (!object->IsAlive())
			continue;

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
		GameObject *object = (GameObject *) GetWidget(i);
		if (!object->IsAlive())
			continue;

		if (intersectY &&
			fabs(in_Object->GetPos().x - object->GetPos().x) > fabs(in_Object->GetPos().x - intersectY->GetPos().x))
			continue;

		if (!in_Object->CheckIntersectY(object, in_Time))
			continue;

		intersectY = object;
	}

	return intersectY;
}
