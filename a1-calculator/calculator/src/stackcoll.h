#ifndef STACKCOLL_H
#define STACKCOLL_H

#include <iostream>
using namespace std;


/**
 *Class StackCOLL
 * -----------------
 * implements stack of the specicied value type
 * based on the dynamic array
 */
template <typename ValueType>
class StackCOLL {
    // public functions prototypes
public:
    StackCOLL();
    virtual ~StackCOLL();
    void push(ValueType value);
    ValueType pop();
    void clear();
    bool isStackEmpty() const;
    ValueType top() const;
    int size() const;

    // private functions prototypes
private:
    static const int START_SIZE = 10;
    ValueType *array;               // dynamic array for elements
    int currentSize;                // size of array
    int count;                      // counter of array elements
    void extendArray();             // increases dynamic array in two times

};



/**
 *Constructor: StackCOLL
 * ---------------------
 * initialazes new empty stack
 */
template <typename ValueType>
StackCOLL<ValueType>::StackCOLL(){
    array = new ValueType[START_SIZE];
    currentSize = START_SIZE;
    count = 0;
}

/**
 *Destructor: ~StackCOLL
 * -----------------------
 * Frees memory
 */
template <typename ValueType>
StackCOLL<ValueType>::~StackCOLL(){
    delete[] array;
}

/**
 *Function: push
 * Usage: stack.push(value)
 * ---------------------------
 * Pushes value on the stack
 */
template <typename ValueType>
void StackCOLL<ValueType>::push(ValueType value){
    if (count == currentSize){ //check for a free space for new element
        extendArray();
    }
    array[count] = value;
    count++;
}

/**
 *Function: pop
 * Usage: value = stack.pop()
 * -------------------------
 * Remove top element of the stack and return it's value
 */
template <typename ValueType>
ValueType StackCOLL<ValueType>::pop(){
    if (isStackEmpty()){
        cout << "Stack is empty" << endl;
        exit(1);
    }
    count--;
    return array[count];

}

/**
 *Function: cleaar
 * Usage: stack.clear()
 * --------------------
 * removes all elements of the stack
 */
template <typename ValueType>
void StackCOLL<ValueType>::clear(){
    count = 0;
}

/**
 *Function: isStackEmpty
 * Usage: if(stack.isStackEmpty())
 * ---------------------------
 * Return true if stack is empty
 */
template <typename ValueType>
bool StackCOLL<ValueType>::isStackEmpty() const {
    return count == 0;
}

/**
 *Function: top
 * Usage: value = stack.top()
 * ---------------------------
 * Returns value of the top element of the StackCOLLwithout removing it
 */
template <typename ValueType>
ValueType StackCOLL<ValueType>::top() const {
    if (isStackEmpty()){
        cout << "Stack is empty" << endl;
        exit(1);
    }
    return array[count-1];
}

/**
 *Function size
 * Usage: int size = stack.size()
 * ------------------------------
 * Returns number of the lelements of the stack
 */
template <typename ValueType>
int StackCOLL<ValueType>::size() const{
    return count;
}

/**
 *Function: extendArray
 * Usage: extendArray()
 * --------------------
 * Increases dynamic array
 */
template <typename ValueType>
void StackCOLL<ValueType>::extendArray(){
    ValueType *oldArray = array;
    currentSize *= 2;
    array = new ValueType[currentSize];

    for (int i = 0; i < count; i++){
        array[i] = oldArray[i];
    }
    delete[] oldArray;
}


#endif // STACKCOLL

