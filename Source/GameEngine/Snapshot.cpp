//
// Created by rustam_t on 12/16/15.
//

#include "Snapshot.hpp"

Snapshot::Snapshot(const t2Vector<int> &size, std::vector<SerializedObject *> &objects) {

    this->size = size;
    for (unsigned int i = 0; i < objects.size(); i++)
        this->objects[objects[i]->attr.id] = objects[i];
}

Snapshot::~Snapshot() {

    for (std::map<unsigned int, SerializedObject *>::iterator it = this->objects.begin(); it != this->objects.end(); it++)
        delete (it->second);
}


