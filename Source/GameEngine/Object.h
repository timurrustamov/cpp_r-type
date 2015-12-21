#ifndef OBJECT_H_
# define OBJECT_H_

# include				<string>
# include 				"Timer.hpp"

#define BAD_ID 0xB16B00B5

class 					Geometry;

class					Object
{
public:

	enum				Type
	{
		WallOfPain,
		Obstacle,
		Ennemy,
		Character,
		Projectile,
		Other
	};

	Geometry			*geometry;
	virtual ~Object();

	virtual void interact(Object *) = 0;
	Type  getType() const;
	unsigned int 		getId() const;
	const std::string 	&getName() const;
	bool mustBeDeleted() const;
	bool setToDelete();
	Timer 				timer;

private:

	unsigned int		static getNewId();

protected:
	std::string			name;
	Type				type;
	unsigned int		id;
	bool 				to_delete;

	Object();
	Object(Geometry &, std::string const &, Type);
	Object(Geometry *, std::string const &, Type);

};

# include				"Geometry.hpp"

#endif /* !OBJECT_H_ */