#ifndef CPP_LASER_H_
# define CPP_LASER_H_

# include					"Object.h"
# include					"Explosion.h"
# include					"../System/Animation.h"
# include					"../System/ResourcesBank.h"

class Laser :				public Object
{
public:
	enum					Type
	{
		Shot,
		MiddleChargeShot,
		ChargeShot
	};

	Laser(Laser::Type type, t2Vector<int> position);
	virtual ~Laser() { delete this->entity; };

	virtual Object			*clone(SerializedObject *serializedObject);
	virtual void			interact(Object *);
	virtual void			lateUpdate();
	virtual void			start();

protected:
	Animation				*animation;
	AnimationEntity			*entity;
	sf::Sound				se;

	Laser::Type				laserType;
	const char				*animationID;
	t2Vector<unsigned int>	gridPosition;
};

#endif /* !CPP_LASER_H_ */