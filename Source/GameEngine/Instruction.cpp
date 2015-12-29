//
// Created by rivatn on 12/22/15.
//

#include "Instruction.h"

Instruction::Instruction(std::string string, Instruction::TypeName name)
{
    this->listNames.push_back(string);
    this->instruction = name;
}

Instruction::Instruction(const std::vector<std::string> &vector, Instruction::TypeName name)
{
    for (std::vector<std::string>::const_iterator it = vector.begin(); it != vector.end(); it++)
        this->listNames.push_back(*it);
    this->instruction = name;
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
    return static_cast<unsigned int>(this->listNames.size());
}

const std::string &
Instruction::operator[](unsigned int pos) const {

    if (pos >= this->listNames.size())
        return (this->empty);
    return (this->listNames[pos]);
}

Instruction::Instruction(TypeName type) : instruction(type) {

}

void Instruction::setInstruct(TypeName type) {
    this->instruction = type;
}

void Instruction::eraseNames() {

    this->listNames.clear();
}
