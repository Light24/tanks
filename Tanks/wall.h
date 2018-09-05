#pragma once
#include "game-object.h"

class Wall : public GameObject
{
public:
	Wall(const boost::property_tree::ptree &in_Json);
	Wall(const Wall *in_Wall);
	~Wall();

	virtual GameObject *Clone() const override;

public:
	virtual Object_Type GetType() const override;

	virtual void OnIntersect(GameObject *in_GameObject) override;

private:
};
