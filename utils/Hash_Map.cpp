#include "../Includes/Hash_Map.hpp"

Hash_Map::Hash_Map()
{
    this->head = NULL;
    this->tail = NULL;
}

Hash_Map::~Hash_Map()
{
    Hash_Map_Enter *current = this->head;
    Hash_Map_Enter *next;

    while (current != NULL)
    {
        next = current->next;
        delete current;
        current = next;
    }
    this->head = NULL;
    this->tail = NULL;
}

void Hash_Map::replace(std::string key, std::string value)
{
    Hash_Map_Enter *current = this->head;

    while (current != NULL)
    {
        if (current->key == key)
        {
            current->value = value;
            return;
        }
        current = current->next;
    }
}

void Hash_Map::insert(std::string key, std::string value, Type type)
{
    Hash_Map_Enter *new_enter = new Hash_Map_Enter();
    new_enter->key = key;
    new_enter->value = value;
    new_enter->type = type;
    new_enter->next = this->head;
    new_enter->prev = NULL;

    if (this->head == NULL)
    {
        this->head = new_enter;
        this->tail = new_enter;
    }
    else
    {
        this->head->prev = new_enter;
        this->head = new_enter;
    }
}

std::string Hash_Map::get(std::string key)
{
    Hash_Map_Enter *current = this->head;
    while (current != NULL)
    {
        if (current->key == key)
            return current->value;
        current = current->next;
    }
    return "";
}

std::string Hash_Map::get_key(std::string value)
{
    Hash_Map_Enter *current = this->head;
    while (current != NULL)
    {
        if (current->value == value)
            return current->key;
        current = current->next;
    }
    return "";
}

Type Hash_Map::get_type(std::string key)
{
    Hash_Map_Enter *current = this->head;
    while (current != NULL)
    {
        if (current->key == key)
            return current->type;
        current = current->next;
    }
    return T_INT;
}
