//
// Created by rivatn on 12/22/15.
//

#ifndef CPP_R_TYPECPY2_INSTRUCTION_H
#define CPP_R_TYPECPY2_INSTRUCTION_H

#include <string>
#include <vector>
#include <algorithm>

class Instruction
{
public:
    enum TypeName
    {
        OK,
        KO,
        CONNEXION,
        DECONNEXION,
        GETALLUSERNAMES,
        START_GAME,
        END_GAME,
        GETALLROOMNAMES,
        GETALLUSERSINROOM,
        CREATE_ROOM,
        JOIN_ROOM,
        LEAVE_ROOM
    };

    Instruction(TypeName type);
    Instruction(std::string, TypeName);
    Instruction(const std::vector<std::string> &, TypeName);

    ~Instruction();

    std::vector<std::string> getListNames() const;
    TypeName getInstruct() const;
    void eraseNames();
    void setInstruct(TypeName type);
    bool addName(std::string);
    unsigned int getNb() const;
    const std::string &operator[](unsigned int pos) const;

private:
    std::vector<std::string>    listNames;
    std::string                 empty;
    TypeName                    instruction;
    unsigned int                nb;
};


#endif //CPP_R_TYPECPY2_INSTRUCTION_H
