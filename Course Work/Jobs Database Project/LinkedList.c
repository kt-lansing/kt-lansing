#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

extern void printJob( Job* );
extern void printAttr(JobAttr*);
extern int compareJobs(Job*, Job*);

/* Given a Job pointer, allocate memory for the Job and the Node and assign the job to the Node.
 *   Initialize the next and previous Nodes of the created Node to be null. Return a pointer to
 *   the newly created Node
 */
LLNode* createLLNode( Job* j ){
    LLNode *n = (LLNode*)malloc(sizeof(LLNode));
    n->job = (Job*)malloc(sizeof(Job));
    n->job = j;
    n->next = NULL;
    n->prev = NULL;
    return(n);
}

/* Given a LinkedList pointer, allocate memory for the list and initialize the size to be 0
 *   Return a pointer to the created LinkedList 
 */
LinkedList* createLinkedList( LinkedList* list ){
    list = (LinkedList*)malloc(sizeof(LinkedList));
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    return(list);
}

/* Given a LinkedList pointer and a Job, create a LLNode from the job and insert it into the LinkedList
 *   depending on the size of the list and the positioning of the node in the LinkedList. 
 *   Increases the size of the list and return a pointer to it.
 */
LinkedList* insertInLinkedList( LinkedList* list, Job* j ){
    if(list == NULL) createLinkedList(list);
    LLNode *new = createLLNode( j );
    
    if(list->size == 0){
        list->head = new;
        list->tail = new;
    } else if(list->size == 1){
        list->head->next = new;
        new->prev = list->head;
        list->tail = new;
    } else {
        list->tail->next = new;
        new->prev = list->tail;
        list->tail = new;  
    }     
    list->size++;
    return list;
}

/* Iterates through the LinkedList parameter and uses the function compareJobs to compare the node's job
 *   to the parameter job. If the jobs match, it removes the job from the list with three cases of positioning
 *   in the LinkedList. Has a flag for if the job has been deleted, and prints if the job can't be found in the list
 *   If the job was found and removed, the size of the list is reduced by one. The LinkedList parameter is returned
 */
LinkedList* removeFromLinkedList( LinkedList* list, Job* j ){
    bool deleteFlag = false;
    if(list == NULL) return list;
    LLNode* curr = list->head;
    while(curr != NULL){
        if(compareJobs(j, curr->job) == 0){
            deleteFlag = true;
            //it's the head node
            if(curr->prev == NULL){
                list->head = curr->next;
            } else if (curr->next == NULL){
                list->tail = curr->prev;
                (curr->prev)->next = NULL;
            } else {
                (curr->prev)->next = curr->next;
                (curr->next)->prev = curr->prev;
            }
        } 
        curr = curr->next;
    }
    if(!deleteFlag){
        printf("Could not find job in list");
    } else {
        list->size--;
    }
    return list;
}

/* Given a LinkedList pointer, print all of the Jobs in the LinkedList by iterating 
 *   through all nodes and using the printAttr() method from Job.c
 */
void printLinkedListJobs( LinkedList* list ){
    if(list == NULL) return;
    LLNode* curr = list->head;
    while(curr != NULL){
        printJob( curr->job );
        curr = curr->next;
        printf("\n");
    }
}

/* Given a LinkedList pointer, print all titles of the Jobs in the LinkedList by iterating 
 *   through all nodes and using the printAttr() method from Job.c
 */
void printLinkedListTitles( LinkedList* list ){
    if(list == NULL) return;
    LLNode* curr = list->head;
    while(curr != NULL){
        printAttr(curr->job->attrList[0]);
        curr = curr->next;
    }
}

/* Given a LinkedList pointer, print all states of the Jobs in the LinkedList by iterating 
 *   through all nodes and using the printAttr() method from Job.c
 */
void printLinkedListStates( LinkedList* list ){
    if(list == NULL) return;
    LLNode* curr = list->head;
    while(curr != NULL){
        printAttr(curr->job->attrList[3]);
        curr = curr->next;
    }
}
