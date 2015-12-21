//
// Created by rustam_t on 12/16/15.
//

#ifndef CPP_R_TYPECPY2_SNAPSHOT_HPP
#define CPP_R_TYPECPY2_SNAPSHOT_HPP

#include "World.hpp"
#include "SerializedObject.hpp"

#define MAGIC_SNAP 0xFA5EB00B

class World;

class Snapshot {

public:

    Snapshot(const t2Vector<int> &size, std::vector<SerializedObject *> &objects);
    Snapshot(std::vector<unsigned char> &binary);
    ~Snapshot();

    std::vector<unsigned char>  &toBinary();
    bool                        isInited() const;

    t2Vector<int>                   size;
    std::map<unsigned int, SerializedObject *> objects;

private:

    bool                            inited;
    std::vector<unsigned char>      binaryString;
};


#endif //CPP_R_TYPECPY2_SNAPSHOT_HPP
