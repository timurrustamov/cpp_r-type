#ifndef OBJECT_H_
# define OBJECT_H_

# include								<cstddef>
# include								<string>
# include 								"Timer.hpp"
# include								"AnimationEntity.hpp"

# define BAD_ID							0xB16B00B5

class 									Geometry;
class									SerializedObject;

class									Object
{
public:
	enum								Type
	{
		WallOfPain,
		Obstacle,
		Ennemy,
		Character,
		Projectile,
		Radiation,
		Force,
		Other
	};

	Geometry							*geometry;
	Timer 								timer;

	virtual ~Object();

	virtual Object						*clone(SerializedObject *serializedObject) = 0;
	virtual void						lateUpdate() = 0;
	virtual void						interact(Object *) = 0;
	virtual void						start() = 0;

	Type								getType() const;
	unsigned int 						getId() const;
	void 								setId(unsigned int);
	unsigned int						getIdentifier() const;

	bool								mustBeDeleted() const;
	bool								setToDelete();
	void								setValues(SerializedObject *serializedObject);
	void								setIdentifier(unsigned int);

private:
	unsigned int						static getNewId();

protected:
	Type								type;

	unsigned int						identifier;
	unsigned int						id;
	bool 								to_delete;

	Object();
	Object(Geometry &, Type);
	Object(Geometry *, Type);
};

# include				"SerializedObject.hpp"
# include				"Geometry.hpp"

#endif /* !OBJECT_H_ */