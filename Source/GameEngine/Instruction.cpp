//
// Created by rivatn on 12/22/15.
//

#include "Instruction.h"

Instruction::Instruction(std::string string, Instruction::TypeName name)
{
    this->listNames.push_back(string);
    this->instruction = name;
    this->nb = 1;
}

Instruction::Instruction(std::vector<std::string> vector, Instruction::TypeName name)
{
    this->listNames.reserve(vector.size());
    this->listNames.resize(vector.size());
    for (std::vector<std::string>::iterator it = vector.begin(); it != vector.end(); it++)
        this->listNames.push_back(*it);
    this->instruction = name;
    this->nb = static_cast<unsigned int>(this->listNames.size());
}

Instruction::~Instruction()
{

}

std::vector<std::string> Instruction::getListNames() const
{
    return this->listNames;
}

Instruction::TypeName Instruction::getInstruct() const
{
    return this->instruction;
}

bool Instruction::addName(std::string str)
{
    if (std::find(this->listNames.begin(), this->listNames.end(), str) != this->listNames.end())
        return false;
    this->listNames.push_back(str);
    return true;
}

unsigned int Instruction::getNb() const
{
    return this->nb;
}
