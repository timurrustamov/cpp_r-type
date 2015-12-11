#include						"ResourcesBank.h"
#include						"../System/RTypeException.h"

ResourcesBank::ResourcesBank()
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

void								ResourcesBank::setTexture(const std::string &name, const std::string &pathfile)
{
	try
	{
		if (this->textureBank.at(name))
			throw RTypeException("Trying to add texture: " + name + " (location: " + pathfile + ")" + " but it already exists");
	}
	catch (const std::out_of_range &)
	{
		sf::Texture					*texture = new sf::Texture();

		if (texture->loadFromFile(pathfile))
			this->textureBank[name] = texture;
		else
			throw RTypeException("Adding texture: " + name + " (location: " + pathfile + ")" + " failed (loading)");
	}
}

void								ResourcesBank::setSoundBuffer(const std::string &name, const std::string &pathfile)
{
	try
	{
		this->soundBufferBank.at(name);
		throw RTypeException("Trying to add sound: " + name + " (location: " + pathfile + ")" + " but it already exists");
	}
	catch (const std::out_of_range &)
	{
		if (!this->soundBufferBank[name].loadFromFile(pathfile))
			throw RTypeException("Adding sound: " + name + " (location: " + pathfile + ")" + " failed (loading)");
	}
}