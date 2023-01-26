#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Job.h"
#include "LinkedList.h"

/* LinkedList Summary: 
 *   Includes the code for a BinaryTree structure of BTNodes that hold a LinkedList* of Jobs 
 *     as their data. Functionality includes creating BinaryTrees and its BTNodes as well as
 *     inserting into, removing from, and printing the BinaryTree, its nodes, and the jobs inside
 *     those nodes.
 *   Major changes from v1: Binary Tree fully replaces all ArrayList functionality
 */

/* BTNode struct:
 *   char* stateID: string of the state that all jobs of the node will have
 *   LinkedList* jobList: List of jobs held by the node that have same state as the stateID
 *   BTNode* left: pointer to BTNode's left child
 *   BTNode* right: pointer to BTNode's right child
 */
typedef struct BTNode {
    char* stateID;
    LinkedList* jobList;
    struct BTNode* left;
    struct BTNode* right;
} BTNode;

/* BinaryTree struct:
 *   BTNode* root: the root of the Binary Tree
 *   int* size: the size of the BinaryTree structure / total number of BTNodes in the tree
 */
typedef struct BinaryTree {
    struct BTNode* root;
    int size;
} BinaryTree;

char* BTInOrder;                    //string of all states in the Binary Tree
LinkedList* listOfJobs;             //LinkedList of all jobs in the Binary Tree

/* @brief initializes variables and allocates memory for a BTNode struct pointer 
 * @param Job* j: pointer to the Job of which to turn into a BTNode
 * @returns pointer to the BTNode created
 */
BTNode* createBTNode(Job* );

/* @brief Gets the BTNode with the stateID that matches the given Job*'s state attribute
 * @param BTNode** nodeAddr: address of the BTNode at which to start tree recursion
 * @param Job*: job pointer with which to find the matching BTNode
 * @returns address of the BTNode with the matching stateID to the job
 */
BTNode** getBTNode(BTNode**, Job*);

/* @brief Compares two BTNode's stateID to see which has the alphabetically larger stateID
 * @param BTNode* n1: first BTNode to compare
 * @param BTNode* n2: second BTNode to compare
 * @returns int value of which has the larger stateID (1 = 2nd BTNode bigger, -1 = first BTNode bigger, 0 = equal)
 */
int compareBTNode(BTNode* n1, BTNode* n2);

/* @brief Compares a Job and a BTNode's states to see which has the alphabetically larger state
 * @param BTNode* n1: BTnode to compare
 * @param Job* j: job to compare
 * @returns int value of which struct has the larger stateID (1 = Job is bigger, -1 = BTNode bigger, 0 = equal)
 */
int compareNodeToJob(BTNode* n1, Job* j);

/* @brief Initializes a binary tree object with memory and creates it's first node from the provided Job*
 * @param BinaryTree* bt: pointer to the BinaryTree struct to initialize
 * @param Job* j: jpointer to the ob to add into the BinaryTree as it's first BTNode
 * @returns pointer to the BinaryTree struct just initialized
 */
BinaryTree* createBinaryTree( BinaryTree*, Job* );

/* @brief Given the address of the pointer to a BTNode of a BinaryTree, recurse through the tree to find where to insert the Job given
 * @param BTNode** nodeAddr: address of the BTNode at which to start tree recursion
 * @param Job* j: pointer to the job to insert into the given BTNode's BinaryTree
 */
void insertInBinaryTree( BTNode**, Job* );

/* @brief Given a pointer to a BTNode of a BinaryTree, recurses through the tree to find the node with the matching Job to remove
 * @param BTNode* root: pointer to the BTNode with which to start tree recursion
 * @param Job* j: pointer to the job match to and remove in the given BTNode's BinaryTree
 * @returns pointer to the BTNode* where the recursion finally landed on
 */
BTNode* removeFromBinaryTree( BTNode*, Job* );

/* @brief Given a pointer to a BTNode of a BinaryTree, finds the smallest node accessible by the BTNode
 * @param BTNode* node: pointer to the BTNode with which to start tree recursion
 * @returns pointer to the BTNode in the smallest position of the Binary Tree accessible by the parameter BTNode
 */
BTNode* findSmallestBTNode( BTNode* );

/* @brief Given a pointer to a BTNode of a BinaryTree, prints all jobs accessible
 * @param BTNode* node: pointer to the BTNode with which to start tree recursion
 */
void printBTInOrder( BTNode* );

/* @brief Given a pointer to a BTNode of a BinaryTree, compares all accessible jobs to the Job* given
 * @param BTNode* node: pointer to the BTNode with which to start tree recursion
 * @param Job* j: pointer to job with which to compare the Jobs in each BTNode to 
 * @param int type: type of comparison that will be performed (0=exact match, 1=close match)
 */
void findJobsInBT(BTNode* node, Job* j, int type);

/* @brief Getter and initializer for the global LinkedList* variable listOfJobs
 * @param BTNode* node: node from which all accessible matching jobs will be added to listOfJobs
 * @param Job* j:
 * @returns returns the LinkedList* listOfJobs variable after initializing it with the provided parameters
 */
LinkedList* getJobsInBT(BTNode* node, Job* j, int type);

#endif // BINARYTREE_H
