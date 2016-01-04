#include				<iostream>
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

OnEditor::OnEditor() : backgroundEntity(0, 0, t2Vector<int>(0, 0)), layoutEntity(0, 0, t2Vector<int>(0, 0))
{
	DIR					*dir;
	struct dirent		*ent;
	std::string			repertory(ASSET_FOLDER S_LOCATION);
	std::string			wantedType(".png");

	this->gameData = GameData::getInstance();
	this->gameData->resourceBank->setAnimations(&this->animations);
	if ((dir = opendir("../Assets/Graphics/Sprites/")) == NULL)
		throw RTypeException("Could not open sprite directory");

	while ((ent = readdir(dir)) != NULL)
	{
		std::string		image(ent->d_name);
		if (hasEnding(image, wantedType))
			this->gameData->resourceBank->setTexture(image.substr(0, image.size() - wantedType.size()), repertory + ent->d_name);
	}
	closedir(dir);

	ResourcesBank::getInstance()->setTexture("Layout", ASSET_FOLDER + std::string("Graphics/Editor/Layout.png"));
	this->animations["Layout"] = new Animation("Layout", ResourcesBank::getInstance()->getTexture("Layout"), t2Vector<unsigned int>(EDITOR_WIDTH, EDITOR_HEIGHT));
	this->animations["Layout"]->changeEntity(&this->backgroundEntity);

	std::string end("END");
	const char *monsters[] = { "BasicShip", "Meteora", "Nautilus", "Robot", "END" };
	unsigned int i = 0;

	while (std::string("END").compare(monsters[i]) != 0)
		this->monsterBank.push_back(EditorMonster(monsters[i++]));
	/*
	i = 0;
	while (i <= MAX_IDENTIFIER)
		this->entityBank.push_back(EditorEntity(i++));
		*/
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
	for (std::map<std::string, Animation *>::const_iterator animation = this->animations.begin(); animation != this->animations.end(); ++animation)
		animation->second->draw(target, states);
}

void					OnEditor::updateLogic(sf::Time *time)
{
}

void					OnEditor::updateGraphics()
{
	for (std::map<std::string, Animation *>::const_iterator animation = this->animations.begin(); animation != this->animations.end(); ++animation)
		animation->second->prepareVertices();
}