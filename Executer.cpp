#include "Includes/Executer.hpp"

Excecuter::Excecuter(Hash_Map *instructions)
{
    this->instructions = instructions;
}

void Excecuter::execute()
{
    Hash_Map_Enter *current = this->instructions->head;
    while (current != NULL)
    {
        if (current->key == FUNC_PRINT)
        {
            std::cout << current->value << std::endl;
        }
        current = current->next;
    }
}

