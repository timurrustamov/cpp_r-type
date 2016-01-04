#ifndef METEORA_H_
# define METEORA_H_

# include						"../GameEngine/Object.h"
# include						"../GameEngine/IMonsterBehaviour.h"

class Meteora :					public IMonsterBehaviour
{
	int							life;
	Object						*object;
	Animation					*animation;
	Animation					*animationHit;
	AnimationEntity				*entity;

public:
	Meteora() {};
	~Meteora() {

		if (this->entity != NULL) {
			this->animation->removeEntity(this->entity->getId());
			delete this->entity;
		}
	};
	virtual void				lateUpdate();
	virtual void				interact(Object *);
	virtual void				start(Object * const that);
	virtual void				parseConfig(std::string);
	virtual void				onDestroy();
	virtual Animation			*getAnimationSheet() const;
};

#endif /* !METEORA_H_ */