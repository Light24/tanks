#include "tank.h"
#include "config.h"

Tank::Tank(const boost::property_tree::ptree &in_Json) : GameObject(in_Json)
{
}


Tank::Tank(const Tank *in_Tank) : GameObject(in_Tank)
{
}

Tank::~Tank()
{
}

GameObject *Tank::Clone() const
{
	return new Tank(this);
}

void Tank::OnIntersect(GameObject *in_GameObject)
{

}