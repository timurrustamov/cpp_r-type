//
// Created by rustam_t on 10/13/15.
//

#ifndef CPP_BABEL_PACKET_H
#define CPP_BABEL_PACKET_H

#include <string>
#include <vector>
#include <typeinfo>
#include "Instruction.h"
#include "SerializedObject.hpp"
#include "Snapshot.hpp"
#include "Level.h"

#define _MAGIC_ 0x0101010

class Instruction;

class Packet
{
public:

    ~Packet() {};

    enum Type {

        String = 0xb16b00b5,
        IntVector = 0x42424242,
        Id = 0x12345678,
        Inst = 0x51515151,
        SSLPublicKey = 0x4ab2321a,
        Sound = 0x98765432,
        Instruct = 0x69696969,
        SerializedObj = 0x98765432,
        Snap = 0x13371337,
        L3v3l = 0x98467879
    };

    //object specific constructors
    Packet(const std::string &str);
    Packet(std::vector<int> &vec);
    Packet(Instruction &);
    Packet(SerializedObject &);
    Packet(Snapshot &);
    Packet(Level &);

    static std::vector<unsigned char>& stringToStream(char *buf, int const size)
    {
        std::vector<unsigned char>* stream = new std::vector<unsigned char>();

        for (int i=0; i < size; ++i)
        {
            stream->push_back(buf[i]);
        }
        return (*stream);
    }

    static void streamToString(std::vector<unsigned char>* stream, unsigned char* data)
    {
        for (unsigned int i=0; i < stream->size(); ++i)
        {
            data[i] = (*stream)[i];
        }
    }

    template <typename T>
    static Packet *pack(T &obj)
    {
        return (new Packet(obj));
    };

    static int extractSizeFromHeader(std::vector<unsigned char> &data)
    {
        unsigned int headerSize = Packet::getHeaderSize();
        if (data.size() <= headerSize)
            return (-1);

        unsigned int *r_magic = reinterpret_cast<unsigned int *>(&data[0]);
        Packet::Type *r_type = reinterpret_cast<Packet::Type *>(&data[sizeof(unsigned int)]);
        unsigned int *r_size = reinterpret_cast<unsigned int *>(&data[sizeof(unsigned int) * 2]);

        if (*r_magic != _MAGIC_ || *r_size + headerSize > data.size())
            return (-1);
        return (*r_size);
    }

    //build a bytestream from the packet
    std::vector<unsigned char>              *build();

    //reconstruct the packet from vector stream which will be consumed if succeeded
    static Packet                           *fromStream(std::vector<unsigned char> &data);

    //unpack the packet to get your object back
    template <typename T>
    T *unpack()
    {
        if (typeid(T) == typeid(std::string))
            return (reinterpret_cast<T *>(this->getString()));
        else if (typeid(T) == typeid(std::vector<int>))
            return (reinterpret_cast<T *>(this->getIntVector()));
        else if (typeid(T) == typeid(Instruction))
            return (reinterpret_cast<T *>(this->getInstruction()));
        else if (typeid(T) == typeid(SerializedObject))
            return (reinterpret_cast<T *>(this->getSerializedObject()));
        else if (typeid(T) == typeid(Snapshot))
            return (reinterpret_cast<T *>(this->getSnapshot()));
        else if (typeid(T) == typeid(Level))
            return (reinterpret_cast<T *>(this->getLevel()));
        return (NULL);
    };

    //just 3 * (sizeof(unsigned int))
    static unsigned int                     getHeaderSize();

    Type                                    getType() const;

    std::vector<unsigned char>              &getData();

protected:

    //properties
    Type _type;
    std::vector<unsigned char> _data;

    //constructor
    Packet();

    std::string                             *getString();
    std::vector<int>                        *getIntVector();
    Instruction                             *getInstruction();
    SerializedObject                        *getSerializedObject();
    Snapshot                                *getSnapshot();
    Level                                   *getLevel();
};

#endif //CPP_BABEL_PACKET_H
