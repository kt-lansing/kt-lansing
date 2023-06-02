#include "FileHandler.h"

extern Job* createJob( Job* );
extern Job* addJobAttr( Job*, int, char* );
extern BinaryTree* createBinaryTree( BinaryTree* bt, Job* j );
extern void addToBinaryTree(BinaryTree* bt, Job* j);
extern LinkedList* getJobsInBT(BTNode* node, Job* j, int type);
extern void printAllBTJob( BTNode* node );

/*Initializes the global variable inFile for reading by trying to open
 *  the file with the name provided. Prints to stdout if file is still NULL
 */
void openInFile(char* name){
    inFile = fopen(name, "r");
    if(inFile == NULL){
        printf("Error: Could not open input file successfully\n");
    }
}

/*Initializes the global variable out File for writing by trying to open
 *  the file with the name provided. Prints to stdout if file is still NULL
 */
void openOutFile(char* name){
    outFile = fopen(name, "w");
    if(outFile == NULL){
        printf("Error: Could not open output file successfully\n");
    }
}

/* First, initializes the BinaryTree to return and while the global inFile has
 *   another line of data, the function determines whether or not to add that data
 *   as an attribute, create a new Job, or skip the line, depending on what the line
 *   number of the file is (which specifics the data's format). Once it reaches a line
 *   where all attributes have been initialized, it adds the Job created to the BinaryTree
 *   and once all data has been read, returns a pointer to the resulting BinaryTree
 */
BinaryTree* createBTFromInFile(){
    //idea: loop through all data in the file
    char* line = (char*)malloc(sizeof(char)*255);
    int lineNumber = 1;
    BinaryTree* bt = createBinaryTree(bt, NULL);
    Job* newJob = createJob(newJob);

    //while there is a next line in the file
    while(fgets(line, 255, inFile)){
        //every 10th line is a blank line between jobs, indicating where each job ends
        if(lineNumber % 10 == 0){
            //create a new job to start the next cycle of data input
            newJob = createJob(newJob);
        } else {
            //initialize the attribute, with lineNumer%10-1 as the index
            newJob = addJobAttr(newJob, lineNumber%10-1, line);

            // if it just created the contactInfo, the job has all its attributes and can be
            // added to the arrayList now
            if(lineNumber % 10 == 9) {
                addToBinaryTree(bt, newJob);
            }
        }
        lineNumber++;
    }
    
    return bt;
}

/* Checks if the BinaryTree* given is null and if so, creates the tree,
 *   and if not, inserts the Job* into the BinaryTree
 */
void addToBinaryTree(BinaryTree* bt, Job* j){
    if(bt == NULL){        //if binary tree is null, initialize it with the given job
        bt = createBinaryTree(bt, j);
    } else {
        insertInBinaryTree(&bt->root, j);
    }
}

/* Creates a LinkedList of all the files in the job database and prints out each job's
 *  attributes line by line to the location of the global outFile. The ouput format is 
 *  the exact same format that input files have.
 */
void writeToFile(LinkedList* jobsList){
    LLNode* curr = jobsList->head;
    int lineNumber = 1;
    while(curr != NULL){
        fflush(stdin);
        if(lineNumber%10 == 0){
            fputs("\n", outFile);
            curr = curr->next;
        } else {
            JobAttr* toPrint = curr->job->attrList[lineNumber%10-1];
            for(int i = 0; i < toPrint->size; i++){
                if(lineNumber%10-1 == 4 && i != toPrint->size-1){
                    fputs(toPrint->data[i], outFile);
                    fputs(" ", outFile);
                }else if(lineNumber%10-1 != 4 && i != toPrint->size-1) {
                    fputs(toPrint->data[i], outFile);
                    fputs(",", outFile);
                } else {
                    fputs(toPrint->data[i], outFile);
                }
            }
            fputs("\n",outFile);
        }
        lineNumber++;
    }
}

/* Closes the global file object ptrs inFile and outFile. Used at the end of the program.
*/
void closeFiles(){
    fclose(inFile);
    if(outFile != NULL) fclose(outFile);
}