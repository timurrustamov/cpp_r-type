#ifndef GAMEDATA_H_
# define GAMEDATA_H_

# include				"../System/ResourcesBank.h"
# include				"World.hpp"

class					GameData
{
	bool				fullscreen;
	bool				mustQuit;
	unsigned int		width;
	unsigned int		height;

	GameData();
	~GameData();

public:
	static GameData		*getInstance(bool _delete = false);
	ResourcesBank		*resourceBank;
	World				*world;

	void				setFullscreen(bool);
	void				setMustQuit(bool);

	bool				getFullscreen() const;
	bool				getMustQuit() const;

	void				GameData::setWorld(t2Vector<int> size, bool verticalWalls = true, bool horizontalWalls = false);
	unsigned int		getWidth() const;
	unsigned int		getHeight() const;
};

#endif /* !GAMEDATA_H_ */