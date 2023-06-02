#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Job.h"

/* LinkedList Summary: 
 *   Includes the code for a LinkedList structure of LLNodes that hold Jobs as their
 *     data. Functionality includes creating LinkedLists and its LLNodes as well as
 *     inserting into, removing from, and printing the LinkedList.
 *   Major changes from v1: changed the name of node struct to LLNode.
 *     Added more printing functions and removal function.
 */

/* LLNode struct:
 *   LLNode* next: pointer to the next LLNode in the LinkedList
 *   LLNode* prev: pointer to the previous LLNode in the LinkedList
 *   Job* job: pointer to the Job that is considered the LLNode's data
 */
typedef struct LLNode {
    struct LLNode* next;
    struct LLNode* prev;
    Job* job;
} LLNode;

/* LinkedList struct:
 *   LLNode* tail: the last LLNode in the LinkedList structure
 *   LLNode* head: the first LLNode in the LinkedList structure
 *   int* size: the size of the LinkedList structure / total number of LLNodes in the LinkedList
 */
typedef struct LinkedList {
    LLNode* tail;
    LLNode* head;
    int size;
} LinkedList;

/* @brief initializes variables and allocates memory for a LLNode struct pointer 
 * @param Job* j: pointer to the Job of which to turn into a LLNode and allocate memory for both
 * @returns pointer to the LLNode created
 */
LLNode* createLLNode( Job* );

/* @brief initializes variables and allocates memory for a LinkedList struct pointer 
 * @param LinkedList* list: pointer to the LinkedList of which to allocate memory
 * @returns pointer to the LinkedList created
 */
LinkedList* createLinkedList( LinkedList* );

/* @brief inserts a Job pointer into the LinkedList given by creating a LLNode for the job 
 *   inserting it at the end of the LinkedList
 * @param LinkedList* list: pointer to the LinkedList of which to insert the Job*
 * @param Job* j: pointer to the Job to be added to the LinkedList
 * @returns pointer to the now extended LinkedList
 */
LinkedList* insertInLinkedList( LinkedList*, Job* );
//extern LinkedList* insertSorted( LinkedList* list );

/* @brief find and remove a node from a Linkedlist given a Job and a LinkedList
 * @param LinkedList* list: pointer to the LinkedList of which to remove the Job*
 * @param Job* j: pointer to the Job to be removed in the LinkedList
 * @returns pointer to the now modified LinkedList
 */
LinkedList* removeFromLinkedList( LinkedList* list, Job* j );

/* @brief prints all attributes of the Jobs in a LinkedList 
 * @param LinkedList* list: pointer to the LinkedList of which to print
 */
void printLinkedListJobs( LinkedList* );

/* @brief prints all of the Titles of the Jobs in a LinkedList
 * @param LinkedList* list: pointer to the LinkedList of which to print
 */
void printLinkedListTitles( LinkedList* );


/* @brief prints all of the States of the Jobs in a LinkedList
 * @param LinkedList* list: pointer to the LinkedList of which to print
 */
void printLinkedListStates( LinkedList* list );


#endif // LINKEDLIST_H