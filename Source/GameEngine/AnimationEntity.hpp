#ifndef ANIMATIONENTITY_HPP_
# define ANIMATIONENTITY_HPP_

# include				<cstddef>
# include				"t2Vector.hpp"

class					AnimationEntity
{
	unsigned int		id;
	unsigned int		state;
	t2Vector<int>		position;

public:
	AnimationEntity(unsigned int _id, unsigned int _state, t2Vector<int> _position) : id(_id), state(_state), position(_position) {};
	AnimationEntity() : id(0), state(0), position(t2Vector<int>(0, 0)) {};
	~AnimationEntity() {};

	void				setId(unsigned int newId) { this->id = newId; }
	void				setState(unsigned int newState) { this->state = newState; }
	void				setPosition(t2Vector<int> newPosition) { this->position = newPosition; }

	unsigned int		getId() const { return (this->id); }
	unsigned int		getState() const { return (this->state); }
	t2Vector<int>		getPosition() const { return (this->position); }
};

#endif /* !ANIMATIONENTITY_HPP_ */