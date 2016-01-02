#ifndef GAMEDATA_H_
# define GAMEDATA_H_

# include				<cstddef>
# include				"../System/RTypeException.h"
# include				"../System/ResourcesBank.h"
# include				"t2Vector.hpp"
# include				"World.hpp"

# ifdef _GNUC
#  define ATTR_UNUSED __attribute__((unused))
# else
#  define ATTR_UNUSED
# endif

# define MAX_IDENTIFIER	42

class					GameData
{
public:
	enum				Identifier
	{
		Player1 = 0,
		Player2,
		Player3,
		Player4,
		WallOfPain,
		Laser,
		MiddleChargeShot,
		ChargeShot,
		RocketWeakLaser,
		RocketStrongLaser,
		RocketWeakPhysic,
		RocketStrongPhysic,
		ExplosionWeakLaser,
		ExplosionStrongLaser,
		ExplosionWeakPhysic,
		ExplosionStrongPhysic,
		ArtificeExplosion
	};
private:

	bool				fullscreen;
	bool				mustQuit;
	unsigned int		width;
	unsigned int		height;

	GameData();
	~GameData();

public:
	static GameData		*getInstance(bool _delete = false);
	ResourcesBank		*resourceBank;
	World				*world;

	void				setFullscreen(bool);
	void				setMustQuit(bool);

	bool				getFullscreen() const;
	bool				getMustQuit() const;

	void				setWorld(t2Vector<int> size, bool verticalWalls = true, bool horizontalWalls = false);
	unsigned int		getWidth() const;
	unsigned int		getHeight() const;
};

#endif /* !GAMEDATA_H_ */