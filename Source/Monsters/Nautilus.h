#ifndef NAUTILUS_H_
# define NAUTILUS_H_

# include						"../GameEngine/Object.h"
# include						"../GameEngine/IMonsterBehaviour.h"

class Nautilus :				public IMonsterBehaviour
{
	int							life;
	bool						upValve;

	Object						*object;
	Animation					*animation;
	Animation					*animationHit;
	AnimationEntity				*entity;

public:
	Nautilus() {};
	~Nautilus() { delete this->entity; };

	virtual void				lateUpdate();
	virtual void				interact(Object *);
	virtual void				start(Object * const that);
	virtual void				parseConfig(std::string);
	virtual void				onDestroy();
};

#endif /* !NAUTILUS_H_ */