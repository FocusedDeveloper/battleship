#ifndef NODETYPE_H
#define NODETYPE_H


template <typename T>
struct ComponentNode
{
    T component;
    ComponentNode<T> *next;
    //ComponentNode* next;
};

#endif // NODETYPE_H
