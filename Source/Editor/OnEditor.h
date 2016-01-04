#ifndef ONEDITOR_H_
# define ONEDITOR_H_

# include									<map>
# include									<vector>
# include									<cstddef>
# include									<SFML/Graphics.hpp>
# include									<SFML/Graphics/Drawable.hpp>
# include									"../GameEngine/IGameplay.h"
# include									"../GameEngine/GameData.h"
# include									"../System/Animation.h"
# include									"EditorEntity.h"
# include									"EditorMonster.h"

# define EDITOR_WIDTH						1400
# define EDITOR_HEIGHT						755

class										OnEditor : public IGameplay
{
	unsigned int							id;

	GameData								*gameData;
	sf::Window								*window;
	std::map<std::string, Animation *>		animations;

	std::vector<EditorEntity>				backgroundBank;
	std::vector<EditorMonster>				monsterBank;
	std::vector<EditorEntity>				entityBank;

	std::vector<EditorEntity>				storyLine;

	EditorEntity							background;
	AnimationEntity							layoutEntity;
	AnimationEntity							backgroundEntity;
	AnimationEntity							warningEntity;
	Timer									timer;

public:
	OnEditor(sf::Window *);
	~OnEditor();

	void									loadFromDirectory(std::string const &directory, std::vector<std::string> *storage = NULL);
	void									keyPressed(sf::Keyboard::Key);
	bool									mustCloseGame();
	bool									mustSwitchFullscreen();
	void									draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void									updateGraphics();
	void									updateLogic(sf::Time *time);
};

#endif /* !ONEDITOR_H_ */