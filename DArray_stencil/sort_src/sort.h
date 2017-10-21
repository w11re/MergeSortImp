#ifndef SORT_H
#define SORT_H

#include "darray.h"

template<class T>
void sort( DArray<T> &data ){
    int m_size = sizeof(data);
    divideList(data, 0, m_size);
}

template<class T>
void divideList(DArray<T> &m_array, T lefty, T righty) {

    //Recursive to divide the list into sublists and merge sublists to produce a sorted sublist with the merge method
    if (lefty < righty) {
        int middleGround = lefty+(righty-lefty)/2;
        divideList(m_array, lefty, middleGround);
        divideList(m_array, middleGround + 1, righty);

        mergeSort(m_array, lefty, middleGround, righty);
    }
}

template<class T>
void mergeSort(DArray<T> &m_array, T lefty, T middleGround, T righty) {
    int i = 0, j = 0;
    T firstSect = middleGround - lefty + 1;
    T secondSect =  righty - middleGround;
    DArray<T> leftArray, rightArray;
    DArray<T> iAmMerging;

    for (i = 0; i < firstSect; i++) {
        leftArray[i] = m_array[lefty + i];
    }
    for (j = 0; j < secondSect; j++) {
        rightArray[j] = m_array[middleGround + 1 + j];
    }

    //Sorting rotation starts here.
    //Inserts lower value of the leftmost indexes of either array and puts them into the merged array so we can sort with recursion
    while (i < firstSect && j < secondSect) {
        if (leftArray[i] <= rightArray[j]) {
            iAmMerging[lefty] = leftArray[j];
            i++;
        }
        else {
            iAmMerging[lefty] = rightArray[j];
            j++;
        }

        lefty++;
    }

    m_array = iAmMerging;
}


#endif // SORT_H
