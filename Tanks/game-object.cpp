#include "game-object.h"
#include "config.h"
#include "tank.h"
#include "wall.h"
#include "missile.h"

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

GameObject::GameObject(const boost::property_tree::ptree &in_Json) : m_Velocity(sf::Vector2f(0, 0)), m_Group(GROUP_NONE), m_Prototype(NULL)
{
	id.Generate();

	boost::property_tree::ptree properties = in_Json.get_child("properties");

	const int subtype = properties.get<int>("subtype");
	if (subtype < Object_Subtype_First || subtype > Object_Subtype_Last)
		throw "Error create Object";
	SetSubtype(subtype);

	sf::Vector2f size;
	size.x = properties.get<float>("width", 0);
	size.y = properties.get<float>("height", 0);
	SetSize(size);

	m_Damage = properties.get<int>("damage", 0);
	m_Health = properties.get<int>("health");
	m_MaxVelocity = properties.get<float>("velocity", 0);

	SetTexture(in_Json);

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
	if (GetMaxVelocity() == 0)
		return;

	if (m_Direction.x == 0 && m_Direction.y == 0)
		setDirectionImpl(sf::Vector2f(1, 0));

	if (m_Velocity.x == 0 && m_Velocity.y == 0)
		return;

	sf::Vector2f direction;
	direction.x = m_Velocity.x == 0 ? 0 : (m_Velocity.x < 0 ? -1 : 1);
	direction.y = m_Velocity.y == 0 ? 0 : (m_Velocity.y < 0 ? -1 : 1);

	setDirectionImpl(direction);
}

void GameObject::setDirectionImpl(const sf::Vector2f &in_Direction)
{
	if (in_Direction == m_Direction)
		return;

	m_Direction = in_Direction;

	if (m_Direction.x > 0)
		GetAnimation()->SetAnimationType(Animation_Type::Right);
	if (m_Direction.x < 0)
		GetAnimation()->SetAnimationType(Animation_Type::Left);
	if (m_Direction.y > 0)
		GetAnimation()->SetAnimationType(Animation_Type::Bottom);
	if (m_Direction.y < 0)
		GetAnimation()->SetAnimationType(Animation_Type::Top);
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

const GameObject *GameObject::Create(const boost::property_tree::ptree &in_Json)
{
	int type = in_Json.get_child("properties").get<int>("type");
	
	return CreateImpl((Object_Type) type, in_Json);
}

GameObject *GameObject::CreateImpl(const Object_Type in_Type, const boost::property_tree::ptree &in_Json)
{
	GameObject *object;
	try {
		switch (in_Type)
		{
			case Object_Type::Object_Type_Tank:
				object = new Tank(in_Json);
				break;

			case Object_Type::Object_Type_Wall:
				object = new Wall(in_Json);
				break;

			case Object_Type::Object_Type_Missile:
				object = new Missile(in_Json);
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
	Object::Update(in_Time);
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

