
#include "Sequence.h"
#include <optional>
#include <string>
#include <sstream>
#include <stdexcept>

// !!!Do not use the following line!!!.
//using namespace std;
// This is a horrible practice and leads to invisible side effects.
// Instead, use the scope resolution operator :: to prefix std to the method.
// ex. std::cout

template <class T>
Sequence<T>::Sequence ()
{
    head = NULL;
    size = 0;
}

template <class T>
Sequence<T>::~Sequence ()
{
    reclaimAllNodes(head);
}

template <class T>
void Sequence<T>::clear ()
{
    reclaimAllNodes(head);
    head = NULL;
    size = 0;
}

template <class T>
void Sequence<T>::reclaimAllNodes (NodeRecord*& initialP)
{
    if (initialP != NULL) {
        reclaimAllNodes(initialP->next);
        delete (initialP);
    }
}


template <class T>
void Sequence<T>::transferFrom(Sequence& source)
{
    std::optional<T> temp;
    clear(); //clears self
    for (int i = 0; i < source.length(); i++)//traverses source
    {
        temp = source.entry(i);
        if(temp != std::nullopt) {
            add(temp.value(), length());//adds source elements to self
        }
    }
    source.clear();//clears source
}

template <class T>
Sequence<T>& Sequence<T>::operator=(Sequence const& rhs) = default;


template<class T>
void Sequence<T>::add(T &x, int pos) {
    //Error handling for invalid positions
    if (pos < 0 || pos > size) {
        throw std::invalid_argument("Error: pos is out of scope");
    }

    //add NodeRecord to the heap so variable can live on out of scope
    auto newElem = new NodeRecord;

    //set the value to x
    newElem->value=x;

    //find the values that are supposed to be behind and ahead in the linkedList
    NodeRecord* prevElemPointer = getElementAt(--pos);
    NodeRecord* nextElemPointer = getElementAt(++pos);

    if (pos == 0) {
        //make the head point to x's address
        head = newElem;
    } else {
        prevElemPointer->next = newElem;
    }

    //Make the new node point to the variable in front
    newElem->next = nextElemPointer;
    size++;
}

template<class T>
void Sequence<T>::remove(T &x, int pos) {
    /*General Steps
     *  Make the node behind x point where x.next is pointing
     *  Delete ts node from memory
     */
    //find the element before pos and make it point to the element x is pointing tp
    // auto prevElemPointer = getElementAt(--pos);
    // prevElemPointer->next = x.next;
    // //delete x
    // x = getElementAt(pos);
}

template<class T>
std::optional<T> Sequence<T>::entry(int pos)  {
    NodeRecord* currentValue = head;

    if (pos >= size) {
        return std::nullopt;
    }
    else if (pos == 0) {
        return currentValue->value;
    }

    /*for (int i = 0; i <= pos; i++):
     *  currentValue = currentValue ->next
     */
    else {
        for (int i = 0; i < pos; i++) {
            currentValue = currentValue->next;
        }
        return currentValue->value;
    }

}

template<class T>
Sequence<T>::NodeRecord* Sequence<T>::getElementAt(int pos)  {
    NodeRecord* currentValue = head;

    if (pos >= size) {
        return nullptr;
    }
    else if (pos == 0) {
        return currentValue;
    }

    /*for (int i = 0; i <= pos; i++):
     *  currentValue = currentValue ->next
     */
    else {
        for (int i = 0; i < pos; i++) {
            currentValue = currentValue->next;
        }
        return currentValue;
    }

}

template<class T>
int Sequence<T>::length() {
    return size;
}

template<class T>
std::string Sequence<T>::outputSequence() {
    std::stringstream ss;

    //Use insertion operator (<<) to build the string.
    return ss.str();

}

