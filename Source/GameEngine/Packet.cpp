#include "Packet.h"
#include <iostream>

//real constructor
Packet::Packet()
{
    this->_encrypted = false;
}

//pbject specific constructors
Packet::Packet(std::string &str) : _type(Packet::String)
{
    for (unsigned int i = 0; i < str.size(); i++)
        this->_data.push_back(static_cast<unsigned char>(str[i]));
    this->_encrypted = false;
}

Packet::Packet(std::vector<int> &vec) : _type(Packet::IntVector)
{
    unsigned char *ptr;

    for (unsigned int i = 0; i < vec.size(); i++)
    {
        ptr = reinterpret_cast<unsigned char *>(vec[i]);
        for (unsigned int j = 0; j < sizeof(int); j++)
            this->_data.push_back(*ptr);
    }
    this->_encrypted = false;
}

Packet::Packet(Rsa &rsa) : _type(Packet::SSLPublicKey)
{
    this->_data = rsa.getPublicKey();
    this->_encrypted = false;
}

Packet::Packet(Instruction &instr) : _type(Packet::Instruct)
{
    Instruction::TypeName typeName = instr.getInstruct();
    std::vector<std::string> data = instr.getListNames();
    unsigned int elemNo = instr.getNb();
    unsigned char *ptr = reinterpret_cast<unsigned char *>(&typeName);

    for (unsigned int i = 0; i < sizeof(Instruction::TypeName); i++)
        this->_data.push_back(ptr[i]);
    ptr = reinterpret_cast<unsigned char *>(&elemNo);
    for (unsigned int i = 0; i < sizeof(unsigned int); i++)
        this->_data.push_back(ptr[i]);
    for (std::vector<std::string>::iterator it = data.begin(); it != data.end(); it++)
    {
        Packet *p = Packet::pack(*it);
        std::vector<unsigned char> *build = p->build();
        this->_data.insert(this->_data.end(), build->begin(), build->end());
        delete p;
        delete build;
        //std::cout << this->_data.size() << std::endl;
    }
    this->_encrypted = false;
}

//static
unsigned int
Packet::getHeaderSize()
{
    static unsigned int size = 0;

    if (size == 0)
        size = sizeof(unsigned int) * 4;
    return (size);
}

//get packet from bytestream (bytestream is then consumed)
Packet *
Packet::fromStream(std::vector<unsigned char> &data, Rsa* rsa)
{
    unsigned int headerSize = Packet::getHeaderSize();
    if (data.size() <= headerSize)
        return (NULL);
    unsigned int *r_magic = reinterpret_cast<unsigned int *>(&data[0]);
    Packet::Type *r_type = reinterpret_cast<Packet::Type *>(&data[sizeof(unsigned int)]);
    unsigned int *r_size = reinterpret_cast<unsigned int *>(&data[sizeof(unsigned int) * 2]);
    unsigned int *r_encrypted = reinterpret_cast<unsigned int *>(&data[sizeof(unsigned int) * 3]);

    if (*r_magic != _MAGIC_ || *r_size + headerSize > data.size() || !(*r_encrypted == 0 || *r_encrypted == 1))
    {
        std::cout << (int)(*r_size) << std::cout;
        if (*r_magic != _MAGIC_)
            std::cout << "magic" << std::endl;
        if (*r_size + headerSize < data.size())
            std::cout << "size" << std::endl;
        if (!(*r_encrypted == 0 || *r_encrypted == 1))
            std::cout << "encr" << std::endl;
        return (NULL);
    }
    Packet *newPacket = new Packet;
    std::vector<unsigned char> new_data;
    newPacket->_type = *r_type;
    newPacket->_encrypted = (*r_encrypted != 0);
    for (unsigned int i = 0; i < *r_size; i++)
        newPacket->_data.push_back(data[i + headerSize]);
    //consume flux
    data.erase(data.begin(), data.begin() + headerSize + *r_size);
    if (rsa != NULL && newPacket->_encrypted)
    {
        newPacket->_data = rsa->decrypt(newPacket->_data);
        newPacket->_encrypted = false;
    }

    return (newPacket);
}

//get bytestream from packet
std::vector<unsigned char> *
Packet::build(Rsa *rsa)
{
    unsigned char *magic_ptr;
    unsigned char *size_ptr;
    unsigned char *type_ptr;
    unsigned char *encryption_ptr;

    unsigned int magic = _MAGIC_;
    unsigned int length = static_cast<unsigned int>(this->_data.size());
    unsigned int encryption = (rsa == NULL ? 0 : 1);

    magic_ptr = reinterpret_cast<unsigned char *>(&magic);
    size_ptr = reinterpret_cast<unsigned char *>(&length);
    type_ptr = reinterpret_cast<unsigned char *>(&this->_type);
    encryption_ptr = reinterpret_cast<unsigned char *>(&encryption);

    //allocate
    std::vector<unsigned char> *build = new std::vector<unsigned char>(Packet::getHeaderSize());
    for (unsigned int i = 0; i < 4; i++) {

        //magic goes first
        (*build)[i] = magic_ptr[i];
        //type
        (*build)[i + sizeof(unsigned int) * 1] = type_ptr[i];
        //size!
        (*build)[i + sizeof(unsigned int) * 2] = size_ptr[i];
        //encryption
        (*build)[i + sizeof(unsigned int) * 3] = encryption_ptr[i];
    }
    if (rsa != NULL)
    {
        std::vector<unsigned char> crypt = rsa->encrypt(this->_data);
        build->insert(build->end(), crypt.begin(), crypt.end());
        //rewrite size
        length = crypt.size();
        for (unsigned int i = 0; i < sizeof(unsigned int); i++)
            (*build)[i + sizeof(unsigned int) * 2] = size_ptr[i];
    }
    else
        build->insert(build->end(), this->_data.begin(), this->_data.end());
    return (build);
}

std::vector<unsigned char>&
Packet::getData()
{
    return (this->_data);
}

Packet::Type
Packet::getType() const
{
    return (_type);
}

bool
Packet::isEncrypted() const
{
    return (this->_encrypted);
}

std::string *
Packet::getString()
{
    std::string *tmp = NULL;

    if (this->_type == Packet::String)
    {

        tmp = new std::string;
        for (unsigned int i = 0; i < this->_data.size(); i++)
            tmp->push_back(static_cast<char>(this->_data[i]));
    }
    return (tmp);
}

std::vector<int> *
Packet::getIntVector()
{
    std::vector<int> *tmp = NULL;
    int *ptr;

    if (this->_type == Packet::IntVector && this->_data.size() % sizeof(int) == 0)
    {
        tmp = new std::vector<int>();
        for (unsigned int i = 0; i < this->_data.size(); i += sizeof(int))
        {
            ptr = reinterpret_cast<int *>(&(this->_data[i]));
            tmp->push_back(*ptr);
        }
    }
    return (tmp);
}

Rsa *
Packet::getRsa()
{
    Rsa *result = NULL;

    if (this->_type == Packet::SSLPublicKey)
    {
        try
        {
            result = new Rsa(this->_data);
        }
        catch (std::exception &e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
    return (result);
}

Instruction *
Packet::getInstruction() {

    Instruction *result = NULL;

    Instruction::TypeName typeName;
    std::vector<std::string> vectorTmp;
    std::string *stringPtr;
    Packet *p;

    unsigned int elemNo = 0;
    if (this->_type == Packet::Instruct)
    {
        typeName = *(reinterpret_cast<Instruction::TypeName *>(&this->_data[0]));
        elemNo = *(reinterpret_cast<unsigned int *>(&this->_data[sizeof(Instruction::TypeName)]));
        //consume this flux
        this->_data.erase(this->_data.begin(), this->_data.begin() + (sizeof(Instruction::TypeName) + sizeof(unsigned int)));

        for (unsigned int i = 0; i < elemNo; i++) {
            if ((p = Packet::fromStream(this->_data)) != NULL &&
                p->getType() == Packet::String) {
                if ((stringPtr = p->unpack<std::string>()) != NULL) {
                    vectorTmp.push_back(*stringPtr);
                    delete stringPtr;
                }
                delete p;
            }
        }

        result = new Instruction(vectorTmp, typeName);
    }
    return (result);
}
