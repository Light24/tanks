#pragma once
#include "game-object.h"

class Missile : public GameObject
{
public:
	Missile(const boost::property_tree::ptree &in_Json);
	Missile(const Missile *in_Tank);
	~Missile();

	GameObject *Clone() const;

public:
	virtual Object_Type GetType() const override;

	void OnIntersect(GameObject *in_GameObject);
};

