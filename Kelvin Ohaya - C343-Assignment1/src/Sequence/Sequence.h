# ifndef C343_ASSIGNMENT1EXAMPLE_SEQUENCE_H
#define C343_ASSIGNMENT1EXAMPLE_SEQUENCE_H


#include <string>
#include <optional>
#include <sstream>
#include <stdexcept>

/**
 * @tparam T Generic type
 */
template <class T>
class Sequence {

private:

    /**
     * Description: NodeRecord is used as the underlining Data Structure to hold
     * the values and pointers
     */
    class NodeRecord {
    public:
        /**
         * Description: Holds a single instance of a value for this node in the sequence.
         */
        T value;

        /**
         * Description: Points at the next NodeRecord in the sequence
         */
        NodeRecord* next;

        /**
         * Description: Default Constructor
         */
        NodeRecord() = default;
    };

    /**
     * Description: First value in sequence
     */
    NodeRecord* head;

    /**
     * Description: size of sequence
     */
    int size;

    /**
     * Description: Reclaims all space in the heap from the allocated for p and any sequential NodeRecord it points to.
     * @param p A NodeRecord value
     */
    void reclaimAllNodes (NodeRecord*& p);

public:

    /**
     * Description: Constructor that initializes all attributes of this class.
     */
    Sequence ();

    /**
     * Description: Deconstructor that reclaims all space allocated to the heap.
     */
    ~Sequence ();

    /**
     * Description: Clears all of the elements in the data structure.
     */
    void clear ();

    /**
     * Description: Adds a node to sequence
     * @param x value to place in node field
     * @param pos index in sequence representing location to add node
     */
    void add (T& x, int pos);

    /**
     * Description: Removes a node from sequence and storing the removed element's reference in the variable x
     * @param x the reference to the removed node
     * @param pos index in sequence representing location of node
     */
    void remove (T& x, int pos);

    /**
     * Description: Gets value at pos
     * @param pos index in sequence representing location of node
     * @return value from given position
     */
    std::optional<T> entry (int pos);

    /**
     *Description: Gets pointer to object at pos
     *@param pos index in sequence representing location of node
     *@return pointer to node from pos
     */
    NodeRecord* getElementAt(int pos);


    /**
     * Description: size of sequence
     * @return number of nodes in sequence
     */
    int length ();

    /**
     * Description: prints out values in sequence
     * @return string containing values in sequence
     */
    std::string outputSequence();




    /**
  * Description: Transfer elements from one sequence to another
  * @param source Sequence to get elements from
  */
    void transferFrom(Sequence& source);

    /**
   * Description: Assign sequence elements to self leaving rhs unchanged
   * @param rhs Other sequence
   * @return generic type Sequence
   */
    Sequence& operator=(Sequence const& rhs);

};

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
    if (this==&source) return;
    NodeRecord* temp;
    clear(); //clears self
    head = source.head;
    size = source.size;
    source.head = nullptr;
    source.head = nullptr;
    source.size = 0;
}

template <class T>
Sequence<T>& Sequence<T>::operator=(Sequence const& rhs) = default;


template<class T>
void  Sequence<T>::add(T &x, int pos) {
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
    if (pos < 0 || pos > size) {
        throw std::invalid_argument("Error: pos is out of scope");
    }
    //find the element before pos and make it point to the element x is pointing to
    if (pos > 0) {
        NodeRecord* prevElemPointer = getElementAt(--pos);
        NodeRecord* currElemPtr = getElementAt(pos);
        prevElemPointer->next = currElemPtr->next;
        delete currElemPtr;
    } else {
        //pos == 0, meaning there is no previous element
        NodeRecord* nextElemPointer = getElementAt(++pos);
        delete head;//delete the node head is pointing to
        head = nextElemPointer;//make head point to element in front of it
    }

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
 typename Sequence<T>::NodeRecord* Sequence<T>::getElementAt(int pos)  {
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
    NodeRecord* currentValue = head;
    for (int i = 0; i < size; i++) {
        ss << currentValue->value << (i == (size-1)?"": ", ");
        currentValue = currentValue->next;
    }
    //Use insertion operator (<<) to build the string.
    return ss.str();
}



#endif
