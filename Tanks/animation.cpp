#include "Animation.h"
#include "texture-manager.h"

#include "animation-manager.h"

#define ANIMATION_INFITY 0

Animation_Type getAnimationTypeByName(const std::string &in_AnimationName)
{
	std::string animationNameLower(in_AnimationName);
	std::transform(in_AnimationName.begin(), in_AnimationName.end(), animationNameLower.begin(), ::tolower);

	if (animationNameLower == "idle")
		return Animation_Type::Idle;
	if (animationNameLower == "left")
		return Animation_Type::Left;
	if (animationNameLower == "right")
		return Animation_Type::Right;
	if (animationNameLower == "top")
		return Animation_Type::Top;
	if (animationNameLower == "bottom")
		return Animation_Type::Bottom;
	if (animationNameLower == "explosion")
		return Animation_Type::Explosion;

	return Animation_Type::Idle;
}


Animation::Animation(const boost::property_tree::ptree &in_Json)
{
	auto tilesOptional = in_Json.get_child_optional("tiles");
	if (!tilesOptional)
		return;

	boost::property_tree::ptree tiles = *tilesOptional;
	// подготовим картинки
	std::map<std::string, std::shared_ptr<sf::Sprite>> images;
	for (auto it = tiles.begin(); it != tiles.end(); ++it)
	{
		const std::string &imagePath = it->second.get<std::string>("image");
		sf::Texture *texture = TextureManager::GetInstance()->GetTexture(imagePath.c_str());

		images.emplace(it->first, new sf::Sprite(*texture));
	}

	boost::property_tree::ptree tileProperties = in_Json.get_child("tileproperties");
	for (auto it = tiles.begin(); it != tiles.end(); ++it)
	{
		auto properties = tileProperties.get_child_optional(it->first);
		if (!properties)
			continue;

		const std::string &animationName = properties->get<std::string>("animation");
		Animation_Type animationType = getAnimationTypeByName(animationName);

		auto animationJson = it->second.get_child_optional("animation");
		if (!animationJson)
		{
			std::string tileid = it->first;
			size_t duration = 0;

			m_Animations[animationType].emplace_back(images[tileid], duration);
			continue;
		}

		for (auto itAnimation = animationJson->begin(); itAnimation != animationJson->end(); ++itAnimation)
		{
			std::string tileid = itAnimation->second.get<std::string>("tileid");
			size_t duration = itAnimation->second.get<size_t>("duration");

			m_Animations[animationType].emplace_back(images[tileid], duration);
		}
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
	if (IsAnimationEnd())
		return;

	const std::vector<AnimationFrame> &animationFrames = m_Animations[m_PlayingAnimation.animationType];
	const AnimationFrame &animationFrame = animationFrames[m_PlayingAnimation.frameNum];
	in_RenderWindow->draw(*animationFrame.sprite);
}

sf::Sprite *Animation::Update(const sf::Time &in_Time)
{
	const AnimationFrame *animationFrame = getAnimationFrame();
	if (!animationFrame)
		return NULL;

	if (animationFrame->timeout == ANIMATION_INFITY)
		return &(*animationFrame->sprite);

	m_PlayingAnimation.passedTime += in_Time.asMilliseconds();
	if (m_PlayingAnimation.passedTime < animationFrame->timeout)
		return &(*animationFrame->sprite);

	m_PlayingAnimation.passedTime = 0;
	m_PlayingAnimation.frameNum += 1;

	return &(*animationFrame->sprite);
}

bool Animation::IsAnimationEnd()
{
	const AnimationFrame *animationFrame = getAnimationFrame();
	if (!animationFrame)
		return true;

	return false;
}

bool Animation::HasAnimationType(const Animation_Type in_AnimationType) const
{
	for (auto it = m_Animations.begin(); it != m_Animations.end(); ++it)
		if (it->first == in_AnimationType)
			return true;

	return false;
}

const AnimationFrame *Animation::getAnimationFrame() const
{
	auto animationFrames = m_Animations.find(m_PlayingAnimation.animationType);
	if (animationFrames == m_Animations.end())
	{
		auto animation = AnimationManager::GetInstance()->GetTemplateAnimation(m_PlayingAnimation.animationType);
		if (animation)
		{
			animationFrames = animation->m_Animations.find(m_PlayingAnimation.animationType);

			if (animationFrames == animation->m_Animations.end())
			{
				animationFrames = m_Animations.find(Animation_Type::Idle);
				if (animationFrames == m_Animations.end())
					return NULL;
			}
		}
		else
		{
			animationFrames = m_Animations.find(Animation_Type::Idle);
			if (animationFrames == m_Animations.end())
				return NULL;
		}
	}

	if (!animationFrames->second.size())
		return NULL;

	if (m_PlayingAnimation.frameNum >= animationFrames->second.size())
		return NULL;

	return &animationFrames->second[m_PlayingAnimation.frameNum];
}
