//
// Created by rustam_t on 11/24/15.
//

#include <algorithm>
#include "QuadTree.hpp"

QuadTree::QuadTree(const Rectangle<int> &rec) {

    this->level = 0;
    this->obj = rec;
    this->parent = NULL;
    int i = -1;
    while (++i < 4)
        this->nodes[i] = NULL;
}

QuadTree::QuadTree(int pLevel, QuadTree *parent, const Rectangle<int> &rec) {

    this->level = pLevel;
    this->obj = rec;
    this->parent = parent;
    int i = -1;
    while (++i < 4)
        this->nodes[i] = NULL;
}

QuadTree::~QuadTree()
{
    this->clear();
}

QuadTree &
QuadTree::clear()
{
    int i = -1;
    while (++i < 4) {
        if (this->nodes[i] != NULL)
            delete (this->nodes[i]);
        this->nodes[i] = NULL;
    }
    for (std::list<Geometry *>::iterator it = this->objects.begin(); it != this->objects.end(); it++)
        (*it)->detach();
    return (*this);
}

unsigned int
QuadTree::countSubTotal() const
{
    unsigned int result = 0;
    int i = -1;

    if (this->nodes[0] != NULL)
        while (++i < 4)
            result += this->nodes[i]->countSubTotal();

    result += this->objects.size();
    return (result);
}

QuadTree &
QuadTree::split()
{
    t2Vector<int> psize(this->obj.getSize() / 4);
    t2Vector<int> plusX(psize.getX(), 0);
    t2Vector<int> plusY(0, psize.getY());

    this->nodes[0] = new QuadTree(level + 1, this, Rectangle<int>(psize, this->obj.getPosition() - psize));
    this->nodes[1] = new QuadTree(level + 1, this, Rectangle<int>(psize, this->obj.getPosition() - plusY));
    this->nodes[2] = new QuadTree(level + 1, this, Rectangle<int>(psize, this->obj.getPosition() - plusX));
    this->nodes[3] = new QuadTree(level + 1, this, Rectangle<int>(psize, this->obj.getPosition()));
    for (std::list<Geometry *>::iterator it = this->objects.begin(); it != this->objects.end(); it++)
        this->insert(*it);
    return (*this);
}

QuadTree &
QuadTree::collapse()
{
    int i = -1;
    if (this->nodes[0] != NULL)
        while (++i < 4) {
            this->nodes[i]->collapse();
            for (std::list<Geometry *>::iterator it = this->nodes[i]->objects.begin(); it != this->nodes[i]->objects.end(); it++) {
                (*it)->attach(this, true);
                this->nodes[i]->objects.clear();
            }
            delete this->nodes[i];
            this->nodes[i] = NULL;
        }
    return (*this);
}

bool
QuadTree::objectExists(Geometry *geo) const
{
    if (this->parent != NULL)
        return (this->parent->objectExists(geo));

    return (this->has(geo));
}

bool
QuadTree::has(Geometry *geo) const
{
    if (std::find(this->objects.begin(), this->objects.end(), geo) != this->objects.end())
        return (true);

    int i = -1;
    if (this->nodes[0])
        while (++i < 4)
            if (this->nodes[i]->has(geo))
                return (true);
    return (false);
}

QuadTree *
QuadTree::insert(Geometry *geo, bool parentTest)
{
    QuadTree *tmp;

    if (parentTest && !geo->getRect().fitsIn(this->obj))
    {
        if (this->parent != NULL)
            return (this->parent->insert(geo));
    }
    else if (!parentTest && !geo->getRect().fitsIn(this->obj))
        return (NULL);

    int i = -1;
    if (this->nodes[0] != NULL && this->nodes[0]->obj.getSize() >= geo->getSize())
        while (++i < 4)
            if ((tmp = this->nodes[i]->insert(geo, false)) != NULL)
                return (tmp);

    if (this->nodes[0] == NULL && this->objects.size() > MAX_OBJECTS && this->level < MAX_LEVELS && this->obj.getSize() / 4 >= geo->getSize()) {

        std::cout << "SPLIT level " << this->level << std::endl;
        return (this->split().insert(geo));
    }

    if (geo->getNode() != this) {

        if (geo->getNode() != NULL)
            geo->detach();
        geo->attach(this, true);
        this->objects.push_back(geo);
    }
    return (this);
}

QuadTree &
QuadTree::remove(Geometry *geo)
{
    std::list<Geometry *>::iterator it;
    if ((it = std::find(this->objects.begin(), this->objects.end(), geo)) != this->objects.end()) {
        //(*it)->hardDetach();
        this->objects.erase(it);
    }
    if (this->parent != NULL && this->parent->countSubTotal() <= MAX_OBJECTS)
        return (this->parent->collapse());
    return (*this);
}

unsigned long int
QuadTree::retrieveObjects(std::list<Geometry *> &objects, bool searchSon)
{
    if (this->parent != NULL)
        return (this->parent->retrieveObjects(objects, false));
    int i = -1;
    if (this->nodes[0] != NULL && searchSon)
        while (++i < 4)
            this->nodes[i]->retrieveObjects(objects);
    objects.insert(objects.end(), this->objects.begin(), this->objects.end());
    return (objects.size());
}

void
QuadTree::testCollision(Geometry *geo, std::map<Geometry *, std::vector<Geometry *> > interactionmap)
{
    if (geo->getNode() == NULL)
        return;
    std::list<Geometry*> objects;
    geo->getNode()->retrieveObjects(objects);

    for (std::list<Geometry *>::iterator it = objects.begin(); it != objects.end(); it++)
        if (geo != *it &&
            std::find(interactionmap[geo].begin(), interactionmap[geo].end(), *it) == interactionmap[geo].end() &&
            geo->getRect().touches((*it)->getRect()))
        {
            geo->getNode()->collision(geo, *it);
            interactionmap[*it].push_back(geo);
        }
}


//geo1 is always the one initializing collision
void
QuadTree::collision(Geometry *geo1, Geometry *geo2)
{
    Geometry *tmp[2];

    geo1->removeImpulse();
    geo2->applyImpulse(geo2->getPosition() - geo1->getPosition());
    //geo2->setPosition(geo2->getPreviousPosition(9));

    if (geo1->getRect().touchUpper(geo2->getRect()) || geo1->getRect().touchLower(geo2->getRect()))
        geo1->velocity().y() *= -1;
    if (geo1->getRect().touchLeft(geo2->getRect()) || geo1->getRect().touchRight(geo2->getRect()))
        geo1->velocity().x() *= -1;
    geo1->setPosition(geo1->getPreviousPosition(1));
//    if (geo1->getRect().fitsIn(geo2->getRect()))
//        geo1->setPosition(t2Vector<float>(std::rand() % 400, std::rand() % 400));
    //geo1->attach(this);
}
