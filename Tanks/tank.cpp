#include "tank.h"
#include "config.h"
#include "container.h"

Tank::Tank(const boost::property_tree::ptree &in_Json) : GameObject(in_Json), m_FireRate(0.6)
{
	m_FireCharge = m_FireRate;
	SetGroup(GROUP_COMPUTER);
}


Tank::Tank(const Tank *in_Tank) : GameObject(in_Tank)
{
	m_FireRate = in_Tank->m_FireRate;
	m_FireCharge = in_Tank->m_FireCharge;
}

Tank::~Tank()
{
}

GameObject *Tank::Clone() const
{
	return new Tank(this);
}


void Tank::Fire()
{
	m_FireCharge += m_Clock.getElapsedTime().asSeconds();
	m_Clock.restart();
	if (m_FireCharge < m_FireRate)
		return;

	GameObject *missile = ConfigManager::GetInstance()->Create_Object(Object_Subtype_Missile);
	missile->SetPos(sf::Vector2f((GetPos().x + GetSize().x / 2) - (GetSize().x / 2 * GetDirection().x) - missile->GetSize().x / 2, (GetPos().y + GetSize().y / 2) - (GetSize().y / 2 * GetDirection().y) - missile->GetSize().y / 2));
	missile->SetVelocity(sf::Vector2f(missile->GetMaxVelocity() * GetDirection().x, missile->GetMaxVelocity() * GetDirection().y));
	missile->SetGroup(GetGroup());
	dynamic_cast<Container *>(GetParent())->AddWidget(missile);

	m_FireCharge = 0;
}

Object_Type Tank::GetType() const
{
	return Object_Type::Object_Type_Tank;
}

void Tank::OnIntersect(GameObject *in_GameObject)
{
}