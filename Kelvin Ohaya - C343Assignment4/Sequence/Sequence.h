#ifndef C343_ASSIGNMENT1EXAMPLE_SEQUENCE_H
#define C343_ASSIGNMENT1EXAMPLE_SEQUENCE_H

#include <string>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <utility>

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
        NodeRecord() : next(nullptr) {}
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
     * @param p A NodeRecord value (reference so caller's pointer can be nulled)
     */
    void reclaimAllNodes (NodeRecord*& p);

    /**
     * Description: Clone a list of NodeRecords and return pointer to head of the clone.
     */
    NodeRecord* cloneNodes(NodeRecord* src);

    /**
     * Swap helper
     */
    void swap(Sequence& other) noexcept {
        std::swap(head, other.head);
        std::swap(size, other.size);
    }

public:

    /**
     * Description: Constructor that initializes all attributes of this class.
     */
    Sequence ();

    /**
     * Description: Copy constructor (deep copy).
     */
    Sequence (Sequence const& other);

    /**
     * Description: Move constructor.
     */
    Sequence (Sequence&& other) noexcept;

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
     * @param pos index in sequence representing location to add node (0..size)
     */
    void add (T const& x, int pos);

    /**
     * Description: Removes a node from sequence and storing the removed element's value in the variable x
     * @param x the reference to store the removed node's value
     * @param pos index in sequence representing location of node (0..size-1)
     */
    void remove (T& x, int pos);

    /**
     * Description: Gets value at pos
     * @param pos index in sequence representing location of node
     * @return value from given position
     */
    std::optional<T> entry (int pos, int* counter = nullptr) const;

    /**
     *Description: Gets pointer to object at pos
     *@param pos index in sequence representing location of node
     *@return pointer to node from pos or nullptr if out of bounds
     */
    NodeRecord* getElementAt(int pos, int* counter = nullptr) const;


    /**
     * Description: size of sequence
     * @return number of nodes in sequence
     */
    int length () const;

    /**
     * Description: prints out values in sequence
     * @return string containing values in sequence
     */
    std::string outputSequence() const;

    /**
     * Description: Transfer elements from one sequence to another (move semantics).
     * After call, source becomes empty.
     * @param source Sequence to get elements from
     */
    void transferFrom(Sequence& source);

    /**
     * Description: Assign sequence elements to self (deep copy)
     * @param rhs Other sequence
     * @return reference to this
     */
    Sequence& operator=(Sequence const& rhs);

    /**
     * Move assignment
     */
    Sequence& operator=(Sequence&& rhs) noexcept;

};

/* ------------------ Implementations (templates live in header) ------------------ */

template <class T>
Sequence<T>::Sequence ()
    : head(nullptr), size(0)
{}

template <class T>
Sequence<T>::Sequence(Sequence const& other)
    : head(nullptr), size(0)
{
    head = cloneNodes(other.head);
    size = other.size;
}

template <class T>
Sequence<T>::Sequence(Sequence&& other) noexcept
    : head(nullptr), size(0)
{
    swap(other);
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
    head = nullptr;
    size = 0;
}

template <class T>
void Sequence<T>::reclaimAllNodes (NodeRecord*& p)
{
    NodeRecord* cur = p;
    while (cur != nullptr) {
        NodeRecord* nxt = cur->next;
        delete cur;
        cur = nxt;
    }
    p = nullptr;
}

template <class T>
typename Sequence<T>::NodeRecord* Sequence<T>::cloneNodes(NodeRecord* src)
{
    if (src == nullptr) return nullptr;
    NodeRecord* newHead = new NodeRecord();
    newHead->value = src->value;
    NodeRecord* dst = newHead;
    src = src->next;
    while (src != nullptr) {
        NodeRecord* n = new NodeRecord();
        n->value = src->value;
        dst->next = n;
        dst = n;
        src = src->next;
    }
    dst->next = nullptr;
    return newHead;
}

template <class T>
void Sequence<T>::transferFrom(Sequence& source)
{
    if (this == &source) return;
    clear(); // clear self
    head = source.head;
    size = source.size;
    source.head = nullptr;
    source.size = 0;
}

template <class T>
Sequence<T>& Sequence<T>::operator=(Sequence const& rhs)
{
    if (&rhs == this) return *this;
    Sequence copy(rhs);
    swap(copy);
    return *this;
}

template <class T>
Sequence<T>& Sequence<T>::operator=(Sequence&& rhs) noexcept
{
    if (&rhs == this) return *this;
    reclaimAllNodes(head);
    head = rhs.head;
    size = rhs.size;
    rhs.head = nullptr;
    rhs.size = 0;
    return *this;
}

template<class T>
void Sequence<T>::add(T const& x, int pos) {
    if (pos < 0 || pos > size) {
        throw std::invalid_argument("Error: pos is out of range");
    }

    NodeRecord* newElem = new NodeRecord();
    newElem->value = x;
    newElem->next = nullptr;

    if (pos == 0) {
        newElem->next = head;
        head = newElem;
    } else {
        NodeRecord* prev = getElementAt(pos - 1);
        if (prev == nullptr) {
            delete newElem;
            throw std::invalid_argument("Internal error: invalid previous element");
        }
        newElem->next = prev->next;
        prev->next = newElem;
    }
    ++size;
}

template<class T>
void Sequence<T>::remove(T &x, int pos) {
    if (pos < 0 || pos >= size) {
        throw std::invalid_argument("Error: pos is out of range");
    }

    NodeRecord* toDelete = nullptr;
    if (pos == 0) {
        toDelete = head;
        head = head->next;
    } else {
        NodeRecord* prev = getElementAt(pos - 1);
        toDelete = prev->next;
        prev->next = toDelete->next;
    }
    x = toDelete->value;
    delete toDelete;
    --size;
}

template<class T>
std::optional<T> Sequence<T>::entry(int pos, int *counter) const {
    if (pos < 0 || pos >= size) {
        return std::nullopt;
    }
    NodeRecord* cur = getElementAt(pos, counter);
    if (cur == nullptr) return std::nullopt;
    return cur->value;
}

template<class T>
typename Sequence<T>::NodeRecord* Sequence<T>::getElementAt(int pos, int *counter) const {
    if (pos < 0 || pos >= size) return nullptr;
    NodeRecord* cur = head;
    for (int i = 0; i < pos; ++i) {
        cur = cur->next;
        if (counter) ++(*counter);
    }
    return cur;
}

template<class T>
int Sequence<T>::length() const {
    return size;
}

template<class T>
std::string Sequence<T>::outputSequence() const {
    std::stringstream ss;
    NodeRecord* currentValue = head;
    for (int i = 0; i < size && currentValue != nullptr; i++) {
        ss << currentValue->value << (i == (size-1) ? "" : ", ");
        currentValue = currentValue->next;
    }
    return ss.str();
}

#endif
