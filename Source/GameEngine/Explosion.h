//
// Created by rustam_t on 12/15/15.
//

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

	Explosion(Explosion::Type type, bool hurting, t2Vector<int> position);
	virtual ~Explosion() {};

	virtual void			interact(Object *);
	virtual void			lateUpdate();
	virtual void			start();

protected:
	Animation				*animation;
	AnimationEntity			*entity;
	unsigned int			collisionNo;

	const char				*animationID;
	Explosion::Type			explosionType;
	bool					hurting;
	t2Vector<int>			size;
	t2Vector<unsigned int>	grid;
};

#endif /* !EXPLOSION_H_ */