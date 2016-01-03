//
// Created by rustam_t ET BOREL FUCKING D on 12/15/15.
//

#ifndef CPP_R_TYPECPY2_ROCKET_HPP
# define CPP_R_TYPECPY2_ROCKET_HPP

# include					"Object.h"
# include					"Explosion.h"
# include					"../System/Animation.h"
# include					"../System/ResourcesBank.h"

class Rocket :				public Object
{
public:
	enum					Type
	{
		LowEnergy,
		Energy,
		LowPhysic,
		Physic,
	};

    Rocket(Rocket::Type type, t2Vector<int> position);
    virtual ~Rocket() { delete this->entity; };

	virtual Object			*clone(SerializedObject *serializedObject);
    virtual void			interact(Object *);
	virtual void			lateUpdate();
	virtual void			start();

protected:
	Animation				*animation;
	AnimationEntity			*entity;
	sf::Sound				se;

	Rocket::Type			rocketType;
	unsigned char			initialState;
	unsigned char			explosionEnum;
};

#endif /* !CPP_R_TYPECPY2_ROCKET_HPP */