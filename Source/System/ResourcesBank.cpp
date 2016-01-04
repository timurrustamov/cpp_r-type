#include						"ResourcesBank.h"
#include						"../System/RTypeException.h"

ResourcesBank::ResourcesBank() : animationBank(NULL)
{}

ResourcesBank::~ResourcesBank()
{}

ResourcesBank					*ResourcesBank::getInstance(bool _delete)
{
	static						ResourcesBank *that = static_cast<ResourcesBank *>(0);
	bool						isNull = (that == static_cast<ResourcesBank *>(0));

	if (isNull && _delete == false)
		that = new ResourcesBank();
	else if (_delete == true && !isNull)
	{
		delete that;
		that = static_cast<ResourcesBank *>(0);
	}
	return (that);
}

sf::Texture							*ResourcesBank::getTexture(const std::string &name) const
{
	return (this->textureBank.at(name));
}

sf::SoundBuffer						*ResourcesBank::getSoundBuffer(const std::string &name)
{
	return (&this->soundBufferBank.at(name));
}

std::map<std::string, Animation *>	*ResourcesBank::getAnimations() const
{
	if (this->animationBank == NULL)
		throw RTypeException("access error: the animation bank has not been initialized (on function getAnimations())");
	return (this->animationBank);
}

Animation							*ResourcesBank::getAnimation(const std::string &name)
{
	if (this->animationBank == NULL)
		throw RTypeException("access error: the animation bank has not been initialized (on function getAnimations())");
	try
	{
		return (this->animationBank->at(name));
	}
	catch (const std::out_of_range &)
	{
		return (static_cast<Animation *>(0));
	}
}

void								ResourcesBank::setTexture(const std::string &name, const std::string &pathfile)
{
	if (this->textureBank.find(name) != this->textureBank.end())
		return;

	sf::Texture					*texture = new sf::Texture();

	if (texture->loadFromFile(pathfile))
		this->textureBank[name] = texture;
	else
		throw RTypeException("Adding texture: " + name + " (location: " + pathfile + ")" + " failed (loading)");
}

void								ResourcesBank::setSoundBuffer(const std::string &name, const std::string &pathfile)
{
	if (this->soundBufferBank.find(name) != this->soundBufferBank.end())
		return;
	if (!this->soundBufferBank[name].loadFromFile(pathfile))
		throw RTypeException("Adding sound: " + name + " (location: " + pathfile + ")" + " failed (loading)");
}

void								ResourcesBank::setAnimations(std::map<std::string, Animation *> *animations)
{
	this->animationBank = animations;
}

void								ResourcesBank::setAnimation(std::string const &name, Animation *newAnimation)
{
	try
	{
		if (this->animationBank->at(name))
			throw RTypeException("Trying to add texture: " + name + " but it already exists");
	}
	catch (const std::out_of_range &)
	{
		this->animationBank->operator[](name) = newAnimation;
	}
}