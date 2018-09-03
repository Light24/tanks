#pragma once
#include "SFML/Graphics.hpp"
#include "boost/property_tree/json_parser.hpp"

enum Animation_Type
{
	Idle,
	Top,
	Bottom,
	Left,
	Right,
};

class Animation
{
public:
	Animation(const boost::property_tree::ptree &in_Json);
	Animation(const Animation &in_Animation);
	~Animation();

	Animation *Clone();

public:
	void SetAnimationType(Animation_Type in_AnimationType);
	void Draw(sf::RenderWindow *in_RenderWindow);
	sf::Sprite *Update(const sf::Time &in_Time);

private:
	struct PlayingAnimation
	{
		Animation_Type animationType;
		size_t frameNum;
		float passedTime;
	};
	PlayingAnimation m_PlayingAnimation;

	struct AnimationFrame
	{
		AnimationFrame(sf::Sprite *in_Sprite, float in_Timeout) : sprite(in_Sprite), timeout(in_Timeout) {}
		~AnimationFrame() { delete sprite; sprite = NULL; }

		sf::Sprite *sprite;
		float timeout;
	};

	// TODO: сделать через shared ptr
	std::map<Animation_Type, std::vector<AnimationFrame>> m_Animations;
};
