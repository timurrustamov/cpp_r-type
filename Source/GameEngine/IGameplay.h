#ifndef IGAMEPLAY_H_
# define IGAMEPLAY_H_

# include			<SFML/Window/Event.hpp>
# include			"GameData.h"

class				IGameplay
{
public:
	virtual			~IGameplay() {}

	void			virtual keyPressed(sf::Keyboard::Key) = 0;
};

#endif /* !IGAMEPLAY_H_ */