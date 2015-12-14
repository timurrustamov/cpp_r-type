//
// Created by rustam_t on 12/8/15.
//

#ifndef CPP_R_TYPE_WORLD_HPP
#define CPP_R_TYPE_WORLD_HPP

#include "Geometry.hpp"
#include "QuadTree.hpp"

#define MAX_PLAYERS 4

class World {

public:
    World(t2Vector<int> size, bool verticalWalls = true, bool horizontalWalls = false);
    ~World();

    World &newGeometry(Geometry *geo);
    Geometry *newGeometry(const Rectangle<float> &obj, float terminalVelocity, float accelerationTime, float inertiaRatio);
    World &bindPlayerObject(Geometry *geo);
    Geometry *bindPlayerObject(const Rectangle<float> &obj, float terminalVelocity, float accelerationTime, float inertiaRatio);
    World & removePlayerObject(Geometry *geo);
    World & tick(float seconds);

    std::vector<Geometry *> _objects;
    std::vector<Geometry *> _players;
private:

    QuadTree _qt;
};


#endif //CPP_R_TYPE_WORLD_HPP
