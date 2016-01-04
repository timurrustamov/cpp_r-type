#ifndef EDITOR_ENTITY
# define EDITOR_ENTITY

# include						"../System/Animation.h"
# include						"../GameEngine/AnimationEntity.hpp"
# include						"../GameEngine/t2Vector.hpp"

class							EditorEntity
{
protected:
	Animation					*animation;
	AnimationEntity				entity;
	t2Vector<unsigned int>		position;
	unsigned int				range;
	unsigned int				identifier;

	EditorEntity() {};
public:
	EditorEntity(unsigned int identifier);
	~EditorEntity() {};
};

#endif /* !EDITOR_ENTITY */