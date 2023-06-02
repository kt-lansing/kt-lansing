#include "unitTest.h"

//FileHandler.c fnx:
extern void openInFile(char* name);
extern BinaryTree* createBTFromInFile();
extern void addToBinaryTree(BinaryTree* bt, Job* j);
//Job.c fnx:
extern Job* createJob();
extern Job* addJobAttr( Job* j, int index, char* data);
extern Job* modifyAttribute(Job* j, int index, char* data);
//BinaryTree.c fnx:
extern BTNode* createBTNode(Job* j);
extern void printBTNode(BTNode* node);
extern int compareBTNode(BTNode* n1, BTNode* n2);
extern BinaryTree* createBinaryTree( BinaryTree* bt, Job* j );
extern void insertInBinaryTree( BTNode** node, Job* j );
extern void printBTInOrder( BTNode* node );
extern BTNode** getBTNode(BTNode** nodeAddr, Job* j);
extern BTNode* findSmallestBTNode(BTNode* node);
extern BTNode* findLargestBTNode(BTNode* node);
extern BTNode* removeFromBinaryTree( BTNode* nodeAddr, Job* j);
extern void printAllBTJob( BTNode* node );
extern void findJobsInBT(BTNode* node, Job* j, int type);
extern LinkedList* getJobsInBT(BTNode* node, Job* j, int type);
//LinkedList.c fnx:
extern LinkedList* removeFromLinkedList( LinkedList* list, Job* j );
//Program.c fnx:
extern void startProgram();
extern Job* initializeParams(int startInd, int endInd);
extern void initializeBT();
extern char* formatParam( char* );
extern void printJobs();
extern void searchJobs();
extern void listIndustry();
extern void listLocation();
extern void listTitle();
extern void addJobs();
extern void modifyJobs();
extern void removeJobs();
extern void writeJobs();

void testStartProgram(){
    startProgram();
}

void testJobCreation(){
    openInFile("one_job.txt");
    Job* j1 = createJob(j1);

    printf("Testing Job Creation\n");

    JobAttr** ptr = j1->attrList;                   //create a pointer to the 2D array
    for(int i = 0; i < 9; i++){          
        JobAttr* jAptr = *ptr;                      //create a pointer to the jobAttr in the 2D array
        printf("Name of attr: %s\n", jAptr->name);   //print out the 
        ptr++;
    }
    
    printf("Passes Job Creation test");   
}

void testAddAttribute(){
    Job* j1 = createJob(j1);

    j1 = addJobAttr( j1, 4, "90000 100000\n");
     
    JobAttr* jAttr = j1->attrList[4];

    j1 = addJobAttr( j1, 0, "software engineer\n");
    j1 = addJobAttr( j1, 7, "Git,Javascript\n");
    j1 = addJobAttr( j1, 6, "beta,alpha,gamma,delta\n");    //sorting not working... trying to change sortAttr()

    printJob(j1);
}

void testFileHandler(){
    openInFile("jobs.txt");
    //createJobsFromInFile();

}

void testBTCreation(){
    Job* j1 = createJob(j1);
    Job* j2 = createJob(j2);
    Job* j3 = createJob(j3);
    Job* j4 = createJob(j4);

    
    j1 = addJobAttr( j1, 3, "CA\r\n");
    j2 = addJobAttr( j2, 3, "VA\r\n");
    j3 = addJobAttr( j3, 3, "AL\r\n");
    j4 = addJobAttr( j4, 3, "AL\r\n");

    BTNode* b1 = createBTNode(j1);
    BTNode* b2 = createBTNode(j2);
    BTNode* b3 = createBTNode(j3);
    BTNode* b4 = createBTNode(j4);
    
    printf("%d\n", compareBTNode(b1, b2));  //CA vs VA, CA is bigger = negative
    printf("%d\n", compareBTNode(b2, b3));  //VA vs AL, AL is bigger = positive
    printf("%d\n", compareBTNode(b3, b1));  //AL vs CA, AL is bigger = negative
    printf("%d\n", compareBTNode(b3, b4));  //AL vs AL, AL = AL = zero


}

void testBTInsert(){
    Job* j1 = createJob(j1);
    Job* j2 = createJob(j2);
    Job* j3 = createJob(j3);
    Job* j4 = createJob(j4);

    j1 = addJobAttr( j1, 3, "CA\r\n");
    j2 = addJobAttr( j2, 3, "VA\r\n");
    j3 = addJobAttr( j3, 3, "AL\r\n");
    j4 = addJobAttr( j4, 3, "AL\r\n");

    BinaryTree* bt = createBinaryTree(bt, j1);
    insertInBinaryTree(&bt->root, j2);
    insertInBinaryTree(&bt->root, j3);
    insertInBinaryTree(&bt->root, j4);

    printBTInOrder(bt->root);
}

void testBTInsertWithFile(){
    openInFile("jobs.txt"); //works with full file!
    BinaryTree* bt = createBTFromInFile();

    printBTInOrder(bt->root);
}

void testJobCompare(){
    Job* j1 = createJob(j1);
    Job* j2 = createJob(j2);
    Job* j3 = createJob(j3);
    Job* j4 = createJob(j4);
    Job* j5 = createJob(j4);

    //job 1
    j1 = addJobAttr( j1, 3, "CA\r\n");

    //job 2
    j2 = addJobAttr( j2, 3, "VA\r\n");

    //job 3
    j3 = addJobAttr( j3, 3, "AL\r\n");
    j3 = addJobAttr( j3, 7, "katie,item\r\n");

    //job 4
    j4 = addJobAttr( j4, 3, "AL\r\n");
    j4 = addJobAttr( j4, 7, "pizza,item\r\n");

    //job 5
    j5 = addJobAttr( j5, 3, "AL\r\n");
    j5 = addJobAttr( j5, 7, "pizza,item\r\n");

    printf("1 vs 2: %d\n", compareJobs(j1, j2));    //CA vs VA -> -1
    printf("2 vs 3: %d\n", compareJobs(j2, j3));    //VA vs AL -> -1
    printf("3 vs 4: %d\n", compareJobs(j3, j4));    //AL vs AL -> 1

    j3 = addJobAttr( j3, 0, "software engineer\r\n");
    j4 = addJobAttr( j4, 0, "Software engineer\r\n");
    j5 = addJobAttr( j5, 0, "Software engineer\r\n");

    printf("3 vs 4: %d\n", compareJobs(j3, j4));    //AL vs AL -> 1
    printf("3 vs 4: %d\n", compareJobs(j3, j4));    //AL vs AL -> 1
    printf("4 vs 5: %d\n", compareJobs(j4, j5));    //AL vs AL -> 0

    j5 = modifyAttribute(j5, 3, "VA");
    j5 = modifyAttribute(j5, 2, "VA");
    j5 = modifyAttribute(j5, 1, "");
    j5 = modifyAttribute(j5, 0, "chef");
    printf("4 vs 5: %d\n", compareJobs(j4, j5));    //should be -1

}

void testDeleteFromLL(){
    //first we must fix compareJobs
    openInFile("jobs.txt"); //works with full file!
    BinaryTree* bt = createBTFromInFile();

    Job* j1 = createJob(j1);
    j1 =  addJobAttr( j1, 0, "george washington impersonator\r\n");
    j1 =  addJobAttr( j1, 1, "The Mount Vernon Company\r\n");
    j1 =  addJobAttr( j1, 2, "Mt. Vernon\r\n");
    j1 =  addJobAttr( j1, 3, "VA\r\n");
    j1 =  addJobAttr( j1, 4, "30000 60000\r\n");
    j1 =  addJobAttr( j1, 5, "entertainment\r\n");
    j1 =  addJobAttr( j1, 6, "historical knowledge of george washington,interpretive acting skills\r\n");
    j1 =  addJobAttr( j1, 7, "george washington costume\r\n");
    j1 =  addJobAttr( j1, 8, "jobs@mountvernon.org\r\n");
    printJob(j1);

    BTNode** b1Addr = getBTNode(&bt->root, j1);   //check if working or no
    BTNode* b1 = *b1Addr;

    printLinkedListTitles(b1->jobList);
    printf("\nRemoving GW JOB\n"); //middle job
    b1->jobList = removeFromLinkedList(b1->jobList, j1);
    printLinkedListTitles(b1->jobList);
    printf("\n");

    j1 =  modifyAttribute( j1, 0, "professor of computer science\r\n");
    j1 =  modifyAttribute( j1, 1, "George Mason University\r\n");
    j1 =  modifyAttribute( j1, 2, "Fairfax\r\n");
    
    j1 =  modifyAttribute( j1, 4, "60000 80000\r\n");
    j1 =  modifyAttribute( j1, 5, "academia\r\n");
    j1 =  modifyAttribute( j1, 6, "PhD in computer science\r\n");
    j1 =  modifyAttribute( j1, 7, "java,c++\r\n");
    j1 =  modifyAttribute( j1, 8, "cs@gmu.edu\r\n");

    printLinkedListTitles(b1->jobList);
    printf("\nRemoving CSPROF JOB\n"); //middle job
    b1->jobList = removeFromLinkedList(b1->jobList, j1);
    printLinkedListTitles(b1->jobList);
    printf("\n");

    j1 =  modifyAttribute( j1, 0, "System Analyst with Facets\r\n");
    j1 =  modifyAttribute( j1, 1, "Cognizant\r\n");
    j1 =  modifyAttribute( j1, 2, "Norfolk\r\n");
    
    j1 =  modifyAttribute( j1, 4, "100000 150000\r\n");
    j1 =  modifyAttribute( j1, 5, "Data Analytics\r\n");
    j1 =  modifyAttribute( j1, 6, "Work experience required: 10 - 14yrs,Skill set: PL/SQL,ANSI SQL,TSQL and Facets Domain skill\r\n");
    j1 =  modifyAttribute( j1, 7, "Liaison between the business team and development team in converting the business requirement to facets specific requirements /design\r\n");
    j1 =  modifyAttribute( j1, 8, "CareersNA2@cognizant.com\r\n");

    printLinkedListTitles(b1->jobList);
    printf("\nRemoving SAwF JOB\n"); //middle job
    b1->jobList = removeFromLinkedList(b1->jobList, j1);
    printLinkedListTitles(b1->jobList);
}

void testDeleteFromBT(){
    openInFile("jobs.txt"); //works with full file!
    BinaryTree* bt = createBTFromInFile();
    Job* j1 = createJob(j1);
    Job* j3 = createJob(j3);
    Job* j4 = createJob(j4);
    Job* j2 = createJob(j2);
    for(int i = 0; i < 9; i++){
        j1 = addJobAttr(j1, i, "");
        j3 = addJobAttr(j3, i, "");
        j4 = addJobAttr(j4, i, "");
    }
    j1 = modifyAttribute(j1, 3, "MA");
    j1 = modifyAttribute(j1, 0, "specialty metal salesman");

    j3 = modifyAttribute(j3, 3, "NJ");
    j3 = modifyAttribute(j3, 0, "chemical engineer");

    j4 = modifyAttribute(j4, 3, "FL");
    j4 = modifyAttribute(j4, 0, "line cook");
    //printJob(j1);
    
    j2 = modifyAttribute(j2, 0, "dentist");
    j2 = modifyAttribute(j2, 1, "Clean Tooth");
    j2 = modifyAttribute(j2, 2, "San Francisco");
    j2 = modifyAttribute(j2, 3, "CA");
    j2 = modifyAttribute(j2, 4, "125000 145000");
    j2 = modifyAttribute(j2, 5, "healthcare");
    j2 = modifyAttribute(j2, 6, "good judgment,critical thinking");
    j2 = modifyAttribute(j2, 7, "organization,professionalism");
    j2 = modifyAttribute(j2, 8, "info@cleantooth.com");
    //printJob(j2);
    //printf("j1 and j2: %d\n", compareJobs(j1, j2));
    //printBTInOrder(bt->root);
    //printf("Smallest Node: ");
    //printBTNode(findSmallestBTNode(bt->root));
    //printf("Largest Node: ");
    //printBTNode(findLargestBTNode(bt->root));
    //these two functions 
    printf("BT: %s\n", toStringBinaryTree(bt));
    /* PARENT FNX TESTING
    j1 = modifyAttribute(j1, 3, "FL");
    j1 = modifyAttribute(j1, 0, "dentist");
    BTNode* node = getBTNode(bt->root, j1);
    printBTNode(node);
    BTNode* nodeP = getBTParent(bt->root, j1); //seg fault when parent = root
    printBTNode(nodeP);
    */
    //bt->root = removeFromBinaryTree(bt->root, j2);
    //printBTInOrder(bt->root);
    printBTInOrder(bt->root);
    bt->root = removeFromBinaryTree(bt->root, j1);  //remove CA *good
    printf("\n\n");
    printBTInOrder(bt->root);
    bt->root = removeFromBinaryTree(bt->root, j2);  //remove MA *failed
    printf("\n\n");
    printBTInOrder(bt->root);
    bt->root = removeFromBinaryTree(bt->root, j3);  //remove NJ *good
    printf("\n\n");
    printBTInOrder(bt->root);
    bt->root = removeFromBinaryTree(bt->root, j4);  //remove FL *good
    printf("\n\n");
    printBTInOrder(bt->root);

}

void testSearch(){
    searchJobs();
}

void testLists(){
    listLocation();
    listIndustry();
    listTitle();
}

void testAdd(){
    addJobs();
}

void testModify(){
    modifyJobs();
}

void testRemove(){
    removeJobs();
}

void testCommands(){
    openInFile("jobs_lite.txt"); //works with full file!
    BinaryTree* bt = createBTFromInFile();
    initializeBT(bt);
    //testSearch();
    //testLists();
    //testAdd();
    //testModify(); //could use more testing
    //testRemove();
    writeJobs();
}

void testProgram(){
    
}



void main(){
    testProgram();
}
