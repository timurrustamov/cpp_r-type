#include				<iostream>
#include				<vector>
#include				<dirent.h>
#include				"../System/RTypeException.h"
#include				"../System/Animation.h"
#include				"../System/RTypeException.h"
#include				"../GameEngine/Monster.h"
#include				"OnEditor.h"

static bool				hasEnding(std::string const &fullString, std::string const &ending)
{
	if (fullString.length() >= ending.length())
		return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
	return (false);
}

void					OnEditor::loadFromDirectory(std::string const &directory, std::vector<std::string> *storage)
{
	DIR					*dir;
	struct dirent		*ent;
	std::string			repertory(directory);
	std::string			wantedType(".png");

	if ((dir = opendir(directory.c_str())) == NULL)
		throw RTypeException("Could not open" + directory);

	while ((ent = readdir(dir)) != NULL)
	{
		std::string		image(ent->d_name);
		if (hasEnding(image, wantedType))
		{
			std::string		name(image.substr(0, image.size() - wantedType.size()));

			if (storage != NULL)
				storage->push_back(name);
			this->gameData->resourceBank->setTexture(name, repertory + image);
		}
	}
	closedir(dir);
}

OnEditor::OnEditor(sf::Window *_window) : window(_window), id(0), backgroundEntity(), warningEntity(0, 0, t2Vector<int>(50, 50)), layoutEntity(0, 0, t2Vector<int>(0, 0)), background(static_cast<unsigned int>(0))
{
	std::vector<std::string> backgrounds;

	this->gameData = GameData::getInstance();
	this->gameData->resourceBank->setAnimations(&this->animations);

	this->loadFromDirectory(ASSET_FOLDER S_LOCATION);
	this->loadFromDirectory(ASSET_FOLDER BGT_LOCATION, &backgrounds);

	for (std::vector<std::string>::iterator it = backgrounds.begin(); it != backgrounds.end(); ++it)
	{
		sf::Vector2u size = this->gameData->resourceBank->getTexture(*it)->getSize();
		this->gameData->resourceBank->setAnimation(*it, new Animation(*it, this->gameData->resourceBank->getTexture(*it), t2Vector<unsigned int>(size.x, size.y)));
		this->backgroundBank.push_back(EditorEntity(this->gameData->resourceBank->getAnimation(*it)));
		this->background.animation = this->gameData->resourceBank->getAnimation(*it);
	}
	this->background.entity.setPosition(t2Vector<unsigned int>(11, 0));
	this->background.animation->changeEntity(&this->background.entity);

	ResourcesBank::getInstance()->setTexture("Layout", ASSET_FOLDER + std::string("Graphics/Editor/Layout.png"));
	this->animations["Layout"] = new Animation("Layout", ResourcesBank::getInstance()->getTexture("Layout"), t2Vector<unsigned int>(EDITOR_WIDTH, EDITOR_HEIGHT));
	this->animations["Layout"]->changeEntity(&this->backgroundEntity);

	this->animations["Warning"] = new Animation("Warning", ResourcesBank::getInstance()->getTexture("Warning"), t2Vector<unsigned int>(50, 44));

	std::string end("END");
	const char *monsters[] = { "BasicShip", "Meteora", "Nautilus", "Robot", "END" };
	unsigned int i = 0;

	while (std::string("END").compare(monsters[i]) != 0)
		this->monsterBank.push_back(EditorMonster(monsters[i++]));

	this->storyLine.push_back(EditorMonster(this->monsterBank[0]));
	this->storyLine[0].setPosition(t2Vector<int>(300, 300));
	this->storyLine[0].animation->changeEntity(&this->storyLine[0].entity);

	this->timer.addNewEvent("mouseSpam", 0.1f);
	this->timer.addNewEvent("Warning", 1);
}

OnEditor::~OnEditor()
{
}

void					OnEditor::keyPressed(sf::Keyboard::Key key)
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

void					OnEditor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	this->background.animation->draw(target, states);
	this->animations.at("Layout")->draw(target, states);
	for (std::vector<EditorEntity>::const_iterator it = this->storyLine.begin(); it != this->storyLine.end(); ++it)
	{
		(*it).animation->draw(target, states);
	}
	this->animations.at("Warning")->draw(target, states);
}

void					OnEditor::updateLogic(sf::Time *time)
{
	try
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->timer.eventDone("mouseSpam"))
		{
			sf::Vector2i position = sf::Mouse::getPosition(*this->window);

			EditorMonster	sample(this->monsterBank[0]);

			this->storyLine.push_back(sample);
			EditorEntity	*entity = &this->storyLine[this->storyLine.size() - 1];
			entity->setPosition(position);
			entity->animation->changeEntity(&entity->entity);

			this->timer.reset("mouseSpam");
		}
	}
	catch (const RTypeException &err)
	{
		this->animations["Warning"]->changeEntity(&this->warningEntity);
		this->timer.reset("Warning");
	}
	if (this->timer.eventDone("Warning"))
		this->animations["Warning"]->removeEntity(this->warningEntity.getId());
}

void					OnEditor::updateGraphics()
{
	for (std::map<std::string, Animation *>::const_iterator animation = this->animations.begin(); animation != this->animations.end(); ++animation)
		animation->second->prepareVertices();
}