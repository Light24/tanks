#pragma once
#include "SFML/Graphics.hpp"

class Object
{
public:
	Object(const char *in_TexturePath);
	Object(const sf::Vector2f &in_Pos = sf::Vector2f(0, 0), const sf::Vector2f &in_Size = sf::Vector2f(0, 0));
	Object(const Object *in_Object);
	virtual ~Object();

public:
	Object *GetParent() const;
	void SetParent(Object *in_Parent);

	sf::Vector2f GetPos() const;
	virtual void SetPos(const sf::Vector2f &in_Pos);

	sf::Vector2f GetSize() const;
	void SetSize(const sf::Vector2f &in_Size);

	bool SetTexture(const char *in_TexturePath);

	sf::Vector2f GetAbsolutePos() const;

	bool CheckIntersect(const sf::Vector2f &in_Pos) const;

public:
	virtual void Draw(sf::RenderWindow *in_RenderWindow);
	virtual void Update(const sf::Time &in_Time) = 0;

	void CalculateSpritePos();

private:
	void calculateSpriteSize();

private:
	Object *m_Parent;

	sf::Vector2f m_Pos;
	sf::Vector2f m_Size;

	sf::Texture m_Texture;
	sf::Sprite m_Sprite;
};
