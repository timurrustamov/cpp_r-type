#ifndef ONEDITOR_H_
# define ONEDITOR_H_

# include									<map>
# include									<vector>
# include									<cstddef>
# include									"../GameEngine/IGameplay.h"
# include									"../GameEngine/GameData.h"
# include									"../System/Animation.h"
# include									"EditorEntity.h"
# include									"EditorMonster.h"

# define EDITOR_WIDTH						1400
# define EDITOR_HEIGHT						755

class										OnEditor : public IGameplay
{
	GameData								*gameData;
	std::map<std::string, Animation *>		animations;

	std::vector<EditorMonster>				monsterBank;
	std::vector<EditorEntity>				entityBank;

	std::vector<EditorEntity>				storyLine;

	AnimationEntity							layoutEntity;
	AnimationEntity							backgroundEntity;
	Timer									timer;

public:
	OnEditor();
	~OnEditor();

	void									keyPressed(sf::Keyboard::Key);
	bool									mustCloseGame();
	bool									mustSwitchFullscreen();
	void									draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void									updateGraphics();
	void									updateLogic(sf::Time *time);
};

#endif /* !ONEDITOR_H_ */