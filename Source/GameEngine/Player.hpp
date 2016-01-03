//
// Created by rustam_t on 12/14/15.
//

#ifndef CPP_R_TYPECPY2_PLAYER_HPP
# define CPP_R_TYPECPY2_PLAYER_HPP

# include				<cstddef>
# include				<SFML/Window/Event.hpp>
# include				"Rocket.hpp"
# include				"Laser.h"
# include				"../System/Animation.h"
# include				"../System/ResourcesBank.h"

class Player :			public Object
{
public:
    Player(t2Vector<int> position, unsigned int);
    Player(int x, int y, unsigned int);
    virtual ~Player() { delete this->entity; };

    unsigned int		getPlayerNo() const;

	virtual Object		*clone(SerializedObject *serializedObject);
    virtual void		interact(Object *);
	virtual void		lateUpdate();
	virtual void		start();

	void 				move(std::vector<sf::Keyboard::Key> key);
	void				launchRocket(Rocket::Type type);
	void				laser(Laser::Type type);
	void				chargeShot();
	void				unleashShot();

protected:
	Animation			*animation;
	Animation			*chargeShotLoading;
	AnimationEntity		*entity;
	AnimationEntity		*chargeShotEntity;

	sf::Sound			chargeShot1;
	sf::Sound			chargeShot2;

    unsigned int		playerNo;
};

#endif /* !CPP_R_TYPECPY2_PLAYER_HPP */