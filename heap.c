/*******************************************************************************************
* File Name          : ..
* Description        : Prog8130 - Assignment 4: Heap
*                      This program should implement a MAX-heap to manage a list of positive
*                      numbers using its array representation
*
* Author:              Gaurav Kalia
* Date:                17th April, 2022
********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SWAP(x, y) do { int t = x; x = y; y = t; } while(0)

void heapSort(int *, int);
void printarr(int *, int);
void heap(int *, int, int);             // construct a max-heap of an array using array representation

int main(int argc, char* argv[]) {
    int arrSize = argc - 1;
    int *arr = (int *) malloc ( sizeof(int) * arrSize );
    // input will be a heap but not sorted and it will have more than 1 number
    // sample input command line arguments: 100 19 36 17 3 25 1 2 7
    for (int i = 0; i < arrSize; i++) {
        arr[i] = atoi(argv[i+1]);
    }
    printf("input heap is:\n");
    printarr(arr, arrSize);
    printf("begin heapSort:\n");
    heapSort(arr, arrSize);
    printf("done\n");
    return 0;
}

void printarr(int *arr, int arrSize) {
    for (int i = 0; i < arrSize-1; i++) {
        printf("%d ", arr[i]);
    }
    printf("%d\n", arr[arrSize-1]);
}

void heapSort(int *arr, int arrSize) {
    for (int curSize = arrSize; curSize > 1; curSize--) {
        heap(arr, 0, curSize);
        printf("%13s", "heapify: ");
        printarr(arr, arrSize);
        // swap root and the last number in arr
        SWAP(arr[0], arr[curSize-1]);
        printf("%13s", "swap root: ");
        printarr(arr, arrSize);
    }
    return;
}

//====================== You should not modify anything above ==============================//
//==================== You should only modify following functions ==========================//
//============================= do not remove above comments  ==============================//

// FUNCTION      : heap
//
// DESCRIPTION   :
//   This function will convert an array into a max-heap
//
// PARAMETERS    :
//   int* arr    - The array
//   int curNode - current node index
//   int arrSize - size of the array. used by upper-level function. Do NOT change
//
// RETURNS       :
//   None
void heap(int *arr, int curNode, int arrSize) {
    // you can use the SWAP macro to quickly swap two nodes
    // refer to the lecture slide or recording if you forget how to do this
    int a = curNode;
    int l = 2 * curNode + 1;
    int r = 2 * curNode + 2;

    if (l < arrSize && arr[l] > arr[a])
    {
        /* code */
        a = l;
    }
    if (r < arrSize && arr[r] > arr[l])
    {
        /* code */
        a = r;
    }
    if (a != curNode)
    {
        /* code */
        SWAP(arr[curNode], arr[a]);
        heap(arr, a, curNode);
    }
    return;
}

