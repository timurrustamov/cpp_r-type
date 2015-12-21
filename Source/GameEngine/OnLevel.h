#ifndef ONLEVEL_H_
# define ONLEVEL_H_

# include			"IGameplay.h"
# include			"GameData.h"
# include			"../System/Animation.h"

class				OnLevel : public IGameplay
{
	GameData		*gameData;
	Animation		*background;
	Animation		*test;

public:
	OnLevel();
	~OnLevel();

	void			keyPressed(sf::Keyboard::Key);
	bool			mustCloseGame();
	bool			mustSwitchFullscreen();
	void			draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void			updateGraphics();
};

#endif /* !GAMEPLAY_H_ */