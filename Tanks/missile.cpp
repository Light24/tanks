#include "missile.h"


Missile::Missile(const boost::property_tree::ptree &in_Json) : GameObject(in_Json)
{
}


Missile::Missile(const Missile *in_Tank) : GameObject(in_Tank)
{
}

Missile::~Missile()
{
}

GameObject *Missile::Clone() const
{
	return new Missile(this);
}

void Missile::OnIntersect(GameObject *in_GameObject)
{
	SetHealth(GetHealth() - 1);
	in_GameObject->SetHealth(in_GameObject->GetHealth() - 1);
}
