#ifndef GAMEDATA_H_
# define GAMEDATA_H_

# include				<cstddef>
# include				"../System/RTypeException.h"
# include				"../System/ResourcesBank.h"
# include				"t2Vector.hpp"
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

	void				setWorld(t2Vector<int> size, bool verticalWalls = true, bool horizontalWalls = false);
	unsigned int		getWidth() const;
	unsigned int		getHeight() const;
};

#endif /* !GAMEDATA_H_ */