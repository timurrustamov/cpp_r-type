#ifndef WINDOW_H_
# define WINDOW_H_

# include					<string>
# include					<SFML/Graphics.hpp>
# include					"RTypeException.h"
# include					"../GameEngine/Gameplay.h"

class						Window
{
	Gameplay				*gameplay;
	sf::RenderWindow		window;
	sf::View				view;

	const					char *title;
	bool					fullscreen;
	unsigned int			width;
	unsigned int			height;

public:
	Window(const char *, unsigned int width = 1138, unsigned int height = 640, bool fullscreen = false);
	~Window();

	void					launchWindow();
	void					switchFullscreen();
	bool					isOpen() const;

	void					attachGameplay(Gameplay *);
	void					callGameplay();
};

#endif /* !WINDOW_H_ */