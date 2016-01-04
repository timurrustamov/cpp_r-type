#ifndef LEVEL_H_
# define LEVEL_H_

# include							<cstddef>
# include							<string>
# include							<SFML/Graphics/Texture.hpp>
# include							<SFML/Audio/Music.hpp>
# include							"t2Vector.hpp"
# include							"../System/RTypeException.h"
# include							"GameData.h"

class								Level
{
	std::string						title;
	std::string						bgtPath;
	std::string						bgmPath;
	std::string 					scenario;

	sf::Texture						bgt;
	sf::Music						bgm;

	int								scrollSpeed;
	unsigned int					size;
	bool							loaded;
	
public:
	Level(std::string const &);
	Level(const std::string &title, const std::string &bgtPath, const std::string &bgmPath, const std::string &, unsigned int size, int scrollSpeed);
	~Level();

	void							load();
	void							loadIdentifiers() const;
	std::string const				&getTitle() const;
	std::string const				&getBgmPath() const;
	std::string const				&getBgtPath() const;

	sf::Texture						*getTexture();
	const std::string &				getScenario() const;
	int								getScrollSpeed() const;
	unsigned int					getSize() const;
	bool							isLoaded() const;

	void							playMusic();
	void							unPlayMusic();
};

std::ostream						&operator<<(std::ostream &, const Level &);

#endif /* !LEVEL_H_ */