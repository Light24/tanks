#include "object.h"


Object::Object(const char *in_TexturePath) : m_Pos(sf::Vector2f(0, 0)), m_Size(sf::Vector2f(0, 0)), m_Parent(NULL)
{
	SetTexture(in_TexturePath);
}

bool Object::SetTexture(const char *in_TexturePath)
{
	m_Texture.loadFromFile(in_TexturePath ? in_TexturePath : "");
	m_Sprite.setTexture(m_Texture);

	calculateSpriteSize();
	return true;
}

Object::Object(const sf::Vector2f &in_Pos, const sf::Vector2f &in_Size) : m_Pos(in_Pos), m_Size(in_Size), m_Parent(NULL)
{
	SetTexture(NULL);
}

Object::Object(const Object *in_Object)
{
	m_Texture = in_Object->m_Texture;
	m_Sprite = in_Object->m_Sprite;

	SetParent(const_cast<Object *>(in_Object)->GetParent());
	SetPos(in_Object->GetPos());
	SetSize(in_Object->GetSize());
}

Object::~Object()
{

}

Object *Object::GetParent() const
{
	return m_Parent;
}

void Object::SetParent(Object *in_Parent)
{
	m_Parent = in_Parent;
	CalculateSpritePos();
}

sf::Vector2f Object::GetPos() const
{
	return m_Pos;
}

void Object::SetPos(const sf::Vector2f &in_Pos)
{
	m_Pos = in_Pos;
	CalculateSpritePos();
}

sf::Vector2f Object::GetSize() const
{
	return m_Size;
}

void Object::SetSize(const sf::Vector2f &in_Size)
{
	m_Size = in_Size;
	calculateSpriteSize();
}

bool Object::CheckIntersect(const sf::Vector2f &in_Pos) const
{
	const sf::Vector2f pos = GetAbsolutePos();
	const sf::Vector2f size = GetSize();

	return ((in_Pos.x >= pos.x && in_Pos.x <= pos.x + size.x)
		&& (in_Pos.y >= pos.y && in_Pos.y <= pos.y + size.y));
}

void Object::Draw(sf::RenderWindow *in_RenderWindow)
{
	in_RenderWindow->draw(m_Sprite);
}

sf::Vector2f Object::GetAbsolutePos() const
{
	sf::Vector2f pos(GetPos());

	const Object *parent(this);
	while (parent && (parent = parent->GetParent()))
	{
		pos.x += parent->GetPos().x;
		pos.y += parent->GetPos().y;
	}

	return pos;
}

void Object::calculateSpriteSize()
{
	m_Sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(m_Sprite.getTexture()->getSize().x, m_Sprite.getTexture()->getSize().y)));
	m_Sprite.setScale(sf::Vector2f(GetSize().x / m_Sprite.getTexture()->getSize().x, GetSize().y / m_Sprite.getTexture()->getSize().y)); // sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(GetSize().x, GetSize().y)));
}

void Object::CalculateSpritePos()
{
	m_Sprite.setPosition(GetAbsolutePos());
}
