#ifndef QUEUECOLL_H
#define QUEUECOLL_H

#include <iostream>
using namespace std;

/**
 * Class QueueCOLL implements queue of ValueType elements
 * based on the linked list
 */
template <typename ValueType>
class QueueCOLL{
    // public functions prototypes
public:
    QueueCOLL();
    virtual ~QueueCOLL();
    ValueType dequeue();
    void enqueue (ValueType);
    void clear();
    int size() const;
    bool isQueueEmpty() const;
    ValueType initial() const;

    // private functions protypes
private:
    /**
     * The ListNode struct for elements of the queue
     */
    struct ListNode{
        ValueType value;
        ListNode* nextPtr;
    };

    ListNode* firstPtr;      // a pointer to the first node
    ListNode* lastPtr;       // a pointer to the last node
    int count;               // counter for queue elements

};


/**
 *Constructor: QueueCOLL
 * Initializes new empty queue
 */
template <typename ValueType>
QueueCOLL<ValueType> :: QueueCOLL(){
    count = 0;
    firstPtr = lastPtr = NULL;
}

/**
 *Destructor: QueueCOLL
 * Frees memory
 */
template <typename ValueType>
QueueCOLL<ValueType> :: ~QueueCOLL(){
    for(int i = 0; i < count; i++){
        ListNode *tmpPtr = firstPtr;
        firstPtr = firstPtr->nextPtr;
        delete tmpPtr;
    }
}

/**
 *Function: dequeue
 * Usage: value = queue.dequeue();
 * -------------------------------
 * remove first element of the queue
 * end return it's value
 */
template<typename ValueType>
ValueType QueueCOLL<ValueType> :: dequeue(){
    if (count == 0){
      cout << "Queue is empty" << endl;
        exit(1);
    }
        ListNode *tmpPtr = firstPtr;
        firstPtr = firstPtr->nextPtr;
        ValueType tmpValue = tmpPtr->value;
        count--;
        delete tmpPtr;
        return tmpValue;
}

/**
 *Function: enqueue
 * Usage: queue.enqueue(value)
 * ---------------------------
 * Adds new element to the queue
 */
template<typename ValueType>
void QueueCOLL<ValueType> :: enqueue(ValueType newValue){
    ListNode *newPtr = new ListNode;
    newPtr->value = newValue;
    newPtr->nextPtr = NULL;
    if(firstPtr == NULL) { //if queue is empty
        firstPtr = lastPtr = newPtr;
    } else {
        lastPtr->nextPtr = newPtr;
        lastPtr  = newPtr;
    }
    count++;
}

/**
 *Function: clear
 * Usage: queue.clear()
 * ---------------------
 * remove all elements of the queue
 */
template<typename ValueType>
void QueueCOLL<ValueType> :: clear(){
    for(int i = 0; i < count; i++){
        ListNode *tmpPtr = firstPtr;
        firstPtr = firstPtr->nextPtr;
        delete tmpPtr;
    }
    count = 0;
}

/**
 *Function: size
 * Usage: int size = queue.size()
 * ------------------------------
 * return current number of the elements
 * of the queue
 */
template<typename ValueType>
int QueueCOLL<ValueType> :: size() const{
    return count;
}

/**
 *Function: isQueueEmpty
 * Usage: if(queue.isQueueEmpty)
 * --------------------------
 * Returns true if queue is empty
 */
template<typename ValueType>
bool QueueCOLL<ValueType> :: isQueueEmpty() const{
    return count == 0;
}

/**
 *Function: initial
 * Usage: value = queue.initial()
 * -----------------------------
 * Return value of the first element without removing it
 */
template<typename ValueType>
ValueType QueueCOLL<ValueType> :: initial() const{
    return firstPtr->value;
}


#endif // QUEUECOLL

