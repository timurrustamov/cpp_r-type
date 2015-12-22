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
        CONNEXION,
        DECONNEXION,
        START_GAME,
        END_GAME
    };


    Instruction(std::string, TypeName);
    Instruction(std::vector<std::string>, TypeName);

    ~Instruction();

    std::vector<std::string> getListNames() const;
    TypeName getInstruct() const;
    bool addName(std::string);
    unsigned int getNb() const;

private:
    std::vector<std::string>    listNames;
    TypeName                    instruction;
    unsigned int                nb;
};


#endif //CPP_R_TYPECPY2_INSTRUCTION_H
