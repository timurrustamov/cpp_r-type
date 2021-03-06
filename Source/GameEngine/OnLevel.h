#ifndef ONLEVEL_H_
# define ONLEVEL_H_

# include									<cstddef>
# include									<map>
# include									"IGameplay.h"
# include									"GameData.h"
# include									"Level.h"
# include									"../System/Animation.h"
# include									"Snapshot.hpp"
# include									"Timer.hpp"
//# include   								"ISocket.h"

//void sendUdp(World *);
//void updGameHandler(ISocket *);

class										OnLevel : public IGameplay
{
public:
	typedef  void (*MemFn)(OnLevel &);

private:
	Level									*level;
	GameData								*gameData;
	std::map<std::string, Animation *>		animations;

	World									*world;
	AnimationEntity							backgroundEntity;
	Player									*player;
	Snapshot								*snap;

public:
	OnLevel(MemFn ptr = NULL);
	~OnLevel();

	Timer									timer;
	MemFn 									updatePtr;

	void 									createPlayer(unsigned int playerNo);

	void									loadLevel(Level *newLevel);
	void									keyPressed(sf::Keyboard::Key);
	bool									mustCloseGame();
	bool									mustSwitchFullscreen();
	void									draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void									updateGraphics();
	void									updateLogic(sf::Time *time);
};

#endif /* !ONLEVEL_H_ */
