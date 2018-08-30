#pragma once
#include <map>
#include <random>

#include "object.h"

#define debug_assert(str) throw(str);


struct ID
{
static const int ID_SIZE = 32;

public:
	ID()
	{
		Generate();
	}

	~ID()
	{
	}

	void Generate()
	{
		const char *alphanum = ("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
	
		const size_t num = rand() % strlen(alphanum);
		for (size_t i = 0; i != ID_SIZE; ++i)
			m_Id[i] = alphanum[num];
	}

private:
	char m_Id[ID_SIZE];
};

enum Object_Type
{
	Object_Type_First = 0,
	Object_Type_Tank = Object_Type_First,
	Object_Type_Invulnerable_Wall,
	Object_Type_Wall,
	Object_Type_Last = Object_Type_Wall
};

const int GROUP_NONE     = 0;
const int GROUP_PLAYER   = 1;
const int GROUP_COMPUTER = 2;

class GameObject : public Object
{
public:
	GameObject(const char *in_Buf);
	GameObject(const GameObject *in_GameObject);
	virtual ~GameObject(void);

	static const GameObject *Create(const char *in_Buf);
	virtual GameObject *Clone() const = 0;

public:
	sf::Vector2f GetVelocity() const;
	void SetVelocity(const sf::Vector2f &in_Velocity);

	sf::Vector2f GetDirection() const;

	size_t GetGroup() const;
	void SetGroup(size_t in_Group);

	void SetType(size_t in_Type);
	Object_Type GetType() const;

	int GetHealth() const;

	bool CheckIntersect(const GameObject *in_Object, const sf::Time in_Timeout) const;
	virtual void OnIntersect(GameObject *in_GameObject) = 0;

	bool CheckIntersectX(const GameObject *in_Object, const sf::Time in_Timeout) const;
	bool CheckIntersectY(const GameObject *in_Object, const sf::Time in_Timeout) const;

	virtual void Update(const sf::Time &in_Time) override;

private:
	void calculateDirection();

	static GameObject *CreateImpl(const Object_Type in_Type, const char *in_Buf);

private:
	ID id;
	Object_Type m_Type;
	const GameObject *m_Prototype;

	size_t m_Group;

	sf::Vector2f m_Velocity;
	sf::Vector2f m_Direction;

	int m_Damage;
	size_t m_Health;
};
