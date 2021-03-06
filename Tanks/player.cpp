#include "player.h"
#include "tank.h"


Player::Player(GameObject *in_Object) : m_Object(in_Object)
{
	in_Object->SetGroup(GROUP_PLAYER);
	in_Object->SetObjectDestroyListener(PREPARE_DESTROY_LISTENER(this, &Player::OnObjectDestroy));
}


Player::~Player()
{
}

bool Player::HandleEvent(const sf::Event &in_Event)
{
	if (!GetObject())
		return false;

	if (in_Event.type == sf::Event::KeyPressed)
	{
		switch (in_Event.key.code)
		{
			case sf::Keyboard::Left:
				m_Object->SetVelocity(sf::Vector2f(-1 * m_Object->GetMaxVelocity(), 0));
				return true;
			case sf::Keyboard::Right:
				m_Object->SetVelocity(sf::Vector2f(1 * m_Object->GetMaxVelocity(), 0));
				return true;
			case sf::Keyboard::Up:
				m_Object->SetVelocity(sf::Vector2f(0, -1 * m_Object->GetMaxVelocity()));
				return true;
			case sf::Keyboard::Down:
				m_Object->SetVelocity(sf::Vector2f(0, 1 * m_Object->GetMaxVelocity()));
				return true;

			case sf::Keyboard::Space:
				if (!dynamic_cast<Tank *>(m_Object))
					return true;

				dynamic_cast<Tank *>(m_Object)->Fire();
				return true;
		}
	}
	else if (in_Event.type == sf::Event::KeyReleased)
	{
		m_Object->SetVelocity(sf::Vector2f(0, 0));
	}

	return false;
}

void Player::OnObjectDestroy(GameObject *in_Object)
{
	m_Object = NULL;
}

GameObject *Player::GetObject() const
{
	return m_Object;
}