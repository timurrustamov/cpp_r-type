#ifndef OBJECT_H_
# define OBJECT_H_

# include				<string>
# include				"Geometry.hpp"

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

private:
	Geometry			*geometry;
	std::string			name;
	Type				type;
	unsigned int		id;

	Object(Geometry &, std::string const &, Type);
	Object(Geometry *, std::string const &, Type);
	~Object();

private:
	unsigned int		static getId();
};

#endif /* !OBJECT_H_ */