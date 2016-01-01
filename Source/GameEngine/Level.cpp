#include							<boost/property_tree/ptree.hpp>
#include							<boost/property_tree/xml_parser.hpp>
#include							"GameData.h"
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
	GameData						*gameData = GameData::getInstance();

	if (this->bgmPath.size() <= 0 || this->bgtPath.size() <= 0)
		throw RTypeException("Background music or background texture missing, cannot load level");
	if (!this->bgm.openFromFile(ASSET_FOLDER BGM_LOCATION + this->bgmPath) || !this->bgt.loadFromFile(ASSET_FOLDER BGT_LOCATION + this->bgtPath))
		throw RTypeException("Wrong background music path or background texture path, cannot load level");
	this->size = (this->size) ? this->size : this->bgt.getSize().x;
	this->bgm.setLoop(true);

	try
	{
		gameData->resourceBank->setTexture("Player", "../Assets/Graphics/Sprites/r-typesheet1.png");
		gameData->resourceBank->setTexture("Bullets", "../Assets/Graphics/Sprites/Bullets.png");

		gameData->resourceBank->setTexture("Explode4", "../Assets/Graphics/Sprites/Explode4.png");
		gameData->resourceBank->setTexture("Explode3", "../Assets/Graphics/Sprites/Explode3.png");
		gameData->resourceBank->setTexture("Explode2", "../Assets/Graphics/Sprites/Explode2.png");
		gameData->resourceBank->setTexture("Explode1", "../Assets/Graphics/Sprites/Explode1.png");

		gameData->resourceBank->setSoundBuffer("Explosion3", "../Assets/Sounds/SE/Bomb.ogg");
		gameData->resourceBank->setSoundBuffer("Explosion2", "../Assets/Sounds/SE/Explosion2.ogg");
		gameData->resourceBank->setSoundBuffer("Explosion1", "../Assets/Sounds/SE/Explosion1.ogg");

		gameData->resourceBank->setSoundBuffer("Shoot1", "../Assets/Sounds/SE/Shoot1.ogg");
		gameData->resourceBank->setSoundBuffer("Shoot2", "../Assets/Sounds/SE/Shoot2.ogg");
		gameData->resourceBank->setSoundBuffer("Shoot3", "../Assets/Sounds/SE/Shoot3.ogg");

		gameData->resourceBank->setSoundBuffer("ChargeShot", "../Assets/Sounds/SE/ChargeShot.ogg");
		gameData->resourceBank->setSoundBuffer("ChargeShot2", "../Assets/Sounds/SE/ChargeShot2.ogg");

		gameData->resourceBank->setSoundBuffer("Bomb", "../Assets/Sounds/SE/Bomb.ogg");
		gameData->resourceBank->setSoundBuffer("BombEnergy", "../Assets/Sounds/SE/BombEnergy.ogg");
		gameData->resourceBank->setSoundBuffer("BombLaser", "../Assets/Sounds/SE/BombLaser.ogg");
		gameData->resourceBank->setSoundBuffer("BombPhysic", "../Assets/Sounds/SE/BombPhysic.ogg");
	}
	catch (const std::exception &err)
	{
		throw RTypeException(std::string("Error on loading the resources needed for the player: ") + err.what());
	}

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