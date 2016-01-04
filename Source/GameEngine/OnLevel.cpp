#include				<iostream>
#include				<dirent.h>
#include				"../System/RTypeException.h"
#include				"../System/Animation.h"
#include				"Monster.h"
#include				"OnLevel.h"

OnLevel::OnLevel(OnLevel::MemFn ptr) : level(static_cast<Level *>(0)), backgroundEntity(0, 0, t2Vector<int>(0, 0))
{
	this->updatePtr = ptr;
	this->gameData = GameData::getInstance();
	this->gameData->resourceBank->setAnimations(&this->animations);
}

OnLevel::~OnLevel()
{}

static bool				hasEnding(std::string const &fullString, std::string const &ending)
{
	if (fullString.length() >= ending.length())
		return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
	return (false);
}

void					OnLevel::loadLevel(Level *newLevel)
{
	DIR					*dir;
	struct dirent		*ent;
	std::string			repertory(ASSET_FOLDER S_LOCATION);
	std::string			wantedType(".png");

	this->level = newLevel;
	this->level->load();
	if (!this->level->isLoaded())
		throw RTypeException("Could not load level" + this->level->getTitle());

	this->level->playMusic();
	this->animations["Background"] = new Animation("Background", this->level->getTexture(), t2Vector<unsigned int>(this->level->getSize(), this->gameData->getHeight()));
	this->animations["Background"]->changeEntity(&this->backgroundEntity);
	this->timer.addNewEvent("scrolling", static_cast<float>(this->level->getScrollSpeed()) / 100);
	this->world = new World(t2Vector<int>(this->gameData->getWidth(), this->gameData->getHeight()), true, true);
	this->gameData->world = this->world;

	if ((dir = opendir("../Assets/Graphics/Sprites/")) == NULL)
		throw RTypeException("Could not open sprite directory");

	while ((ent = readdir(dir)) != NULL)
	{
		std::string		image(ent->d_name);
		if (hasEnding(image, wantedType))
			this->gameData->resourceBank->setTexture(image.substr(0, image.size() - wantedType.size()), repertory + ent->d_name);
	}
	closedir(dir);

	//	this->timer.addNewEvent("mobSpawn", 1.3f);
	//	this->timer.addNewEvent("meteoraSpawn", 3);
	this->world->addSample(new Monster("BasicShip")); // A MODIFIER
	this->world->addSample(new Monster("Meteora")); // A MODIFIER
	this->world->addSample(new Monster("Nautilus")); // A MODIFIER
	this->world->addSample(new Monster("Robot"));
	this->level->loadIdentifiers();

	this->player = dynamic_cast<Player *>(this->world->getPlayerObject(0));

	this->snap = NULL;
	this->timer.addNewEvent("snap", 2);
}

void					OnLevel::keyPressed(sf::Keyboard::Key key)
{
	switch (key)
	{
	case sf::Keyboard::Escape:
		this->gameData->setMustQuit(true);
		break;
	case sf::Keyboard::F:
		this->gameData->setFullscreen(!this->gameData->getFullscreen());
		break;
	default:
		break;
	}
}

void					OnLevel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (std::map<std::string, Animation *>::const_iterator animation = this->animations.begin(); animation != this->animations.end(); ++animation)
		animation->second->draw(target, states);
}

void					OnLevel::updateLogic(sf::Time *time)
{
	if (this->updatePtr != NULL)
		this->updatePtr(*this);

	if (this->timer.eventDone("mobSpawn"))
	{
		Monster *monster = new Monster("Nautilus", t2Vector<unsigned int>(this->gameData->getWidth() - 100, rand() % this->gameData->getHeight()));
		GameData::getInstance()->world->createNewObject(monster);
		this->timer.reset("mobSpawn");
	}

	if (this->timer.eventDone("meteoraSpawn"))
	{
		Monster *monster = new Monster("Meteora", t2Vector<unsigned int>(this->gameData->getWidth() - 25, rand() % this->gameData->getHeight()));
		GameData::getInstance()->world->createNewObject(monster);
		this->timer.reset("meteoraSpawn");
	}

	if (this->timer.eventDone("robotSpawn"))
	{
		Monster *monster = new Monster("Robot", t2Vector<unsigned int>(this->gameData->getWidth() - 50, rand() % this->gameData->getHeight()));
		GameData::getInstance()->world->createNewObject(monster);
		this->timer.reset("robotSpawn");
	}

	if (this->world->timer.eventDone("player0"))
	{
		GameData::getInstance()->world->createNewPlayer(t2Vector<unsigned int>(50, 50), 0);
		this->world->timer.removeEvent("player0");
	}
	if (this->world->timer.eventDone("player1"))
	{
		GameData::getInstance()->world->createNewPlayer(t2Vector<unsigned int>(50, 90), 1);
		this->world->timer.removeEvent("player1");
	}
	if (this->world->timer.eventDone("player2"))
	{
		GameData::getInstance()->world->createNewPlayer(t2Vector<unsigned int>(50, 130), 2);
		this->world->timer.removeEvent("player2");
	}
	if (this->world->timer.eventDone("player3"))
	{
		GameData::getInstance()->world->createNewPlayer(t2Vector<unsigned int>(50, 180), 3);
		this->world->timer.removeEvent("player3");
	}

	this->world->tick(time->asSeconds());
}

void					OnLevel::updateGraphics()
{
	if (this->timer.eventDone("scrolling"))
	{
		this->backgroundEntity.setPosition(this->backgroundEntity.getPosition() + t2Vector<int>(-1, 0));
		this->animations["Background"]->changeEntity(&this->backgroundEntity);
		this->timer.addNewEvent("scolling", static_cast<float>(this->level->getScrollSpeed()) / 100);
		this->timer.reset("scrolling");
	}

	for (std::map<std::string, Animation *>::const_iterator animation = this->animations.begin(); animation != this->animations.end(); ++animation)
		animation->second->prepareVertices();
}

void OnLevel::createPlayer(unsigned int playerNo) {

	this->world->createNewPlayer(t2Vector<unsigned int>(this->gameData->getWidth() / 10, this->gameData->getHeight() / 2), playerNo);
}
