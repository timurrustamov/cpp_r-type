#ifndef ARTIFICES_H_
# define ARTIFICES_H_

# include					"Object.h"
# include					"../System/Animation.h"
# include					"../System/ResourcesBank.h"

class Artifices :			public Object
{
public:
	enum					Type
	{
		Explosion
	};

	Artifices(Artifices::Type type, t2Vector<int> position = t2Vector<int>(0, 0));
	virtual ~Artifices() {};

	virtual Object			*clone(SerializedObject *serializedObject);
	virtual void			interact(Object *);
	virtual void			lateUpdate();
	virtual void			start();

protected:
	Animation				*animation;
	AnimationEntity			*entity;

	t2Vector<int>			size;
	t2Vector<unsigned int>	gridPosition;
	t2Vector<unsigned int>	grid;

	unsigned char			minState;
	unsigned char			maxState;

	Artifices::Type			artificeType;
	const char				*animationID;
	const char				*textureName;
};

#endif /* !ARTIFICES_H_ */