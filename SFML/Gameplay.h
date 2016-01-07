#ifndef GAMEPLAY_H_
# define GAMEPLAY_H_

#if defined(_WIN32) && !defined(WIN32)
# define _WINSOCKAPI_
# define NOGDI
# include <windows.h>
# define WIN32
#endif

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