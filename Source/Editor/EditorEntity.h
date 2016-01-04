#ifndef EDITOR_ENTITY
# define EDITOR_ENTITY

# include						"../System/Animation.h"
# include						"../GameEngine/AnimationEntity.hpp"
# include						"../GameEngine/t2Vector.hpp"

class							EditorEntity
{
protected:
	EditorEntity() {};
	t2Vector<unsigned int>		position;

public:
	EditorEntity(unsigned int identifier);
	EditorEntity(Animation *animation);
	EditorEntity(EditorEntity const &);
	~EditorEntity() {};

	Animation					*animation;
	AnimationEntity				entity;
	unsigned int				range;
	unsigned int				identifier;

	void						setPosition(unsigned int x, unsigned int y);
	void						setPosition(t2Vector<unsigned int> new_position);
	void						setPosition(sf::Vector2i new_position);

	t2Vector<unsigned int>		getPosition() const;
	unsigned int				getRange() const;
	unsigned int				getIdentifier() const;
	Animation					*getAnimation() const;
};

std::ostream					&operator<<(std::ostream &, const EditorEntity &);

#endif /* !EDITOR_ENTITY */