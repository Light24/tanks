#include "game-object.h"
#include "config.h"
#include "tank.h"
#include "wall.h"

#include <stdio.h>
#include <string>

GameObject::GameObject(const char *in_Buf) : Object("image.png"), m_Velocity(sf::Vector2f(0, 0)), m_Group(GROUP_NONE), m_Prototype(NULL)
{
	id.Generate();

	const char *pBuf = in_Buf;

	std::string name;
	if (!(pBuf = Config_Parser::Read(pBuf, name)))
		throw "Error create Object";

	int type;
	if (!(pBuf = Config_Parser::Read(pBuf, type)))
		throw "Error create Object";
	SetType(type);

	sf::Vector2f size;
	if (!(pBuf = Config_Parser::Read(pBuf, size.x)))
		throw "Error create Object";
	if (!(pBuf = Config_Parser::Read(pBuf, size.y)))
		throw "Error create Object";
	SetSize(size);

	if (!(pBuf = Config_Parser::Read(pBuf, m_Damage)))
		throw "Error create Object";
	
	int health;
	if (!(pBuf = Config_Parser::Read(pBuf, health)))
		throw "Error create Object";
	m_Health = health;

	float velocity;
	if (!(pBuf = Config_Parser::Read(pBuf, velocity)))
		throw "Error create Object";

	calculateDirection();
}

GameObject::GameObject(const GameObject *in_GameObject) : Object(in_GameObject)
{
	id.Generate();
	m_Type = in_GameObject->m_Type;
	m_Prototype = in_GameObject->m_Prototype ? in_GameObject->m_Prototype : in_GameObject;
	m_Group = in_GameObject->m_Group;
	m_Velocity = in_GameObject->m_Velocity;
	m_Direction = in_GameObject->m_Direction;
	m_Damage = in_GameObject->m_Damage;
	m_Health = in_GameObject->m_Health;
}

GameObject::~GameObject(void)
{
}


sf::Vector2f GameObject::GetVelocity() const
{
	return m_Velocity;
}

void GameObject::SetVelocity(const sf::Vector2f &in_Velocity)
{
	m_Velocity = in_Velocity;
	calculateDirection();
}


sf::Vector2f GameObject::GetDirection() const
{
	return m_Direction;
}

void GameObject::calculateDirection()
{
	if (m_Direction.x == m_Direction.y == 0)
		m_Direction.x = 1;

	if (m_Velocity.x == m_Velocity.y == 0)
		return;

	m_Direction.x = m_Velocity.x == 0 ? 0 : (m_Velocity.x < 0 ? -1 : 1);
	m_Direction.y = m_Velocity.y == 0 ? 0 : (m_Velocity.y < 0 ? -1 : 1);
}


size_t GameObject::GetGroup() const
{
	return m_Group;
}

void GameObject::SetGroup(size_t in_Group)
{
	m_Group = in_Group;
}

void GameObject::SetType(size_t in_Type)
{
	if (in_Type < Object_Type_First || in_Type > Object_Type_Last)
		throw "Invalid type";

	m_Type = (Object_Type) in_Type;
}

Object_Type GameObject::GetType() const
{
	return m_Type;
}

int GameObject::GetHealth() const
{
	return m_Health;
}

const GameObject *GameObject::Create(const char *in_Buf)
{
	const char *pBuf = in_Buf;

	std::string name;
	if (!(pBuf = Config_Parser::Read(pBuf, name)))
		return NULL;
	
	int type;
	if (!(pBuf = Config_Parser::Read(pBuf, type)))
		return NULL;
	if (type < Object_Type_First || type > Object_Type_Last)
		return NULL;
	
	return CreateImpl((Object_Type) type, in_Buf);
}

GameObject *GameObject::CreateImpl(const Object_Type in_Type, const char *in_Buf)
{
	GameObject *object;
	try {
		switch (in_Type)
		{
			case Object_Type::Object_Type_Tank:
				object = new Tank(in_Buf);
				break;

			case Object_Type::Object_Type_Wall:
			case Object_Type::Object_Type_Invulnerable_Wall:
				object = new Wall(in_Buf);
				break;
		}
	}
	catch (...) {
		printf("Error create Object");
	}

	return object;
}

void GameObject::Update(const sf::Time &in_Time)
{
}

bool GameObject::CheckIntersectX(const GameObject *in_Object, const sf::Time in_Timeout) const
{
	if (fabs((GetPos().y + GetSize().y / 2) - (in_Object->GetPos().y + in_Object->GetSize().y / 2)) > GetSize().y / 2 + in_Object->GetSize().y / 2)
		return false;

	if (GetPos().x + GetSize().x <= in_Object->GetPos().x)
		return (GetPos().x + GetSize().x + GetVelocity().x * in_Timeout.asMilliseconds() > in_Object->GetPos().x + in_Object->GetVelocity().x * in_Timeout.asMilliseconds());
	else if (in_Object->GetPos().x + in_Object->GetSize().x <= GetPos().x)
		return (in_Object->GetPos().x + in_Object->GetSize().x + in_Object->GetVelocity().x * in_Timeout.asMilliseconds() > GetPos().x + GetVelocity().x * in_Timeout.asMilliseconds());

	return false;
}

bool GameObject::CheckIntersectY(const GameObject *in_Object, const sf::Time in_Timeout) const
{
	if (fabs((GetPos().x + GetSize().x / 2) - (in_Object->GetPos().x + in_Object->GetSize().x / 2)) > GetSize().x / 2 + in_Object->GetSize().x / 2)
		return false;

	if (GetPos().y + GetSize().y <= in_Object->GetPos().y)
		return (GetPos().y + GetSize().y + GetVelocity().y * in_Timeout.asMilliseconds() > in_Object->GetPos().y + in_Object->GetVelocity().y * in_Timeout.asMilliseconds());
	else if (in_Object->GetPos().y + in_Object->GetSize().y <= GetPos().y)
		return (in_Object->GetPos().y + in_Object->GetSize().y + in_Object->GetVelocity().y * in_Timeout.asMilliseconds() > GetPos().y + GetVelocity().y * in_Timeout.asMilliseconds());

	return false;
}

