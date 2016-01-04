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
# include                               "MutexVault.hpp"
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

        IMutex *mutex = (*MutexVault::getMutexVault())["gameobjects"];

        mutex->lock();
        if (typeid(T) == typeid(Player)) {
            mutex->unlock();
            return (BAD_ID);
        }
        newobj = new T(position);
        this->_objects[newobj->getId()] = newobj;
        this->_qt.insert(newobj->geometry);
        mutex->unlock();
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

        IMutex *mutex = (*MutexVault::getMutexVault())["gameobjects"];

        mutex->lock();
        if (playerNo > MAX_PLAYERS) {
            mutex->unlock();
            return (BAD_ID);
        }
        if (this->_playersId[playerNo] != BAD_ID) {
            mutex->unlock();
            return (this->_playersId[playerNo]);
        }
        newobj = new Player(position + t2Vector<int>(0, playerNo * 30), playerNo);
		newobj->start();
        this->_qt.insert(newobj->geometry);
        id = newobj->getId();
        this->_objects[id] = newobj;
        this->_playersId[playerNo] = id;
        mutex->unlock();
        return (id);
    }

    unsigned int						createNewPlayer(int x, int y, unsigned int playerNo)
    {
        return (this->createNewPlayer(t2Vector<int>(x, y), playerNo));
    }

    Snapshot							*getSnapshot();
    World								&loadSnapshot(Snapshot *);
    World								&tick(float seconds);
    World                               &loadPlayerActions(unsigned int playerNo, std::vector<int> *actions);

    Object								*getPlayerObject(unsigned int playerNo)
    {
        IMutex *mutex = (*MutexVault::getMutexVault())["gameobjects"];

        mutex->lock();
        Object *obj = NULL;

        if (playerNo < MAX_PLAYERS && this->_playersId[playerNo] != BAD_ID)
            obj = this->_objects[this->_playersId[playerNo]];
        mutex->unlock();
        return (obj);
    }

    Object								*getObject(unsigned int objectId)
    {
        IMutex *mutex = (*MutexVault::getMutexVault())["gameobjects"];

        mutex->lock();
        Object *obj = NULL;
        if (this->_objects.find(objectId) != this->_objects.end())
            obj = this->_objects[objectId];
        mutex->unlock();
        return (obj);
    }
};

#endif /* !CPP_R_TYPE_WORLD_HPP */