#include "LinkedList.h"


LinkedList::LinkedList()
{
    head = nullptr;
    tail = nullptr;
    size = 0;
    //ctor
}

LinkedList::~LinkedList()
{
    //dtor
}

LinkedList::LinkedList(const LinkedList& other)
{
    //copy ctor
}

LinkedList& LinkedList::operator=(const LinkedList& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
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
    ComponentNode* newComponentPtr = new ComponetNode<T>;
    newComponentPtr->component = T(component);
    newComponentPtr->next = head;
    head = newComponentPtr;

    size++;

}

template <typename T>
void LinkedList<T>::addToBack(const T& component)
{
    ComponentNode *newComponentPtr = new ComponetNode<T>;
    newComponentPtr->component = T(component);
    newComponentPtr->next = nullptr;

    tail->next = newComponentPtr;
    tail = newComponentPtr;

    size++;
}

template <typename T>
void LinkedList<T>::removeNode(ComponentNode<T>*& target)
{
    ComponentNode* currPtr = head;
    ComponentNode* prevPtr = nullptr;

    if(target == head)                   // if the course we are dropping is the head
    {
        head = head->next;            // set head pointer to the next pointer
        delete target;                              // delete the course to be dropped
        target = nullptr;

        size--;
        //cout<<"1st Ship Removed"<<endl<<endl;
    }
    else
    {
        while(currPtr!=NULL)                                // exit loop if we reach the end
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
                break
            }
            prevPtr = currPtr;
            currPtr = currPtr->next;
        }
    }
}

template <typename T>
void LinkedList<T>::deleteList()
{
    ComponentPtr currPtr = head;
    while(currPtr != nullptr)
    {
        //cout<<"Count is: "<<x<<endl;
        removeShip(currPtr);        currPtr = head;

    }
    head = nullptr;
    tail = nullptr;
}
