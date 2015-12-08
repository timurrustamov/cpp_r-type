#include				"GameData.h"

GameData::GameData() : fullscreen(false), mustQuit(false)
{}
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