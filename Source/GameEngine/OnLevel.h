#ifndef ONLEVEL_H_
# define ONLEVEL_H_

# include			"IGameplay.h"
# include			"GameData.h"

class				OnLevel : public IGameplay
{
	GameData		*gameData;

public:
	OnLevel();
	~OnLevel();

	void			keyPressed(sf::Keyboard::Key);
	bool			mustCloseGame();
	bool			mustSwitchFullscreen();
};

#endif /* !GAMEPLAY_H_ */