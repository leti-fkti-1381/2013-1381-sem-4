#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include "list.h"

namespace Hash
{
const unsigned int M=256;

struct elementTable
{
    int hashCode;
    List::list<std::string>* data;
};

class HashTable
{
public:
    HashTable();
    ~HashTable();
    int hashCode(std::string data);
    void add(std::string data);
    void printTable();
    bool check();
private:
    elementTable* _table;
};

}

#endif // HASHTABLE_H


