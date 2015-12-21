#ifndef ONLEVEL_H_
# define ONLEVEL_H_

# include									<map>
# include									"IGameplay.h"
# include									"GameData.h"
# include									"Level.h"
# include									"../System/Animation.h"
# include									"Timer.hpp"

class										OnLevel : public IGameplay
{
	Level									*level;
	GameData								*gameData;
	std::map<std::string, Animation *>		animations;

	World									*world;
	AnimationEntity							backgroundEntity;
	Timer									timer;
	Player									*player;

public:
	OnLevel();
	~OnLevel();

	void									loadLevel(Level *newLevel);
	void									keyPressed(sf::Keyboard::Key);
	bool									mustCloseGame();
	bool									mustSwitchFullscreen();
	void									draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void									updateGraphics();
	void									updateLogic(sf::Time *time);
};

#endif /* !GAMEPLAY_H_ */