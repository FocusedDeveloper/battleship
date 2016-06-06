#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "NodeType.h"


template <typename T>
class ListIterator
{
    public:



        ListIterator();
        //POST: currPtr = nullptr;

        ListIterator( ComponentNode<T> *ptr);
        //POST: currPtr = ptr;

        T operator*();
        // Returns component of currPtr;

        ListIterator<T> operator++();
        // Post: currPtr = next node

        bool operator==(const ListIterator<T>& right) const;
        // returns true if this iterator == the right iterator

        bool operator!=(const ListIterator<T>& right) const;
        // returns true if this iterator does not equal the right iterator

    private:
        ComponentNode<T> currPtr;
};

//template <typename T>
//struct ComponentNode
//{
//    T component;
//    ComponentNode<T> *next;
//    //ComponentNode* next;
//};

template <typename T>
class LinkedList
{
    public:

        LinkedList();
        LinkedList(const T&);
        ~LinkedList();
        LinkedList(const LinkedList& other);
        const LinkedList<T>& operator=(const LinkedList& other);

        void addToFront(const T& );
        void addToBack(const T& );
        void removeComponent(const T& );
        // Function deletes the first occurrence of item from the list.
        // Postcondition: If item is found, it is removed from list
                        // size decremented

        void printList();

        void removeNode(ComponentNode<T> *&  );
        void deleteList();

    private:

        ComponentNode<T> *head;
        ComponentNode<T> *tail;
        int size;

        void initList(const T& );

};



template <typename T>
LinkedList<T>::LinkedList()
{
    head = nullptr;
    tail = nullptr;
    size = 0;
    //ctor
}

template <typename T>
LinkedList<T>::LinkedList(const T& component)
{
    head = nullptr;
    tail = nullptr;
    size = 0;

    addToFront(component);
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    deleteList();
    //dtor
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList& other)
{
    head = nullptr;
    tail = nullptr;
    size = 0;

    ComponentNode<T> *currPtr = other.head;

    while(currPtr != nullptr)
    {
        addToFront(currPtr->component);
        currPtr = currPtr->next;
    }


    //copy ctor
}

template <typename T>
const LinkedList<T>& LinkedList<T>::operator=(const LinkedList& rhs)
{
    if (this == &rhs)
        return *this; // handle self assignment
    else
    {
        if(head != nullptr)
        {
            deleteList();
        }
        ComponentNode<T> *currPtr = rhs.head;
        while(currPtr != nullptr)
        {
            addToFront(currPtr->component);
            currPtr = currPtr->next;
        }
    }
    //assignment operator
    return *this;
}

template <typename T>
void LinkedList<T>::initList(const T& component )
{
    if(head != nullptr)
    {
        deleteList();
    }
    addToFront(component);

    head->next = nullptr;
    tail = head;
}

template <typename T>
void LinkedList<T>::addToFront(const T& component)
{
    ComponentNode<T> *newComponentPtr = new ComponentNode<T>;
    newComponentPtr->component = T(component);
    newComponentPtr->next = head;

    head = newComponentPtr;

    if(tail == nullptr)
    {
        tail = head;
    }

    size++;

}

template <typename T>
void LinkedList<T>::addToBack(const T& component)
{
    ComponentNode<T> *newComponentPtr = new ComponentNode<T>;
    newComponentPtr->component = T(component);
    newComponentPtr->next = nullptr;

    tail->next = newComponentPtr;
    tail = newComponentPtr;

    if(head == nullptr)
    {
        head = tail;
    }

    size++;
}

template <typename T>
void LinkedList<T>::removeNode(ComponentNode<T>*& target)
{
    ComponentNode<T> *currPtr = head;
    ComponentNode<T> *prevPtr = nullptr;
    bool found = false;

    if(target == head)                   // if the course we are dropping is the head
    {
        if(target == tail)
            tail = prevPtr;

        head = head->next;            // set head pointer to the next pointer
        delete target;                              // delete the course to be dropped
        target = nullptr;

        size--;
        //cout<<"1st Ship Removed"<<endl<<endl;
    }
    else
    {
        while(currPtr!=nullptr && !found)                                // exit loop if we reach the end
        {
            if(target == currPtr)                   // Once the current pointer is pointing to the ship to be deleted...
            {
                if(currPtr == tail)
                    tail = prevPtr;

                prevPtr->next = target->next;       // previous pointer skips over the target ship, to the next proceeding in the list
                delete target;                      // delete the dead ship
                target = nullptr;
                //cout<<"Ship Removed"<<endl<<endl;

                size--;
                found = true;
            }
            prevPtr = currPtr;
            currPtr = currPtr->next;
        }
    }
}

template <typename T>
void LinkedList<T>::deleteList()
{
    ComponentNode<T> *currPtr = head;
    while(currPtr != nullptr)
    {
        //cout<<"Count is: "<<x<<endl;
        removeNode(currPtr);
        currPtr = head;

    }
    head = nullptr;
    tail = nullptr;
}

template <typename T>
void LinkedList<T>::removeComponent(const T& item)
{
    ComponentNode<T> *currPtr = head;
    bool found = false;

    if(head == nullptr)             // if the list is empty
    {
        std::cout << "The list is empty" <<std::endl;
    }
    else if(head->component == item)                    // if the item is the first node...
    {
        removeNode(currPtr);
        found = true;
        std::cout<<"Item removed from list"<<std::endl;
    }
    else                                                // if the list is not empty...
    {
        while(found == false && currPtr->next != nullptr)     // search the list until the item is found
        {
            currPtr = currPtr->next;                    // advance to the next pointer

            if(currPtr->component == item)              // Once found
            {
                removeNode(currPtr);                    // delete from list
                found = true;
                std::cout<<"Item removed from list"<<std::endl;
            }
        }
        //std::cout<<"exit while"<<std::endl;
    }
    if(!found)                                          // if the item is not in the list, notify the user
    {
        std::cout<<"Item: "<<item<<" was not found in list"<<std::endl;
    }
}

template <typename T>
void LinkedList<T>::printList()
{
    ComponentNode<T> * currPtr = head;
    if(currPtr == nullptr)
        std::cout<<" The list is empty"<<std::endl;
    else{
        while(currPtr != nullptr)
        {
            std::cout<< currPtr->component <<std::endl;
            currPtr = currPtr->next;
        }
    }

}

#endif // LINKEDLIST_H
