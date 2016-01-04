#ifndef ROBOT_H_
# define ROBOT_H_

# include						"../GameEngine/Object.h"
# include						"../GameEngine/IMonsterBehaviour.h"

class Robot :					public IMonsterBehaviour
{
	int							life;
	bool						freeFall;
	Object						*object;
	Animation					*animation;
	Animation					*animationHit;
	AnimationEntity				*entity;

public:
	Robot() {};
	~Robot() {

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

#endif /* !ROBOT_H_ */