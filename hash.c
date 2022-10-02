/*******************************************************************************************
* File Name          : ..
* Description        : Prog8130 - Assignment 4: Hash Table
*                      This program should implement a hash table to put/get a list of
*                      strings
*
* Author:              Gaurav Kalia
* Date:                17th April, 2022
********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE    10                                 // size of hash table to be used

// structure used for holding data
typedef struct hashnode {
    const char *data;                                   // the text data of the current node
    unsigned long hashvalue;                            // the calculated hash value
    struct hashnode *next;                              // pointer to the next node in this hash bucket
} hashNode;

hashNode* hashTable[HASH_SIZE];                         // create an empty hash table structure
                                                        // (note this is basically an array of linked list heads)

// data used for test
const char* iData[] = {
    "In computing, a hash table (hash map) is a data structure that implements an associative array abstract data type, a structure that can map keys to values",
    "A hash table uses a hash function to compute an index, also called a hash code, into an array of buckets or slots, from which the desired value can be found.",
    "During lookup, the key is hashed and the resulting hash indicates where the corresponding value is stored.",
    "This sentence should exist in the hash table"
};
const char* cData[] = {
    "Hello World",                                      // not in the hash table
    "This sentence should exist in the hash table"      // in the hash table
};
// end of data for assignment

// hash functions
void put(const char* data);                             // put text into the hash table
int check(const char* data);                            // check if text exists in the hash table, 1 if exists, 0 if not exists

int main() {
    int i = 0;
    // init
    for (i = 0; i < HASH_SIZE; i++) {
        hashTable[i] = NULL;
    }
    // put data into the hash table
    for (i = 0; i < sizeof(iData)/sizeof(iData[0]); i++) {
        put(iData[i]);
    }
    // validate
    for (i = 0; i < HASH_SIZE; i++) {
        if (hashTable[i] != NULL) {
            printf("bucket[%d] contains data\n", i);
        }
    }
    for (i = 0; i < sizeof(cData)/sizeof(cData[0]); i++) {
        // cres == 0 if not found, or 1 if found
        int cres = check(cData[i]);
        if (cres == 0) {
            printf("not found '%s'\n", cData[i]);
        }
        else if (cres == 1) {
            printf("found '%s'\n", cData[i]);
        }
    }
    return 0;
}

// hashing function, as shown in class
unsigned long sdbm(const char *str) {
    unsigned long hash = 0;
    int c;
    for (c = *str; *str != '\0'; str++) {
        hash = c + (hash << 6) + (hash << 16) - hash;
    }
    return hash;
}

//====================== You should not modify anything above ==============================//
//==================== You should only modify following functions ==========================//
//============================= do not remove above comments  ==============================//

// FUNCTION      : put
//
// DESCRIPTION   :
//   This function will add new text data into the hash table
//
// PARAMETERS    :
//   dat - the text data
//
// RETURNS       :
//   Nothing
void put(const char* data) {
    // call sdbm() to get the hash
    unsigned long h = sdbm(data);
    // reduce the hash to a number which our buckets fit
    int d = h % HASH_SIZE;
    // malloc a hash node, note that we also save the hashvalue from sdbm()
    hashNode* val = (hashNode*)malloc(sizeof(hashNode));
    // insert it to the hash table
    // remember to use the linked list handle collisions
    if (val != NULL)
    {
        /* code */
        val->hashvalue =h;
        val->data = data;
        val->next = NULL;
    }
        hashTable[d]= val;
    return;
}

// FUNCTION      : check
//
// DESCRIPTION   :
//   This function will check if text data is in the hash table
//
// PARAMETERS    :
//   data - the text data
//
// RETURNS       :
//   0 if not found, 1 if found
int check(const char* data) {
    // call sdbm() to get the hash
    unsigned long h = sdbm(data);
    // reduce the hash to a number which our buckets fit
    int a = (h)% HASH_SIZE;
    // use the bucket to access the hash node or nodes (since it can be a linked list)
        if (hashTable[a]!= NULL && strcmp(hashTable[a]->data, data))
        {
            /* code */
            return 1;
        }
         return 0;
    }
    
    // compare its hash to see if it matches

    // return 1 if found; 0 if not found


