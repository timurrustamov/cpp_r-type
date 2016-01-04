#include "Packet.h"
#include <iostream>

//real constructor
Packet::Packet()
{

}

//pbject specific constructors
Packet::Packet(const std::string &str) : _type(Packet::String)
{
    for (unsigned int i = 0; i < str.size(); i++)
        this->_data.push_back(static_cast<unsigned char>(str.at(i)));
}

Packet::Packet(std::vector<int> &vec) : _type(Packet::IntVector)
{
    unsigned char *ptr;

    for (unsigned int i = 0; i < vec.size(); i++)
    {
        ptr = reinterpret_cast<unsigned char *>(&vec[i]);
        for (unsigned int j = 0; j < sizeof(int); j++)
            this->_data.push_back(ptr[j]);
    }
}

Packet::Packet(SerializedObject &object) : _type(Packet::SerializedObj) {

    Packet *tmp;
    std::vector<unsigned char> *_data;

    this->_data = object.toBinaryString();
    tmp = Packet::pack(object.getConfig());
    _data = tmp->build();
    this->_data.insert(this->_data.end(), _data->begin(), _data->end());
}

Packet::Packet(Snapshot &snapshot) : _type(Packet::Snap) {

    int x = snapshot.size.getX();
    int y = snapshot.size.getY();
    size_t objnb = snapshot.objects.size();
    Packet *p;
    std::vector<unsigned char> *tmpvec;

    unsigned char *tmpx = reinterpret_cast<unsigned char *>(&x);
    unsigned char *tmpy = reinterpret_cast<unsigned char *>(&y);
    unsigned char *tmpobjnb = reinterpret_cast<unsigned char *>(&objnb);

    for (unsigned int i = 0; i < sizeof(x); i++)
        this->_data.push_back(tmpx[i]);
    for (unsigned int i = 0; i < sizeof(y); i++)
        this->_data.push_back(tmpy[i]);
    for (unsigned int i = 0; i < sizeof(objnb); i++)
        this->_data.push_back(tmpobjnb[i]);

    for (std::map<unsigned int, SerializedObject *>::iterator it = snapshot.objects.begin(); it != snapshot.objects.end(); it++)
    {
        p = Packet::pack(*(it->second));
        tmpvec = p->build();
        this->_data.insert(this->_data.end(), tmpvec->begin(), tmpvec->end());
        delete tmpvec;
        delete p;
    }
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
}

Packet::Packet(Level &level) : _type(Packet::L3v3l) {

    int scrollSpeed = level.getScrollSpeed();
    unsigned int size = level.getSize();
    unsigned char *scrollSpeedC = reinterpret_cast<unsigned char *>(&scrollSpeed);
    unsigned char *sizeC = reinterpret_cast<unsigned char *>(&size);
    std::vector<unsigned char> *builds;

    Packet *p;
    for (unsigned int i = 0; i < sizeof(int); i++)
        this->_data.push_back(sizeC[i]);
    for (unsigned int i = 0; i < sizeof(unsigned int); i++)
        this->_data.push_back(scrollSpeedC[i]);

    p = Packet::pack(level.getTitle());
    builds = p->build();
    this->_data.insert(this->_data.end(), builds->begin(), builds->end());
    delete p;
    delete builds;
    p = Packet::pack(level.getBgtPath());
    builds = p->build();
    this->_data.insert(this->_data.end(), builds->begin(), builds->end());
    delete p;
    delete builds;
    p = Packet::pack(level.getBgmPath());
    builds = p->build();
    this->_data.insert(this->_data.end(), builds->begin(), builds->end());
    delete p;
    delete builds;
    p = Packet::pack(level.getScenario());
    builds = p->build();
    this->_data.insert(this->_data.end(), builds->begin(), builds->end());
    delete p;
    delete builds;
}

//static
unsigned int
Packet::getHeaderSize()
{
    static unsigned int size = 0;

    if (size == 0)
        size = sizeof(unsigned int) * 3;
    return (size);
}

//get packet from bytestream (bytestream is then consumed)
Packet *
Packet::fromStream(std::vector<unsigned char> &data)
{
    unsigned int headerSize = Packet::getHeaderSize();
    if (data.size() <= headerSize) {
        return (NULL);
    }
    unsigned int *r_magic = reinterpret_cast<unsigned int *>(&data[0]);
    Packet::Type *r_type = reinterpret_cast<Packet::Type *>(&data[sizeof(unsigned int)]);
    unsigned int *r_size = reinterpret_cast<unsigned int *>(&data[sizeof(unsigned int) * 2]);

    if (*r_magic != _MAGIC_ || *r_size + headerSize > data.size())
    {
        std::cout << (int)(*r_size) << std::cout;
        if (*r_magic != _MAGIC_)
            std::cout << "magic" << std::endl;
        if (*r_size + headerSize < data.size())
            std::cout << "size" << std::endl;
        return (NULL);
    }
    Packet *newPacket = new Packet;
    std::vector<unsigned char> new_data;
    newPacket->_type = *r_type;
    for (unsigned int i = 0; i < *r_size && i < data.size(); i++)
        newPacket->_data.push_back(data[i + headerSize]);
    //consume flux
    data.erase(data.begin(), data.begin() + headerSize + *r_size);

    return (newPacket);
}

//get bytestream from packet
std::vector<unsigned char> *
Packet::build()
{
    unsigned char *magic_ptr;
    unsigned char *size_ptr;
    unsigned char *type_ptr;

    unsigned int magic = _MAGIC_;
    unsigned int length = static_cast<unsigned int>(this->_data.size());

    magic_ptr = reinterpret_cast<unsigned char *>(&magic);
    size_ptr = reinterpret_cast<unsigned char *>(&length);
    type_ptr = reinterpret_cast<unsigned char *>(&this->_type);

    //allocate
    std::vector<unsigned char> *build = new std::vector<unsigned char>(Packet::getHeaderSize());
    for (unsigned int i = 0; i < 4; i++) {

        //magic goes first
        (*build)[i] = magic_ptr[i];
        //type
        (*build)[i + (sizeof(unsigned int))] = type_ptr[i];
        //size!
        (*build)[i + (sizeof(unsigned int) * 2)] = size_ptr[i];
    }
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

SerializedObject *
Packet::getSerializedObject() {

    SerializedObject *result = NULL;
    std::string *tmp;
    Packet *p;

    if (this->_type == Packet::SerializedObj)
    {
        result = new SerializedObject(this->_data);
        if ((p = Packet::fromStream(this->_data)) != NULL)
        {
            if ((tmp = p->unpack<std::string>()) != NULL) {
                result->setConfig(*tmp);
                delete tmp;
            }
            delete p;
        }
    }
    return (result);
}

Snapshot *
Packet::getSnapshot() {

    Snapshot *result = NULL;
    SerializedObject *objTmp;
    Packet *p;
    size_t objNb;

    if (this->_type == Packet::Snap)
    {
        result = new Snapshot();
        result->size.setX(*(reinterpret_cast<int *>(&this->_data[0])));
        result->size.setY(*(reinterpret_cast<int *>(&this->_data[sizeof(int)])));

        objNb = *(reinterpret_cast<size_t *>(&this->_data[sizeof(int) + sizeof(int)]));
        this->_data.erase(this->_data.begin(), this->_data.begin() + (sizeof(int) * 2 + sizeof(size_t)));
        for (size_t i = 0; i < objNb; i++)
        {
            if ((p = Packet::fromStream(this->_data)) != NULL)
            {
                if ((objTmp = p->unpack<SerializedObject>()) != NULL)
                    result->objects[objTmp->attr.id] = objTmp;
                delete p;
            }
        }
    }
    return (result);
}


Level *
Packet::getLevel() {

    int scrollSpeed;
    unsigned int size;
    std::string *title = NULL;
    std::string *bgtPath = NULL;
    std::string *bgmPath = NULL;
    std::string *scenario = NULL;
    Packet *p;
    Level *level;

    if (this->_type == Packet::L3v3l) {
        size = *reinterpret_cast<unsigned int *>(&(this->_data[0]));
        scrollSpeed = *reinterpret_cast<int *>(&(this->_data[sizeof(unsigned int)]));
        this->_data.erase(this->_data.begin(), this->_data.begin() + sizeof(unsigned int) + sizeof(int));

        if ((p = Packet::fromStream(this->_data)) != NULL)
        {
            title = p->unpack<std::string>();
            delete p;
        }
        if ((p = Packet::fromStream(this->_data)) != NULL)
        {
            bgtPath = p->unpack<std::string>();
            delete p;
        }
        if ((p = Packet::fromStream(this->_data)) != NULL)
        {
            bgmPath = p->unpack<std::string>();
            delete p;
        }
        if ((p = Packet::fromStream(this->_data)) != NULL)
        {
            scenario = p->unpack<std::string>();
            delete p;
        }

        if (title != NULL && bgmPath != NULL && bgmPath != NULL && scenario != NULL)
            level = new Level(*title, *bgtPath, *bgmPath, *scenario, size, scrollSpeed);
        if (title != NULL)
            delete title;
        if (bgmPath != NULL)
            delete bgmPath;
        if (bgtPath != NULL)
            delete bgtPath;
        if (scenario != NULL)
            delete scenario;
    }
    return (level);
}
