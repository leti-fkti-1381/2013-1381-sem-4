#include <iostream>
#include <string>
#include <fstream>
//#include "list.h"
#include "hashtable.h"

Hash::HashTable* load(Hash::HashTable* table, std::string filename)
{
    std::cout<<"Чтение файла "<<filename<<":"<<std::endl;
    std::ifstream file(filename.c_str());
    if (!file || !file.is_open())
    {
        std::cerr<<"ERROR! Invalid FILE!"<<std::endl;
        return NULL;
    }
    std::string data;
    if (!table)
        table=new Hash::HashTable;
    while (file>>data)
    {
        table->add(data);
        std::cout<<data<<"\t";
        //mass->add(data);
    }
    std::cout<<"[OK]"<<std::endl;
    file.close();
    return table;
}

int main()
{
    Hash::HashTable* table;
    std::cout<<"Построение хэш-таблицы для множеств..."<<std::endl;
    table=load(table,"mnogestvo_A.txt");
    if (!table)
        goto err;
    //table->printTable();
    table=load(table,"mnogestvo_B.txt");
    if (!table)
        goto err;
    std::cout<<"[OK]"<<std::endl;
    table->printTable();
    std::cout<<"Проверка коллизий:"<<std::endl;
    if (table->check())
    {
        std::cout<<"Множества не пересекаются!"<<std::endl;
        return 1;
    }
    std::cout<<"Множества пересекаются!"<<std::endl;
    return 0;
err:
    std::cerr<<"ERROR! Ошибка множества!"<<std::endl;
    return -1;
}
