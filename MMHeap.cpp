// Author: Atyub Ahmad
// Project: MMHeap
// File: MMHeap.cpp
// Min-Max Heap file

#ifndef MMHEAP_H
#define MMHEAP_H
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <stdexcept>
#include "Int4MMH.h"


using namespace std;


template<typename T>
class MMHeap{
public:
    // Array and size
    T** pData;
    size_t length;

    //Default Constructor
    MMHeap() :pData(nullptr), length(0) {};

    //Overloaded Constructor
    MMHeap(const int& initialSize):length(0){
        pData = new T*[initialSize];
        arrSize = initialSize;
    };

    //Destructor
    ~MMHeap();

    //Returning the amount of items inside of the array
    size_t size() const {return length;}

    //Inserts into the heap
    void insert(T* px);

    //Prints the heap's content
    void dump();

    //Pushes the minimum value to the top
    void PushUpMin(int);

    //Pushes the maximum values to index 1 or 2
    void PushUpMax(int);

    //Pushes down the root value if needed
    void PushDownMin(int);

    //Pushes down the value stored at the maximum index if needed
    void PushDownMax(int);

    //Swaps two values
    void Swap(int, int);

    //Getters for min/max
    T* getMin();
    T* getMax();

    //Deletes min/max
    T deleteMin();
    T deleteMax();

    //Finds left/right child's index
    int LeftChild(int);
    int RightChild(int);

    //Finds the (grand)parent's index
    int Parent(int);
    int GrandParent(int);

private:
    //Size of the whole array
    int arrSize;
};

template<typename T>
//Destructor
MMHeap<T>::~MMHeap() {
    //Deleting content within the array
    for(unsigned int i = 0; i < size(); i++){
        delete pData[i];
        pData[i] = NULL;
    }
    //Deleting the array
    delete[] pData;
}

//Inserting value into the heap
template<typename T>
void MMHeap<T>::insert(T *px) {
    try {
        //Index being inserted at
        int index = length;

        //Checking if index is within the size of the array
        if (arrSize > index) {
            //Inserting the new value
            pData[index] = px;
            //Incrementing the amount of values inside the array
            length++;

            //Checking to see if the array has at least 2 items
            if (index != 0) {
                //Finding the parent index
                int parentIndex = Parent(index);
                //Checking what level the value is being inserted into
                int level = floor(log2(length));

                //If it is even (min) level
                if (level % 2 == 0) {
                    //Checking if the new value is greater than the parent's value
                    if (*pData[index] > *pData[parentIndex]) {
                        //Swapping the two values
                        Swap(index, parentIndex);
                        //Pushing up the max on the parent's index
                        PushUpMax(parentIndex);
                    } else {
                        //Pushing up the min on the new value's index
                        PushUpMin(index);
                    }
                //Odd (max) level
                } else {
                    //New value is less than parent's value
                    if (*pData[index] < *pData[parentIndex]) {
                        //Swapping the two values
                        Swap(index, parentIndex);
                        //Pushing up the min on the parent's index
                        PushUpMin(parentIndex);
                    } else {
                        //Pushing up the max on the index
                        PushUpMax(index);
                    }
                }
            }
        //Error Statement
        }else{
            cout << "No more available indexes to insert into the array" << endl;
        }

    //Exception
    }catch(exception& e){
        cerr << "Exception caught: " << e.what() << endl;
    }
}

//Printing content within heap
template<typename T>
void MMHeap<T>::dump() {

    //Finding min and max
    T *min = getMin();
    T *max = getMax();

    //Printing the statistics of the heap
    cout << "--- min-max heap dump ---" << endl;
    cout << "  Size = " << size() << endl;
    cout << "  Minimum = " << *min << endl;
    cout << "  Maximum = " << *max << endl;

    //Checking level
    int level = floor(log2(length));

    //Even
    if(level % 2 == 0){
        cout << "  Last level is even" << endl;
    //Odd
    }else{
        cout << "  Last level is odd" << endl;
    }

    //Printing the content within the heap
    cout << "--- heap data items ---" << endl;
    for(unsigned int i = 0; i < length; i++){
        cout << "H[" << i + 1 << "]: " << *pData[i] << endl;
    }
}

//Finding the minimum
template<typename T>
T *MMHeap<T>::getMin() {
    //Nothing inside the array
    if(length == 0){
        cout << "No data in heap" << endl;
        return NULL;
    }
    //Returning the min
    return pData[0];
}

//Finding the maximum
template<typename T>
T *MMHeap<T>::getMax() {
    //index 1 and 2 exist
    if(length > 2) {
        //Return whichever value is higher
        if (*pData[1] > *pData[2]) {
            return pData[1];
        } else {
            return pData[2];
        }
    }else{
        //One value exists
        if(length == 1){
            //Return the only value that exists
            return pData[0];
        //Only 2 values exist
        } else if (length == 2){
            //Return value at index one
            return pData[1];
        }
        //Error Statement
        cout << "No data in heap" << endl;
        return NULL;
    }
}

//Deleting minimum
template<typename T>
T MMHeap<T>::deleteMin() {
    //At least two values exists
    if(length > 1) {
        //Temp for root index
        T* temp = pData[0];

        //Setting the root index to the last value inside the array
        pData[0] = pData[size() - 1];

        //Decrementing amount of values inside array
        --length;
        //Deleting
        delete temp;
        //Pushing down the min on root index
        PushDownMin(0);
        //Returning min
        return *pData[0];
    }else{
        //if one value exists
        if(length == 1){
            //Deleting
             delete pData[0];
            --length;
            return *pData[0];
        }
        //Error Statement
        cout << "No data in heap" << endl;
        return *pData[0];
    }

}

//Deleting Max
template<typename T>
T MMHeap<T>::deleteMax() {
    //At least 2 values exists
    if(length > 2) {
        //Deleting the greater value
        if (*pData[1] > *pData[2]) {
            //Temp for max
            T *temp = pData[1];
            //Setting the index of the max to the last value in the array
            pData[1] = pData[size() - 1];

            //Decrementing amount of values
            --length;
            //Deleting
            delete temp;
            //Pushing down max
            PushDownMax(1);
            //Returning the max
            return *pData[1];
        //Same as above just on index 2
        } else {
            T *temp = pData[2];
            pData[2] = pData[size() - 1];

            --length;
            delete temp;
            PushDownMax(2);
            return *pData[2];
        }
    }else{
        //One value exists
        if(length == 1){
            deleteMin();
        //Two values exists
        }else if(length == 2){
            delete pData[1];
            --length;
            return *pData[1];
        }
        //Error Statement
        cout << "No data in heap" << endl;

    }
    return *pData[0];
}

//Returning left child's index
template<typename T>
int MMHeap<T>::LeftChild(int index) {
    //Equation to find left child's index
    index = (2 * index) + 1;

    return index;
}

//Returning right child's index
template<typename T>
int MMHeap<T>::RightChild(int index) {
    //Equation to find right child's index
    index = (2 * index) + 2;

    return index;
}

//Returning parent's index
template<typename T>
int MMHeap<T>::Parent(int index) {
    //Equation to find parent's index
    index = (index - 1) / 2;

    return index;
}

//Returning grandparent's index
template<typename T>
int MMHeap<T>::GrandParent(int index) {
    //If grandparent exists
    if(index <= 2){
        return -1;
    }else {
        //Equation to find grandparent's index
        index = (index - 3) / 4;

        return index;
    }
}

//Pushing the minimum value up
template<typename T>
void MMHeap<T>::PushUpMin(int index) {
    //Grandparent index
    int grandparentIndex = GrandParent(index);

    //If grandparent index exists and index is less than grandparent
    if(grandparentIndex > -1 and *pData[index] < *pData[grandparentIndex]){
        //Swap the two values
        Swap(index, grandparentIndex);
        //Check again on grandparent's index
        PushUpMin(grandparentIndex);
    }
}

//Pushing up the maximum value
template<typename T>
void MMHeap<T>::PushUpMax(int index) {
    //Grandparent index
    int grandparentIndex = GrandParent(index);

    //If grandparent index exists and index is greater than grandparent
    if(grandparentIndex > -1 and *pData[index] > *pData[grandparentIndex]){
        //Swap the two values
        Swap(index, grandparentIndex);
        //Check again on grandparent's index
        PushUpMax(grandparentIndex);
    }
}

//Swapping two values
template<typename T>
void MMHeap<T>::Swap(int index1, int index2) {
    T *temp = pData[index1]; //Variable to hold index1's original value
    pData[index1] = pData[index2]; //Setting index1's value to index2's value
    pData[index2] = temp; //Setting index2's value to index1's original value
}


//Pushing down the minimum
template<typename T>
void MMHeap<T>::PushDownMin(int index) {
    int inleftChild = LeftChild(index); //Left child
    int inrightChild = RightChild(index); //Right child
    int lowestChild = inleftChild; //Lowest value child

    int leftGrandchild = LeftChild(inleftChild); //Most left grandchild
    int midleft = RightChild(inleftChild); //Middle left grandchild


    int rightGrandchild = RightChild(inrightChild); //Most right grandchild
    int midright = LeftChild(inrightChild); //Middle right grandchild

    int lowestleft = leftGrandchild; //Lowest grandchild on left side
    int lowestright = midright; //Lowest grandchild on right side

    int hsize = size() - 1; //Amount of values
    int lowest = -1; //Lowest value out of all the children and grandchildren

    //Left and Right child exists
    if(inleftChild < hsize and inrightChild < hsize) {

        //Storing the lowest child
        if(*pData[inleftChild] > *pData[inrightChild]){
            lowestChild = inrightChild;
        }

        //Storing the lowest left side grandchild
        if(leftGrandchild < hsize and midleft < hsize and *pData[lowestleft] > *pData[midleft]){
            lowestleft = midleft;
        }

        //Storing the lowest right side grandchild
        if(rightGrandchild < hsize and midright < hsize and *pData[midright] > *pData[rightGrandchild]){
            lowestright = rightGrandchild;
        }

        //Storing the lowest out of the left and right side
        if(*pData[lowestleft] > *pData[lowestright]){
            lowest = lowestright;
        }else{
            lowest = lowestleft;
        }
    }

    //If lowest exists and is within the range of the indexes
    if(lowest > -1 and lowest < hsize){
        //If the grandchild is less than the index
        if(*pData[lowest] < *pData[index]){
            //Swap the values
            Swap(index, lowest);

            //If the grandchild is greater than its parent
            if(*pData[lowest] > *pData[Parent(lowest)]){
                //Swap the values
                Swap(lowest, Parent(lowest));
            }
            //Check again on the grandchild
            PushDownMin(lowest);
        }
    //If the child is the lowest
    }else if(lowestChild < hsize){
        //Child is lower than index
        if(*pData[lowestChild] < *pData[index]) {
            //Swap the values
            Swap(index, lowestChild);
        }
    }
}


template<typename T>
void MMHeap<T>::PushDownMax(int index) {
    int inleftChild = LeftChild(index); //Left child
    int inrightChild = RightChild(index); //Right child
    int greatestChild = inleftChild; //Lowest value child

    int leftGrandchild = LeftChild(inleftChild); //Most left grandchild
    int midleft = RightChild(inleftChild); //Middle left grandchild


    int rightGrandchild = RightChild(inrightChild); //Most right grandchild
    int midright = LeftChild(inrightChild); //Middle right grandchild

    int greatestLeft = leftGrandchild; //greatest grandchild on left side
    int greatestRight = midright; //greatest grandchild on right side

    int hsize = size() - 1; //Amount of values
    int greatest = -1; //greatest value out of all the children and grandchildren

    //Left and Right child exists
    if(inleftChild < hsize and inrightChild < hsize) {
        //Storing the greatest child
        if(*pData[inleftChild] < *pData[inrightChild]){
            greatestChild = inrightChild;
        }

        //Storing the greatest left side grandchild
        if(leftGrandchild < hsize and midleft < hsize and *pData[greatestLeft] < *pData[midleft]){
            greatestLeft = midleft;
        }

        //Storing the greatest right side grandchild
        if(rightGrandchild < hsize and midright < hsize and *pData[midright] < *pData[rightGrandchild]){
            greatestRight = rightGrandchild;
        }

        //Storing the greatest right side grandchild
        if(greatestLeft < hsize and greatestRight < hsize and *pData[greatestLeft] < *pData[greatestRight]){
            greatest = greatestRight;
        }else{
            greatest = greatestLeft;
        }
    }
    //If greatest exists and is within the range of the indexes
    if(greatest > -1 and greatest < hsize){
        if(*pData[greatest] > *pData[index]){
            //Swap the values
            Swap(index, greatest);

            //Parent is greater
            if(*pData[greatest] < *pData[Parent(greatest)]){
                //Swap the values
                Swap(greatest, Parent(greatest));
            }
            //Check again on the grandchild
            PushDownMax(greatest);
        }

    //If the child is the greatest
    }else if(greatestChild < hsize){
        //Child is greater than the parent
        if(*pData[greatestChild] > *pData[index]) {
            //Swap the values
            Swap(index, greatestChild);
        }
    }

}



#endif
