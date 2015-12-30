#include							<boost/property_tree/ptree.hpp>
#include							<boost/property_tree/xml_parser.hpp>
#include							"Level.h"

Level::Level(std::string const &filepath) : loaded(false)
{
	boost::property_tree::ptree		ptree;

	try
	{
		boost::property_tree::read_xml(filepath, ptree);

		this->title = ptree.get<std::string>("level.title");

		this->bgmPath = ptree.get<std::string>("level.BGM");
		this->bgtPath = ptree.get<std::string>("level.BGT");

		this->scrollSpeed = ptree.get("level.parameters.scrollspeed", 100);
		this->size = ptree.get("level.parameters.size", 0);
		this->gravity.assign(ptree.get("level.parameters.gravity.x", 0), ptree.get("level.parameters.gravity.y", 0));
	}
	catch (const std::exception &err)
	{
		throw RTypeException("Cannot load level: " + std::string(err.what()));
	}
}

Level::~Level()
{
	this->bgm.stop();
}

void								Level::load()
{
	if (this->bgmPath.size() <= 0 || this->bgtPath.size() <= 0)
		throw RTypeException("Background music or background texture missing, cannot load level");
	if (!this->bgm.openFromFile(ASSET_FOLDER BGM_LOCATION + this->bgmPath) || !this->bgt.loadFromFile(ASSET_FOLDER BGT_LOCATION + this->bgtPath))
		throw RTypeException("Wrong background music path or background texture path, cannot load level");
	this->size = (this->size) ? this->size : this->bgt.getSize().x;
	this->bgm.setLoop(true);
	this->loaded = true;
}

void								Level::playMusic()
{
	this->bgm.play();
}

void								Level::unPlayMusic()
{
	this->bgm.stop();
}

sf::Texture							*Level::getTexture()
{
	return (&this->bgt);
}

std::string const					&Level::getTitle() const
{
	return (this->title);
}

std::string const					&Level::getBgmPath() const
{
	return (this->bgmPath);
}

std::string const					&Level::getBgtPath() const
{
	return (this->bgtPath);
}

t2Vector<int>						Level::getGravity() const
{
	return (this->gravity);
}

int									Level::getScrollSpeed() const
{
	return (this->scrollSpeed);
}
unsigned int						Level::getSize() const
{
	return (this->size);
}

bool								Level::isLoaded() const
{
	return (this->loaded);
}

std::ostream						&operator<<(std::ostream& os, const Level& that)
{
	os << "Level" << std::endl;
	os << "Title: " << that.getTitle() << std::endl;
	os << "Background Music: " << that.getBgmPath() << std::endl;
	os << "Background Texture: " << that.getBgtPath() << std::endl;

	os << std::endl << "Properties: " << std::endl;
	os << "Size: " << that.getSize() << " | ScrollSpeed: " << that.getScrollSpeed() << std::endl;
	os << "Default Gravity: " << that.getGravity() << std::endl;
	return (os);
}