#ifndef IGAMEPLAY_H_
# define IGAMEPLAY_H_

# include			<SFML/Window/Event.hpp>
# include			<SFML/Graphics/Drawable.hpp>
# include			"GameData.h"

class				IGameplay : public sf::Drawable
{
public:
	virtual			~IGameplay() {}

	void			virtual keyPressed(sf::Keyboard::Key) = 0;
	void			virtual updateGraphics() = 0;
};

#endif /* !IGAMEPLAY_H_ */