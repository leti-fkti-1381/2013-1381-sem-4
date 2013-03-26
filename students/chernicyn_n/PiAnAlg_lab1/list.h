#ifndef LIST_H
#define LIST_H
#include <iostream>

namespace List
{

template <class TYPE>
class _node
{
public:
    _node();
//private:
    _node<TYPE>* _next;
    TYPE _data;
};

template <class TYPE>
class list
{
public:
    list();
    ~list();
    bool reset();
    bool next();
    void add(TYPE data);
    void print(int TAB);
    bool empty();
    bool check();
private:
    _node<TYPE>* _head;
    _node<TYPE>* _tail;
protected:
    _node<TYPE>* _curr;
};

}

#endif // LIST_H

/**
 *Реализация функций класса _node
 */

template <class TYPE>
List::_node<TYPE>::_node()
{
    _next=NULL;
}

/**
 *Реализация функций класса list
 */

template <class TYPE>
List::list<TYPE>::list()
{
    _head=NULL;
    _curr=NULL;
    _tail=NULL;
}

template <class TYPE>
List::list<TYPE>::~list()
{
    while(_head)
    {
        _curr=_head;
        _head=_head->_next;
        delete _curr;
    }
}

template <class TYPE>
bool List::list<TYPE>::reset()
{
    if (!_head)
        return false;
    _curr=_head;
    return true;
}

template <class TYPE>
bool List::list<TYPE>::next()
{
    if (!_curr || !_curr->_next)
        return false;
    _curr=_curr->_next;
    return true;
}

template <class TYPE>
void List::list<TYPE>::add(TYPE data)
{
    if (!_head)
    {
        _head=new List::_node<TYPE>;
        _head->_data=data;
        _curr=_tail=_head;
        return;
    }
    _tail->_next=new List::_node<TYPE>;
    _tail=_tail->_next;
    _tail->_data=data;
}

template <class TYPE>
void List::list<TYPE>::print(int TAB)
{
    List::_node<TYPE>* temp=_head;
    for(; temp; temp=temp->_next)
    {
        for (int i=0; i<TAB; i++)
            std::cout<<" ";
        std::cout<<temp->_data<<std::endl;
    }
}

template <class TYPE>
bool List::list<TYPE>::empty()
{
    return !_head;
}

template <class TYPE>
bool List::list<TYPE>::check()
{
    bool res=true;
    if (empty())
        return res;
    //TYPE temp;
    List::_node<TYPE>* temp1=_head;
    List::_node<TYPE>* temp2=temp1->_next;
    for(; temp1 && res; temp1=temp1->_next)
        for(; temp2 && res; temp2=temp2->_next)
            if (temp1->_data==temp2->_data)
            {
                std::cout<<"find="<<temp1->_data<<std::endl;
                res=false;
                return res;
            }
    return res;
}
