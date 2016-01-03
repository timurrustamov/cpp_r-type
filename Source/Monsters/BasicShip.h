#ifndef BASICSHIP_H_
# define BASICSHIP_H_

# include						"../GameEngine/Object.h"
# include						"../GameEngine/IMonsterBehaviour.h"

class BasicShip :				public IMonsterBehaviour
{
	int							life;
	Object						*object;
	Animation					*animation;
	Animation					*animationHit;
	AnimationEntity				*entity;

public:
	BasicShip() {};
	~BasicShip() { delete this->entity; };

	virtual void				lateUpdate();
	virtual void				interact(Object *);
	virtual void				start(Object * const that);
	virtual void				parseConfig(std::string);
	virtual void				onDestroy();
};

#endif /* !BASICSHIP_H_ */