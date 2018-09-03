#pragma once
#include "game-object.h"

class Tank : public GameObject
{
public:
	Tank(const boost::property_tree::ptree &in_Json);
	Tank(const Tank *in_Tank);
	~Tank();

	virtual GameObject *Clone() const override;

public:
	virtual void OnIntersect(GameObject *in_GameObject) override;

private:
};