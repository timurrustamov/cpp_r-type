#ifndef LEVEL_H_
# define LEVEL_H_

# include							<cstddef>
# include							<string>
# include							<SFML/Graphics/Texture.hpp>
# include							<SFML/Audio/Music.hpp>
# include							"t2Vector.hpp"
# include							"../System/RTypeException.h"

# define ASSET_FOLDER				"../Assets/"
# define BGM_LOCATION				"Sounds/BGM/"
# define BGT_LOCATION				"Graphics/Backgrounds/"

class								Level
{
	std::string						title;
	std::string						bgtPath;
	std::string						bgmPath;

	sf::Texture						bgt;
	sf::Music						bgm;

	int								scrollSpeed;
	unsigned int					size;
	t2Vector<int>					gravity;
	bool							loaded;
	
public:
	Level(std::string const &);
	~Level();

	void							load();
	void							loadIdentifiers() const;
	std::string const				&getTitle() const;
	std::string const				&getBgmPath() const;
	std::string const				&getBgtPath() const;

	sf::Texture						*getTexture();
	t2Vector<int>					getGravity() const;
	int								getScrollSpeed() const;
	unsigned int					getSize() const;
	bool							isLoaded() const;

	void							playMusic();
	void							unPlayMusic();
};

std::ostream						&operator<<(std::ostream &, const Level &);

#endif /* !LEVEL_H_ */