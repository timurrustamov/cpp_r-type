//
// Created by rustam_t on 12/16/15.
//

#include "Snapshot.hpp"

Snapshot::Snapshot(std::vector<unsigned char> &binary) : inited(false) {

    unsigned int magic = MAGIC_SNAP;
    int x;
    int y;
    SerializedObject *newobj;
    unsigned int headerSize = sizeof(magic) + sizeof(this->size.getX()) + sizeof(this->size.getY());
    unsigned int current_length = 0;

    if (binary.size() < headerSize || magic != *(reinterpret_cast<unsigned int *>(&binary[0])) ||
        (binary.size() - headerSize) % sizeof(ObjectAttributes) != 0)
        return;
    std::memcpy(&x, &binary[sizeof(magic)], sizeof(x));
    std::memcpy(&y, &binary[sizeof(magic) + sizeof(x)], sizeof(y));
    this->size.assign(x, y);
    this->inited = true;
    if (binary.size() - headerSize == 0)
        return;
    current_length = headerSize;
    for (unsigned int i = 0; i < binary.size() - headerSize; i += sizeof(ObjectAttributes))
    {
        newobj = new SerializedObject(&binary[i], binary.size() - current_length);
        this->objects[newobj->attr.id] = newobj;
        current_length += sizeof(ObjectAttributes);
    }
}

Snapshot::~Snapshot() {

    for (std::map<unsigned int, SerializedObject *>::iterator it = this->objects.begin(); it != this->objects.end(); it++)
        delete (it->second);
}

std::vector<unsigned char> &
Snapshot::toBinary() {

    unsigned int magic = MAGIC_SNAP;
    int x = this->size.getX();
    int y = this->size.getY();
    unsigned int headerSize = sizeof(magic) + sizeof(x) + sizeof(y);
    binaryString.resize(headerSize + this->objects.size() * sizeof(ObjectAttributes));

    std::memcpy(&binaryString[0], &magic, sizeof(magic));
    std::memcpy(&binaryString[sizeof(magic)], &x, sizeof(x));
    std::memcpy(&binaryString[sizeof(magic) + sizeof(x)], &y, sizeof(y));

    int i = 0;
    for (std::map<unsigned int, SerializedObject *>::iterator it = this->objects.begin(); it != this->objects.end(); it++)
        std::memcpy(&this->binaryString[headerSize + i++ * sizeof(ObjectAttributes)], it->second, sizeof(ObjectAttributes));
    return (this->binaryString);
}

bool
Snapshot::isInited() const
{
    return (this->inited);
}

Snapshot::Snapshot(const t2Vector<int> &size, std::vector<SerializedObject *> &objects) {

    this->size = size;
    for (unsigned int i = 0; i < objects.size(); i++)
        this->objects[objects[i]->attr.id] = objects[i];
    this->inited = true;
}
