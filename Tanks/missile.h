#pragma once
#include "game-object.h"

class Missile : public GameObject
{
public:
	Missile(const boost::property_tree::ptree &in_Json);
	Missile(const Missile *in_Tank);
	~Missile();

public:
	GameObject *Clone() const;

	void OnIntersect(GameObject *in_GameObject);
};

