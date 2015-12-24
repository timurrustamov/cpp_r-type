#ifndef EXPLOSION_H_
# define EXPLOSION_H_

# include					"Object.h"
# include					"../System/Animation.h"
# include					"../System/ResourcesBank.h"

class Explosion :			public Object
{
public:
	enum					Type
	{
		SmallEnergy,
		Energy,
		SmallPhysic,
		Physic,
	};

	Explosion(Explosion::Type type, t2Vector<int> position = t2Vector<int>(0, 0));
	virtual ~Explosion() {};

	virtual Object			*clone(SerializedObject *serializedObject);
	virtual void			interact(Object *);
	virtual void			lateUpdate();
	virtual void			start();

protected:
	Animation				*animation;
	AnimationEntity			*entity;

	t2Vector<int>			size;
	t2Vector<unsigned int>	grid;

	Explosion::Type			explosionType;
	const char				*animationID;
	unsigned char			impulseFactor;
};

#endif /* !EXPLOSION_H_ */