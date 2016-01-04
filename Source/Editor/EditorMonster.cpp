#include						"EditorMonster.h"
#include						"../GameEngine/Monster.h"
#include						"../GameEngine/t2Vector.hpp"

EditorMonster::EditorMonster(std::string const &dllName) : EditorEntity(), dll(dllName)
{
	Monster						sample(dllName);

	sample.start();
	this->animation = sample.getBehaviour()->getAnimationSheet();
	this->identifier = sample.getIdentifier();
	this->position = t2Vector<unsigned int>(0, 0);
	this->range = static_cast<int>(sample.geometry->getSize().distanceTo(t2Vector<int>(0, 0)));
}

EditorMonster::EditorMonster(EditorMonster &other) : EditorEntity(other), dll(other.dll)
{}