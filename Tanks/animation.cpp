#include "Animation.h"
#include "texture-manager.h"

Animation_Type getAnimationTypeByName(const std::string &in_AnimationName)
{
	std::string animationNameLower(in_AnimationName);
	std::transform(in_AnimationName.begin(), in_AnimationName.end(), animationNameLower.begin(), ::tolower);

	if (animationNameLower == "left")
		return Animation_Type::Left;
	if (animationNameLower == "right")
		return Animation_Type::Right;
	if (animationNameLower == "top")
		return Animation_Type::Top;
	if (animationNameLower == "bottom")
		return Animation_Type::Bottom;

	return Animation_Type::Idle;
}


Animation::Animation(const boost::property_tree::ptree &in_Json)
{
	auto tilesOptional = in_Json.get_child_optional("tiles");
	if (!tilesOptional)
		return;

	boost::property_tree::ptree tiles = *tilesOptional;
	boost::property_tree::ptree tileProperties = in_Json.get_child("tileproperties");
	for (auto it = tiles.begin(); it != tiles.end(); ++it)
	{
		if (!tileProperties.get_child_optional(it->first))
		{
			throw "ERROR! skip image";
			continue;
		}

		const std::string &imagePath = it->second.get<std::string>("image");
		const std::string &animationName = tileProperties.get_child(it->first).get<std::string>("animation");

		sf::Texture *texture = TextureManager::GetInstance()->GetTexture(imagePath.c_str());

		Animation_Type animationType = getAnimationTypeByName(animationName);
		m_Animations[animationType].emplace_back(new sf::Sprite(*texture), 0);
	}

	SetAnimationType(Animation_Type::Idle);
}

Animation::Animation(const Animation &in_Animation)
{
	m_Animations = in_Animation.m_Animations;
	m_PlayingAnimation = in_Animation.m_PlayingAnimation;
}

Animation::~Animation()
{
}

Animation *Animation::Clone()
{
	return new Animation(*this);
}


void Animation::SetAnimationType(Animation_Type in_AnimationType)
{
	m_PlayingAnimation.animationType = in_AnimationType;
	m_PlayingAnimation.passedTime = 0;
	m_PlayingAnimation.frameNum = 0;
}

void Animation::Draw(sf::RenderWindow *in_RenderWindow)
{
	const std::vector<AnimationFrame> &animationFrames = m_Animations[m_PlayingAnimation.animationType];
	const AnimationFrame &animationFrame = animationFrames[m_PlayingAnimation.frameNum];
	in_RenderWindow->draw(*animationFrame.sprite);
}

sf::Sprite *Animation::Update(const sf::Time &in_Time)
{
	if (m_Animations.find(m_PlayingAnimation.animationType) == m_Animations.end())
		return NULL;

	const std::vector<AnimationFrame> &animationFrames = m_Animations[m_PlayingAnimation.animationType];
	if (!animationFrames.size())
		return NULL;

	const AnimationFrame &animationFrame = animationFrames[m_PlayingAnimation.frameNum];
	if (!animationFrame.timeout)
		return animationFrame.sprite;

	m_PlayingAnimation.passedTime += in_Time.asMilliseconds();
	if (animationFrame.timeout < m_PlayingAnimation.passedTime)
		return animationFrame.sprite;

	m_PlayingAnimation.passedTime = 0;
	m_PlayingAnimation.frameNum += 1;
	if (m_PlayingAnimation.frameNum >= animationFrames.size())
		m_PlayingAnimation.frameNum = 0;

	return animationFrame.sprite;
}
