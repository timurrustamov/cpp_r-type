#ifndef GAMEPLAY_H_
# define GAMEPLAY_H_

# include			<SFML/Window/Event.hpp>

class				Gameplay
{
	bool			closeGame;
	bool			switchFullScreen;

public:
	Gameplay();
	~Gameplay();

	void			keyPressed(sf::Keyboard::Key);
	bool			mustCloseGame() const;
	bool			mustSwitchFullscreen();
};

#endif /* !GAMEPLAY_H_ */