#include						"EditorEntity.h"
#include						"../GameEngine/GameData.h"
#include						"../GameEngine/Object.h"

EditorEntity::EditorEntity(unsigned int _identifier) : identifier(_identifier), animation(NULL), entity()
{
	this->entity.setId(GameData::getInstance()->getNewEntityId());
}

EditorEntity::EditorEntity(Animation *_animation) : animation(_animation), identifier(0), entity()
{
	this->entity.setId(GameData::getInstance()->getNewEntityId());
}

EditorEntity::EditorEntity(EditorEntity const &other) : animation(other.getAnimation()), position(other.getPosition()), identifier(other.getIdentifier()), entity()
{
	this->entity.setId(GameData::getInstance()->getNewEntityId());
}

void						EditorEntity::setPosition(unsigned int x, unsigned int y)
{
	this->position = t2Vector<unsigned int>(x, y);
	this->entity.setPosition(t2Vector<int>(x, y));
}

void						EditorEntity::setPosition(t2Vector<unsigned int> new_position)
{
	this->position = new_position;
	this->entity.setPosition(t2Vector<int>(new_position.getX(), new_position.getY()));
}

void						EditorEntity::setPosition(sf::Vector2i new_position)
{
	this->position = t2Vector<unsigned int>(new_position.x, new_position.y);
	this->entity.setPosition(t2Vector<int>(new_position.x, new_position.y));
}

t2Vector<unsigned int>		EditorEntity::getPosition() const
{
	return (this->position);
}

unsigned int				EditorEntity::getRange() const
{
	return (this->range);
}

unsigned int				EditorEntity::getIdentifier() const
{
	return (this->identifier);
}

Animation					*EditorEntity::getAnimation() const
{
	return (this->animation);
}

/*
Animation					*animation;
AnimationEntity				entity;
t2Vector<unsigned int>		position;
unsigned int				range;
unsigned int				identifier;
*/

std::ostream				&operator<<(std::ostream& os, const EditorEntity& that)
{
	os << "Identifier" << that.identifier << std::endl;
	os << "Position: " << that.getPosition() << std::endl;
	os << "Range: " << that.range << std::endl;
	return (os);
}