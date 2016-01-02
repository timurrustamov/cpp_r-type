#ifndef MONSTER_H_
# define MONSTER_H_

# include					"Object.h"
# include					"../System/Animation.h"
# include					"../System/ResourcesBank.h"
# include					"IMonsterBehaviour.h"

class Monster :				public Object
{
public:
	Monster(std::string dll, t2Vector<int> position = t2Vector<int>(0, 0));
	virtual ~Monster();

	virtual Object			*clone(SerializedObject *serializedObject);
	virtual void			interact(Object *);
	virtual void			lateUpdate();
	virtual void			start();

protected:
	std::string				dll;
	IMonsterBehaviour		*behaviour;
};

#endif /* !MONSTER_H_ */