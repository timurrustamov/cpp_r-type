//
// Created by rustam_t on 11/24/15.
//

#ifndef CPP_R_TYPE_QUADTREE_HPP
#define CPP_R_TYPE_QUADTREE_HPP

#include <cstddef>
#include <list>
#include <map>
#include "Geometry.hpp"

#define MAX_OBJECTS 90
#define MAX_LEVELS 5

class Geometry;

class QuadTree {

public:
    QuadTree(const Rectangle<int> &rec);

    ~QuadTree();

    QuadTree &  clear();
    bool        has(Geometry *geo) const;
    bool        objectExists(Geometry *geo) const;
    unsigned int countSubTotal() const;
    const t2Vector<int> &getSize() const;
    QuadTree &  split();
    QuadTree &  collapse();
    QuadTree *  insert(Geometry *geo, bool parentTest = true);
    QuadTree &  remove(Geometry *geo);

   // QuadTree &  realign(Geometry *geo1, Geometry *geo2);

    unsigned long int       retrieveObjects(std::list<Geometry*> &, bool searchSon = true);
    Geometry                *testCollision(Geometry *geo, std::map<Geometry *, std::vector<Geometry *> > interactionmap);
private:

    QuadTree(int pLevel, QuadTree *parent, const Rectangle<int> &rec);
    void        collision(Geometry *geo1, Geometry *geo2);

    int                     level;
    std::list<Geometry *>   objects;
    Rectangle<int>          obj;
    QuadTree *              parent;
    QuadTree *              nodes[4];

};


#endif //CPP_R_TYPE_QUADTREE_HPP
