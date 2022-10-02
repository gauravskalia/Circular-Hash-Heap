/*******************************************************************************************
* File Name          : ..
* Description        : Prog8130 - Assignment 4: least recently used cache (LRU cache)
*                      This program should implement a LRU cache
*
* Author:              Gaurav Kalia
* Date:                17th April, 2022
********************************************************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE   9  // the maximum of possible hash keys
#define LRU_SIZE    3  // size of the LRU cache

// structure used for holding data
typedef struct lrunode {
    const char* data;
    struct lrunode* prev;
    struct lrunode* next;
} lruNode;

typedef struct hashnode {
    struct lrunode *lp;         // pointer to the LRU node
} hashNode;

lruNode* lruFront = NULL;       // LRU front
lruNode* lruRare = NULL;        // LRU rare
int lruSize = 0;                // LRU size

hashNode hashTable[HASH_SIZE];  // create an empty hash table structure
                                // note that this time each bucket contains only one node
                                // so no linked list and we don't bother use pointers

// data used for test
const char* iData[] = {
    // for convenience, the hash value of a cache line will be its last number
    // e.g. "cache line 1" -> 1
    //      "cache line 3" -> 3
    // you can assume if cache hit, the hit element will be at the middle part of the LRU.
    "cache line 1",
    "cache line 3",
    "cache line 2",
    "cache line 3", // should hit the middle element
    "cache line 4",
    "cache line 3", // should hit the middle element
    "cache line 4", // should hit the middle element
    "cache line 5"
};
// end of data for assignment

// helper functions
// hash functions
void hashPut(const char*, lruNode *); // put LRU node into the hash table according to a cache line
lruNode* hashGet(const char*);        // get corresponding LRU node of a cache line if it exists in the hash table

// LRU functions
int lruGet(const char* line);        // try to retrieve a cache line

int main() {
    // keep calling lruGet. If hit, it will print
    // "get %s from cache"
    // otherwise it will print
    // "get %s from memory"
    for (int i = 0; i < sizeof(iData)/sizeof(iData[0]); i++) {
        if(lruGet(iData[i]) == 1) {
            printf("get %s from cache\n", iData[i]);
        }
        else {
            printf("get %s from memory\n", iData[i]);
        }
    }

    // validate
    // print out the LRU
    lruNode* p = lruFront;
    int cnt = 0;
    printf("Contents in LRU at the end:\n");
    while (p != NULL) {
        printf("%s\n", p->data);
        p = p->next;
        cnt++;
    }
    assert(cnt == LRU_SIZE);
    return 0;
}

// hashing function
unsigned long myHash(const char *str) {
    return str[strlen(str) - 1] - '0';
}

//====================== You should not modify anything above ==============================//
//==================== You should only modify following functions ==========================//
//============================= do not remove above comments  ==============================//

// FUNCTION      : hashPut
//
// DESCRIPTION   :
//   This function will add a new LRU node into the hash table
//   or set a bucket to NULL if necessary
//
// PARAMETERS    :
//   lp          - the LRU node or NULL
//
// RETURNS       :
//   Nothing
void hashPut(const char* line, lruNode* lp) {
    // use myHash() to get the bucket
    // set the LRU pointer (lp) of that bucket
    int data = myHash(line);
    hashNode *hash = (hashNode*)malloc(sizeof(hashNode));
    hash->lp = lp;
    hashTable[data] = *hash;
}

// FUNCTION      : hashGet
//
// DESCRIPTION   :
//   This function will check if a cache line exists
//
// PARAMETERS    :
//   line        - the cache line
//
// RETURNS       :
//   lruNode*    - the found LRU node or NULl if not found
lruNode* hashGet(const char* line) {
    // use myHash() to get the bucket
    // use the bucket to get the LRU pointer (lp)
    int d = myHash(line);
    if (hashTable[d].lp != NULL)
    {
        /* code */
        return (hashTable[d].lp);
    }
    return NULL;
}

// FUNCTION      : lruGet
//
// DESCRIPTION   :
//   This function will try to get an line from cache first. If failed,
//   it will get it from the memory
//
// PARAMETERS    :
//   line        - the cache line
//
// RETURNS       :
//   0 if get from memory, 1 if get from cache
int lruGet(const char* line) {
    lruNode *lp = hashGet(line);
    if (lp != NULL) {
        // move it to LRU head
        lruNode* a = lruFront;
        while (a->next != NULL)
        {
            /* code */
            if (a->data == line)
            {
                /* code */
                break;
            }
            a = a->next;
        }
        lruNode *prev = a->prev;
        lruNode *next = a->next;
        if (prev != NULL)
        {
            /* code */
            prev->next = next;
        }
        if (next != NULL)
        {
            /* code */
            next->prev = prev;
        }
        a->next = lruFront;
        a->prev = NULL;
        lruFront->prev = a;
        lruFront = a;
        return 1;
    }
    else {
        if (lruSize == LRU_SIZE) {
            // if LRU is full
            // remove last
            lruNode* l = lruRare;
            lruRare = l->prev;
            lruRare->next = NULL;
            free(l);
        }
        else {
            // otherwise increase lruSize
            lruSize++;
        }
        // insert the newNode to the front
        lruNode* newNode = (lruNode*)malloc(sizeof(lruNode));
        newNode->data = line;
        newNode->next = NULL;
        newNode->prev = NULL;

        if (lruFront != NULL)
        {
            /* code */
            newNode->next = lruFront;
            lruFront->prev = newNode;
        }
        lruFront = newNode;
        if (lruRare == NULL)
        {
            /* code */
            lruRare = lruFront;
        }
        

        // put it into the hash
        hashPut (line, newNode);
        return 0;
    }
}

