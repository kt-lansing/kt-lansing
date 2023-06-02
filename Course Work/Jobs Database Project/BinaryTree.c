#include "BinaryTree.h"

extern LinkedList* createLinkedList( LinkedList* list );
extern LinkedList* insertInLinkedList( LinkedList* list, Job* j );
extern LinkedList* removeFromLinkedList( LinkedList* list, Job* j );
extern void printLinkedListStates( LinkedList* list );
extern int compareJobs( Job* j1, Job* j2);

/* Takes a job and creates both the node and the jobList of the node so the job can be
 *   inserted into the jobList. Sets the stateID to the state of the given job, and 
 *   initializes both left and right children nodes to NULL with memory.
 */
BTNode* createBTNode(Job* j){
    BTNode* node = (BTNode*)malloc(sizeof(BTNode));
    node->jobList = createLinkedList( node->jobList );
    node->jobList = insertInLinkedList( node->jobList, j );
    node->stateID = j->attrList[3]->data[0];
    node->left = (BTNode*)malloc(sizeof(BTNode));
    node->right = (BTNode*)malloc(sizeof(BTNode));
    node->left = node->right = NULL;
    return node;
}

/* Given the address of the root node of a binary tree, and a job, the function compare the stateID
 *   of the node at the address and the state attribute of the job to see if it's the correct node, 
 *   returning the address if so. Otherwise, the function recursively calls itself with the children
 *   of the node and the same job to check all the jobs in the tree.
 */
BTNode** getBTNode(BTNode** nodeAddr, Job* j){
    BTNode* node = *nodeAddr;
    if(node == NULL || j == NULL) return NULL;
    
    int i = strcmp(node->stateID, j->attrList[3]->data[0]);
    
    if(i == 0){
        return nodeAddr;
    }

    if(i > 0) {
        getBTNode(&node->left, j);
    } else {
        getBTNode(&node->right, j);
    }
}

/* Takes two nodes and uses strcmp to compare their stateIDs to check which is bigger or if they're equal. 
 *   Returns 1 if the second node is bigger, -1 if the first node is bigger, and 0 if they are equal.
 */
int compareBTNode(BTNode* n1, BTNode* n2){
    int i = strcmp(n1->stateID, n2->stateID);
    if(i > 0) return 1;
    if(i < 0) return -1;
    return 0;
}

/* Takes a node and a job uses strcmp to compare the stateID of the node with the state attribute of the job
 *   to check which is bigger or if they're equal. Returns 1 if the job is bigger, -1 if the node is bigger,
 *   and 0 if they are equal.
 */
int compareNodeToJob(BTNode* n, Job* j){
    int i = strcmp(n->stateID, j->attrList[3]->data[0]);
    if(i > 0) return 1;
    if(i < 0) return -1;
    return 0;
}

/* Prints the stateID and size of the jobList for a given node. 
 */
void printBTNode(BTNode* node){
    if(node == NULL) return;
    printf("%s (%d), ", node->stateID, node->jobList->size);
}

/* Initializes a binary tree object with memory and creates it's first node with the job given
 *   also increasing the size of the tree if the job is not null. Returns the newly created tree.
 */
BinaryTree* createBinaryTree( BinaryTree* bt, Job* j ) {
    bt = (BinaryTree*)malloc(sizeof(BinaryTree));     //allocate memory for the tree

    if(j == NULL){
        bt->size = 0; 
    } else {
        bt->root = createBTNode(j);
        bt->size = 1;
    }
    return bt;
}

/* Given the address of the root of a binary tree and a job, first checks if the job is NULL
 *   and throws a printed error if so, otherwise checks if the node is null and creates a node for
 *   the job at this place in the tree. If the node is not null but the stateID is null, also prints
 *   an error because this should not be able to happen. If stateID is not null, it compares it
 *   with the job's state attribute and decides which was to recurse through the tree or if there is already
 *   a node with that stateID. If the node exists already, the job is added to the jobList of the node.
 */
void insertInBinaryTree( BTNode** nodeAddr, Job* j ) {
    BTNode* node = *nodeAddr;
    if(j == NULL){
        printf("*Error: Insert in BT; Job is null.");
        return;   //return: no job to add
    }
    if(node == NULL){
        BTNode* newNode = createBTNode(j);              
        *nodeAddr = newNode;
        return;   //return: created new node for the job
    }
    if(node->stateID == NULL){
        printf("*Error: Insert in BT; stateID of node is null, could not compare to others.");
        return;   //return: no state to compare the node to others with
    }
    int i = strcmp(node->stateID, j->attrList[3]->data[0]);
    if(i > 0) {
        insertInBinaryTree(&node->left, j);
    } else if(i == 0) {
        node->jobList = insertInLinkedList(node->jobList, j);
        return;   //return: inserted job into previous node's LinkedList
    } else {
        insertInBinaryTree(&node->right, j);
    }
}  

/* Given the root node of a Binary tree, checks if the node is null as a base case, otherwise, compares
 *   the node to the job given to determine which was to recurse through the tree or if it's the correct
 *   node to remove the job from. If so and the list has more than 1 job, it will remove the job from the list
 *   and delete the node. Otherwise, it will remove the node depending on how many children the job has:
 *   for one child or no children, it returns either null or the child that isn't null to replace the node
 *   and for nodes with two children, it will replace the node's data with it's in-order successor and
 *   call itself to remove the in-order succesor node
 */
BTNode* removeFromBinaryTree(BTNode* root, Job* j){
    //first navigate to the node of the job's state
    if (root == NULL)
        return root;

    int i = compareNodeToJob(root, j);

    if (i > 0) root->left = removeFromBinaryTree(root->left, j);

    else if (i < 0) root->right = removeFromBinaryTree(root->right, j);
    
    else {                                                     // correct node is found:
        if(root->jobList->size != 1){                          // node with only one job in list, remove it
            root->jobList = removeFromLinkedList( root->jobList, j );
            return root;
        }
        if (root->left == NULL) {    
            BTNode* temp = root->right;                         // node with no left child 
            return temp;
        } else if (root->right == NULL) {                      // node with no right child
            BTNode* temp = root->left;
            return temp;
        }
        struct BTNode* temp = findSmallestBTNode(root->right); // node with two children: get the inorder successor
 
        // Copy the inorder successor's content to this node
        root->jobList = temp->jobList;
        root->stateID = temp->stateID;
 
        // Delete the inorder successor
        root->right = removeFromBinaryTree(root->right, temp->jobList->head->job);
    }
    return root;
}

/* Given a node it finds the smallest node by recursing left until the node's left child is null and
 *   then returns the node as the smallest node at that point in the tree.
 */
BTNode* findSmallestBTNode(BTNode* node){
    while(node->left != NULL){
        node = node->left;
    }
    return node;
}

/* Given a node in the binary tree, the function recurses through all of the nodes it can access, 
 *   and prints every job in the jobLists of those nodes. If given the root of the tree, this 
 *   prints all the jobs in the binary tree in alphabetical node order.
 */
void printBTInOrder( BTNode* node ) {
    if(node == NULL) return;

    printBTInOrder(node->left);
    printLinkedListJobs(node->jobList);
    printBTInOrder(node->right);
}

/* Given a node in the binary tree, the function recurses through all of the nodes it can access, 
 *   and prints every node's stateID and size.
 */
void printAllBTJob( BTNode* node ) {
    if(node == NULL) return;

    printAllBTJob(node->left);
    printBTNode(node);
    printAllBTJob(node->right);
}

/* Used to initialize the global variable LinkedList listOfJobs with all jobs matching the parameter Job* in the tree 
 *   accessible by the node passed as a parameter. It recurses through the tree and for each node's jobList it uses 
 *   compareJobs function on all jobs in the list. Because compareJobs can check if the job is a close or exact
 *   the match, the type provided determines if the list created is a list of exact (type=0) or close (type=1) 
 *   jobs. If the result of compareJobs matches the type, it is inserted int the global LinkedList variable
 *   listOfJobs. This function works in tandem with the getJobsInBT function.
 */
void findJobsInBT(BTNode* node, Job* j, int type){
    if(node == NULL || j == NULL) return;

    findJobsInBT(node->left, j, type);
    
    LLNode* curr = node->jobList->head;
    while(curr != NULL){
        if(compareJobs(j, curr->job) == type) {
            listOfJobs = insertInLinkedList(listOfJobs, curr->job);
        }
        curr = curr->next;
    }

    findJobsInBT(node->right, j, type);
}

/* This function's main job is to initialize and return the global variable listOfJobs using
 *   the createLinkedList function and findJobsInBT to initialize the variable, and finally it
 *   return it.
 */
LinkedList* getJobsInBT(BTNode* node, Job* j, int type){
    listOfJobs = createLinkedList(listOfJobs);
    findJobsInBT(node, j, type);
    return listOfJobs;
}