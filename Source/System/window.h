#ifndef WINDOW_H_
# define WINDOW_H_

# include					<string>
# include					<SFML/Graphics.hpp>
# include					<SFML/Graphics/Drawable.hpp>
# include					"RTypeException.h"
# include					"../GameEngine/IGameplay.h"

class						Window
{
	IGameplay				*gameplay;
	
	sf::View				view;
	sf::Clock				deltaClock;
	sf::Time				time;

	const					char *title;
	bool					fullscreen;
	unsigned int			width;
	unsigned int			height;

public:
	sf::RenderWindow		window;

	Window(const char *, unsigned int width = 0, unsigned int height = 0, bool fullscreen = false);
	~Window();

	void					launchWindow();
	void					switchFullscreen();
	bool					isOpen() const;

	void					attachGameplay(IGameplay *);
	void					callGameplay();

	unsigned int			getWidth() const;
	unsigned int			getHeight() const;

	void					draw(const sf::Drawable &drawable, const sf::RenderStates &states = sf::RenderStates::Default);
};

#endif /* !WINDOW_H_ */