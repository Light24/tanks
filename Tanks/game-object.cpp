#include "game-object.h"
#include "config.h"
#include "tank.h"
#include "wall.h"

#include <stdio.h>
#include <string>

Object_Type GetType(Object_Subtype in_Subtype)
{
	switch (in_Subtype)
	{
		case Object_Subtype_Player:
		case Object_Subtype_Tank:
			return Object_Type_Tank;
		case Object_Subtype_Invulnerable_Wall:
		case Object_Subtype_Wall:
			return Object_Type_Wall;
		case Object_Subtype_Missile:
			return Object_Type_Missile;
	}

	return Object_Type_First;
}

GameObject::GameObject(const char *in_Buf) : m_Velocity(sf::Vector2f(0, 0)), m_Group(GROUP_NONE), m_Prototype(NULL)
{
	id.Generate();

	const char *pBuf = in_Buf;

	int subtype;
	if (!(pBuf = Config_Parser::Read(pBuf, subtype)))
		throw "Error create Object";
	SetSubtype(subtype);

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

	if (!(pBuf = Config_Parser::Read(pBuf, m_MaxVelocity)))
		throw "Error create Object";

	std::string textureName;
	if (!(pBuf = Config_Parser::Read(pBuf, textureName)))
		throw "Error create Object";
	SetTexture(textureName.c_str());

	calculateDirection();
}

GameObject::GameObject(const GameObject *in_GameObject) : Object(in_GameObject)
{
	id.Generate();
	m_Subtype = in_GameObject->m_Subtype;
	m_Prototype = in_GameObject->m_Prototype ? in_GameObject->m_Prototype : in_GameObject;
	m_Group = in_GameObject->m_Group;
	m_MaxVelocity = in_GameObject->m_MaxVelocity;
	m_Velocity = in_GameObject->m_Velocity;
	m_Direction = in_GameObject->m_Direction;
	m_Damage = in_GameObject->m_Damage;
	m_Health = in_GameObject->m_Health;
}

GameObject::~GameObject(void)
{
}


float GameObject::GetMaxVelocity() const
{
	return m_MaxVelocity;
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

void GameObject::SetSubtype(size_t in_Subtype)
{
	if (in_Subtype < Object_Subtype_First || in_Subtype > Object_Subtype_Last)
		throw "Invalid subtype";

	m_Subtype = (Object_Subtype) in_Subtype;
}

Object_Subtype GameObject::GetSubtype() const
{
	return m_Subtype;
}

int GameObject::GetHealth() const
{
	return m_Health;
}

const GameObject *GameObject::Create(const char *in_Buf)
{
	const char *pBuf = in_Buf;

	int subtype;
	if (!(pBuf = Config_Parser::Read(pBuf, subtype)))
		return NULL;
	if (subtype < Object_Subtype_First || subtype > Object_Subtype_Last)
		return NULL;
	
	return CreateImpl(GetType((Object_Subtype) subtype), in_Buf);
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
	if (fabs((GetPos().y + GetSize().y / 2) - (in_Object->GetPos().y + in_Object->GetSize().y / 2)) >= GetSize().y / 2 + in_Object->GetSize().y / 2)
		return false;

	if (GetPos().x + GetSize().x <= in_Object->GetPos().x)
		return (GetPos().x + GetSize().x + GetVelocity().x * in_Timeout.asMilliseconds() > in_Object->GetPos().x + in_Object->GetVelocity().x * in_Timeout.asMilliseconds());
	else if (in_Object->GetPos().x + in_Object->GetSize().x <= GetPos().x)
		return (in_Object->GetPos().x + in_Object->GetSize().x + in_Object->GetVelocity().x * in_Timeout.asMilliseconds() > GetPos().x + GetVelocity().x * in_Timeout.asMilliseconds());

	return false;
}

bool GameObject::CheckIntersectY(const GameObject *in_Object, const sf::Time in_Timeout) const
{
	if (fabs((GetPos().x + GetSize().x / 2) - (in_Object->GetPos().x + in_Object->GetSize().x / 2)) >= GetSize().x / 2 + in_Object->GetSize().x / 2)
		return false;

	if (GetPos().y + GetSize().y <= in_Object->GetPos().y)
		return (GetPos().y + GetSize().y + GetVelocity().y * in_Timeout.asMilliseconds() > in_Object->GetPos().y + in_Object->GetVelocity().y * in_Timeout.asMilliseconds());
	else if (in_Object->GetPos().y + in_Object->GetSize().y <= GetPos().y)
		return (in_Object->GetPos().y + in_Object->GetSize().y + in_Object->GetVelocity().y * in_Timeout.asMilliseconds() > GetPos().y + GetVelocity().y * in_Timeout.asMilliseconds());

	return false;
}

