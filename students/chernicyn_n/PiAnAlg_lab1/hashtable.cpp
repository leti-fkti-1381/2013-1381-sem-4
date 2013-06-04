#include "hashtable.h"

Hash::HashTable::HashTable()
{
    _table=new elementTable[Hash::M];
    for (unsigned int i=0; i<Hash::M; i++)
    {
        _table[i].data=new List::list<std::string>;
        _table[i].hashCode=i;
    }
}

Hash::HashTable::~HashTable()
{
    delete _table;
}

int Hash::HashTable::hashCode(std::string data)
{
    int res=0;
    for(unsigned int i=0; i<data.size(); i++)
        res+=data[i];
    res=res % Hash::M;
    return res;
}

void Hash::HashTable::add(std::string data)
{
    //std::cout<<hashCode(data)<<"="<<data<<std::endl;
    //std::cout<<_table[hashCode(data)].data<<std::endl;
    _table[hashCode(data)].data->add(data);
}

void Hash::HashTable::printTable()
{
    std::cout<<"Хэш-таблица:"<<std::endl;
    for (unsigned int i=0; i<Hash::M; i++)
        if (!_table[i].data->empty())
        {
            std::cout<<_table[i].hashCode<<":"<<std::endl;
            _table[i].data->print(4);
        }
}

bool Hash::HashTable::check()
{
    bool res=true;
    std::cout<<"Поиск одинаковых элементов в коллизиях:"<<std::endl;
    for (unsigned int i=0; i<Hash::M && res; i++)
        res=_table[i].data->check();
    std::cout<<"[OK]"<<std::endl;
    return res;
}
