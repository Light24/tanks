#include "Wall.h"


Wall::Wall(const boost::property_tree::ptree &in_Json) : GameObject(in_Json)
{

}

Wall::Wall(const Wall *in_Wall) : GameObject(in_Wall)
{

}

Wall::~Wall()
{

}

GameObject *Wall::Clone() const
{
	return new Wall(this);
}

void Wall::OnIntersect(GameObject *in_GameObject)
{

}
