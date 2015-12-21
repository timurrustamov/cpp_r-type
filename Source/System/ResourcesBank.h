#ifndef RESOURCESBANK_H_
# define RESOURCESBANK_H_

# include												<string>
# include												<map>
# include												<SFML/Graphics/Texture.hpp>
# include												<SFML/Audio/Sound.hpp>
# include												<SFML/Audio/SoundBuffer.hpp>

class													ResourcesBank
{
	std::map<std::string, sf::Texture *>				textureBank;
	std::map<std::string, sf::SoundBuffer>				soundBufferBank;

	ResourcesBank();
	~ResourcesBank();

public:
	static ResourcesBank								*getInstance(bool _del = false);

	sf::Texture											*getTexture(const std::string &) const;
	sf::SoundBuffer										*getSoundBuffer(const std::string &);

	void												setTexture(const std::string &, const std::string &);
	void												setSoundBuffer(const std::string &, const std::string &);
};

#endif /* !RESOURCESBANK_H_ */