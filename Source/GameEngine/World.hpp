//
// Created by rustam_t on 12/8/15.
//

#ifndef CPP_R_TYPE_WORLD_HPP
# define CPP_R_TYPE_WORLD_HPP

# include								<cstddef>
# include								"Object.h"
# include								"QuadTree.hpp"
# include								"Player.hpp"
# include								"WallOfPain.hpp"
# include								"Snapshot.hpp"
# include								<typeinfo>

# define MAX_PLAYERS					4

class									Snapshot;

class									World
{
	std::map<unsigned int, Object *>	_objects;
	std::vector<unsigned int>			_playersId;
	QuadTree _qt;
    std::map<unsigned int, Object *>    _samples;

public:
	World(t2Vector<int> size, bool verticalWalls = true, bool horizontalWalls = false);
    ~World();

    //transfer the ownership to world
    World &                             addSample(Object *);

    template <typename T>
    unsigned int						createNewObject(const t2Vector<int> &position)
    {
        Object							*newobj;

        if (typeid(T) == typeid(Player))
            return (BAD_ID);
        newobj = new T(position);
        this->_objects[newobj->getId()] = newobj;
        this->_qt.insert(newobj->geometry);

        std::cout << newobj->getId() << std::endl;
        return (newobj->getId());
    };

    template							<typename T>
    unsigned int						createNewObject(int x, int y)
    {
        return (this->createNewObject<T>(t2Vector<int>(x, y)));
    };

	unsigned int						createNewObject(Object *object);

    unsigned int                        createNewObject(Object::Type type);

    unsigned int                        createNewObject(unsigned int identifier, SerializedObject *serializedObject = NULL);

    unsigned int						createNewPlayer(const t2Vector<int> &position, unsigned int playerNo)
    {
        Object *newobj;
        unsigned int id;

        if (playerNo > MAX_PLAYERS)
            return (BAD_ID);
        if (this->_playersId[playerNo] != BAD_ID)
            return (this->_playersId[playerNo]);
        newobj = new Player(position, playerNo);
        id = newobj->getId();
        this->_objects[id] = newobj;
        this->_playersId[playerNo] = id;
        return (id);
    }

    unsigned int						createNewPlayer(int x, int y, unsigned int playerNo)
    {
        return (this->createNewPlayer(t2Vector<int>(x, y), playerNo));
    }

    Snapshot							*getSnapshot();
    World								&loadSnapshot(Snapshot *);
    World								&tick(float seconds);

    Object								*getPlayerObject(unsigned int playerNo)
    {
        if (playerNo > MAX_PLAYERS || this->_playersId[playerNo] == BAD_ID)
            return (NULL);
        return (this->_objects[this->_playersId[playerNo]]);
    }

    Object								*getObject(unsigned int objectId)
    {
        return (this->_objects[objectId]);
    }
};

#endif /* !CPP_R_TYPE_WORLD_HPP */