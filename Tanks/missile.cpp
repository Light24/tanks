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


Object_Type Missile::GetType() const
{
	return Object_Type::Object_Type_Missile;
}

void Missile::OnIntersect(GameObject *in_GameObject)
{
	SetHealth(GetHealth() - 1);
	if (GetGroup() == in_GameObject->GetGroup())
		return;

	in_GameObject->SetHealth(in_GameObject->GetHealth() - 1);
}
