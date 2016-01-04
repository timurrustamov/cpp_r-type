#include				"GameData.h"

GameData::GameData() : fullscreen(false), mustQuit(false)
{
	this->resourceBank = ResourcesBank::getInstance();
	this->width = 1138;
	this->height = 640;
}

GameData::~GameData() {}

GameData				*GameData::getInstance(bool _delete)
{
	static				GameData *that = static_cast<GameData *>(0);
	bool				isNull = (that == static_cast<GameData *>(0));

	if (isNull && _delete == false)
		that = new GameData();
	else if (_delete == true && !isNull)
	{
		delete that;
		that = static_cast<GameData *>(0);
	}
	return (that);
}

void				GameData::setFullscreen(bool newValue)
{
	this->fullscreen = newValue;
}

void				GameData::setMustQuit(bool newValue)
{
	this->mustQuit = newValue;
}

bool				GameData::getFullscreen() const { return (this->fullscreen); }
bool				GameData::getMustQuit() const { return (this->mustQuit); }

void				GameData::setWorld(t2Vector<int> size, bool verticalWalls, bool horizontalWalls)
{
	if (this->world != static_cast<World *>(0))
		delete this->world;
	this->world = new World(size, verticalWalls, horizontalWalls);
}

unsigned int		GameData::getWidth() const
{
	return (this->width);
}

unsigned int		GameData::getHeight() const
{
	return (this->height);
}

std::map<std::string, std::string>
GameData::parseConfig(std::string &str) {

	std::map<std::string, std::string>	_map;
	std::string							tmp;
	std::size_t 						i;
	std::size_t 						a;

	while ((i = str.find(";")) != std::string::npos)
	{
		tmp = str.substr(0, i);
		str.erase(0, i);
		if ((a = tmp.find(":")) == std::string::npos)
			return _map;
		_map[tmp.substr(0, a)] = tmp.substr(a + 1);
	}
	return _map;
}
