#include "Program.h"

extern LinkedList* createLinkedList( LinkedList* list );
extern LinkedList* insertInLinkedList( LinkedList* list, Job* j );
extern void printLinkedListJobs( LinkedList* list );
extern Job* createJob( Job* j );
extern int compareJobs( Job* j1, Job* j2);
extern Job* addJobAttr( Job*, int, char* );
extern void printJob( Job* );
extern void printBTInOrder( BTNode* );
extern Job* modifyAttribute(Job* j, int index, char* data);
extern void openOutFile(char* name);
extern LinkedList* getJobsInBT(BTNode* node, Job* j, int type);
extern void writeToFile(LinkedList* jobsList);

/* Starts the interraction with the user. Includes a while loop that reads the users' commands until the exit command
 *   is given. Calls other Program.c functions depending on the command given with a switch structure. If the command
 *   is invalid, it calls the function printValidCommands and queries the user for another command.
 */
void startProgram(){
    if(bt == NULL) {
        printf("Error: BT not initialized. Please do so before continuing");
        return;
    }
    char firstParam;
    char secondParam;

    printf("Welcome to Katie's Job Bank 2.0! We've been recently updated (Yay!) Quit anytime by entering x.\n");
    while(firstParam != 'x'){
        printf(" - Please enter a command:\n");
        scanf(" %c", &firstParam);
        switch(firstParam){
            case 'p':
                printJobs();
                break;
            case 's':
                searchJobs();
                break;
            case 'l':
                printf("Inputted l. Please input second modifier (i, l, or t)\n");
                scanf(" %c", &secondParam);
                switch(secondParam){
                    case 'i':
                        listIndustry();
                        break;
                    case 'l':
                        listLocation();
                        break;
                    case 't':
                        listTitle();
                        break;
                }
                break;
            case 'a': 
                addJobs();
                break;
            case 'm': 
                modifyJobs();
                break;
            case 'r': 
                removeJobs();
                break;
            case 'w': 
                writeJobs();
                break;
            case 'x': 
                break;
            default: 
                printValidCommands();
        }
        printf("\n");
    }
    printf("Thank you for using Katie's job bank!\n");
}

/* Initalizes the global BinaryTree* bt that will be used throughout the program.
 *   Sets bt variable to the parameter BinaryTree* tree.
 */
void initializeBT(BinaryTree* tree){
    bt = tree;
}

/* Prints all valid program commands using printf.
 */
void printValidCommands(){
    printf("Please input a valid command. ");
    printf("Valid commands include: p, s, l (i, t, l), a, m, r, w, x\n");

}

/* Prints all jobs in the binary tree of jobs using the printBTInOrder function.
 */
void printJobs(){
    printBTInOrder( bt->root );
    printf("Printed all jobs in the database. See above for all jobs.\n");
    return;
}

/* Uses initializeParams function to create a job to search for in the database. For both exact
 *   and close attribute matches, the created LinkedLists of jobs from the getJobsInBT function, are printed.
 */
void searchJobs(){
    while ( (getchar()) != '\n');
    printf("\nSearching for Jobs in database\n");
    Job* j1 = initializeParams(0, 9);
    LinkedList* l1 = getJobsInBT(bt->root, j1, 0);
    LinkedList* l2 = getJobsInBT(bt->root, j1, 1);
    printSearchResults(l1, 0);
    printSearchResults(l2, 1);
    return;
}

/* Uses initializeParams function to create a job to search for in the database. For only 
 *   exact industry matches, the created LinkedLists of jobs from the getJobsInBT function is printed
 */
void listIndustry(){
    while ( (getchar()) != '\n');
    printf("\nSearching for jobs with matching Industry\n");
    Job* j1 = initializeParams(5, 6);
    LinkedList* l1 = getJobsInBT(bt->root, j1, 0);
    printSearchResults(l1, 0);
    return;
}

/* Manually creates a job (paramJob) and initializes it's attributes using paraList variable.
 *   This is done to account for the different inputted format of location that initializeParams does
 *   not account for. After job is created and for both exact and close  attribute matches, the created  
 *   LinkedLists of jobs from the getJobsInBT function, are printed.
 */
void listLocation(){
    while ( (getchar()) != '\n');
    paramJob = createJob( paramJob );
    paramList = (char**)malloc(sizeof(char*)*9);
    for(int k = 0; k < 9; k++) paramList[k] = (char*)malloc(sizeof(char)*255);

    printf("\nSearching for jobs with matching Location\n");
    printf(" - Enter the location to search for (format: [city] [state])\n");
    char* location = (char*)malloc(sizeof(char)*255);
    fgets(location, 255, stdin);
    char* token = strtok(location, " ");
    int i = 2;
    while( token != NULL){
        if(i > 3 ) break;
        strcpy(paramList[i], token);
        token = strtok(NULL, " ");
        i++;
    }
    for(int k = 0; k < 9; k++){
        if(k != 2 && k != 3) paramList[k] = "*";
        paramJob = addJobAttr(paramJob, k, paramList[k]);
    }
    LinkedList* l1 = getJobsInBT(bt->root, paramJob, 0);
    LinkedList* l2 = getJobsInBT(bt->root, paramJob, 1);
    printSearchResults(l1, 0);
    printSearchResults(l2, 1);
    return;
}

/* Uses initializeParams function to create a job to search for in the database. For only 
 *   exact title matches, the created LinkedLists of jobs from the getJobsInBT function is printed
 */
void listTitle(){
    while ( (getchar()) != '\n');
    printf("\nSearching for jobs with matching Title\n");
    Job* j1 = initializeParams(0, 1);
    LinkedList* l1 = getJobsInBT(bt->root, paramJob, 0);
    printSearchResults(l1, 0);
    return;
}

/* Uses initializeParams function to create a job to add into the database using insertInBinaryTree function.
 *   Checks to make sure the job has a state location so that it can be successfully inserted into the global binary tree.
 *   Finally, prints the job that was added to the database.
 */
void addJobs(){
    while ( (getchar()) != '\n');
    printf("\nAdding job to database\n");
    Job* j1 = initializeParams(0, 9);
    while(strcmp(j1->attrList[3]->data[0], "*") == 0) {
        printf("Warning: job must have a State Location to be inserted into the database. Please enter a state for your job:\n");
        fgets(paramList[3], 255, stdin);
        j1 = modifyAttribute(j1, 3, paramList[3]);
    }
    insertInBinaryTree(&bt->root, j1);
    printf("\nSucessfully inserted job into database:\n\n");
    printJob(j1);
    return;
}

/* Uses initializeParams function to create a job to search for in the database. If the job attributes of title,
 *   company name, or industry are empty, uses invalidParam function to prompt for input. Uses getJobsInBT function to
 *   get all exact matches in the database. If no matches, it returns. If more than one match, it restarts function. If
 *   exactly one match, it uses initializeParams function to create a second job; for this job, if any attributes are wildcards
 *   it copies the previous attribute. After job is created, it deletes the previous job from the database, and inserts the new one.
 */
void modifyJobs(){
    while ( (getchar()) != '\n');
    printf("\nModifying a job in the database. First search for the job to modify.\n");
    printf("Note: search must include a title, company name, and industry to be found in database.\n");
    Job* j1 = initializeParams(0, 9);
    //if title, company name, or industry is empty, prompt again
    j1 = invalidParam(j1, 0);
    j1 = invalidParam(j1, 1);
    j1 = invalidParam(j1, 5);
    printJob(j1);

    LinkedList* searchResults = getJobsInBT(bt->root, j1, 0);
    if(searchResults->head == NULL) printf("Could not find any excatly matching job to modify.\n");
    else {
        if(searchResults->size != 1) {
            printf("Your search found more than one job to modify. Please retry with more specific job info.\n");
            modifyJobs();
        }
        Job* toRemove = searchResults->head->job;
        bt->root = removeFromBinaryTree(bt->root, toRemove);
        printf("Please enter the info you'd like to change your job to or press enter if you'd like to keep the previous info.\n");
        Job* toAdd = initializeParams(0, 9);
        for(int i = 0; i < 9; i++){
            if(strcmp(toAdd->attrList[i]->data[0], "*") == 0) toAdd->attrList[i] = toRemove->attrList[i];
        }
        printf("Your job has been modified to the following:\n");
        printJob(toAdd);
        insertInBinaryTree(&bt->root, toAdd);
    }
    return;
}

/* Uses initializeParams function to create a job to search for in the database. If the job attributes of title,
 *   company name, state or city location, or industry are empty, uses invalidParam function to prompt for input. Uses getJobsInBT
 *   function to get all exact matches in the database. If no matches, it returns. If more than one match, asks for the user to 
 *   either cancel, or delete all jobs. If exactly one match or user wants to delete all matches, it removes the selected job(s)
 *   from the global binary tree.
 */
void removeJobs(){
    while ( (getchar()) != '\n');
    printf("\nRemoving a job in the database. First search for the job to remove.\n");
    Job* j1 = initializeParams(0, 4);
    printf(" - Enter %s:\n", paramJob->attrList[5]->name);
    paramList[5] = (char*)malloc(sizeof(char)*255);
    fgets(paramList[5], 255, stdin);
    j1 = addJobAttr(j1, 5, paramList[5]);

    //if title, company name, state or cityLoc, or industry is empty, invalid
    j1 = invalidParam(j1, 0);
    j1 = invalidParam(j1, 1);
    j1 = invalidParam(j1, 2);
    j1 = invalidParam(j1, 3);
    j1 = invalidParam(j1, 5);

    LinkedList* searchResults = getJobsInBT(bt->root, j1, 0);
    if(searchResults->head == NULL) printf("Could not find any matching job.");
    else {
        if(searchResults->size != 1) {
            printf(" - Your search found more than one job to modify. Please enter 1 to cancel or 0 to delete all jobs selected. \n - Number of jobs found: %d\n", searchResults->size);
            int choice = -1;
            while(choice != 0 && choice != 1){
                scanf(" %d", &choice);
            }
            if(choice == 1) {
                return;
            }
        } else {
            printf("\nYour search found the following job:\n");
            printJob(searchResults->head->job);
        }
        LLNode* curr = searchResults->head;
        printf("\nRemoving %d job(s) from database.\n", searchResults->size);
        while(curr != NULL){
            bt->root = removeFromBinaryTree( bt->root, curr->job );
            curr = curr->next;
        }
    }
    return;
}

/* First, asks user for a filename to output all jobs to. If the inputed string does not include .txt 
 *   the function adds .txt to the end of the string and uses openOutFile to open the file with the string
 *   as the name. A job with all wildcard attributes is made to create a LinkedList of all the jobs in the
 *   global binary tree using the getJobsInBt function. Finally, the LinkedList is passed to the writeToFile function
 *   to be written to the output file.
 */
void writeJobs(){
    while ( (getchar()) != '\n');
    printf("\nWriting all database jobs to a file.\n");
    printf("Please input the name of the file to output database to:\n");
    char* fileName = (char*)malloc(sizeof(char)*255);
    scanf("%s", fileName);
    while ( (getchar()) != '\n');
    fileName = formatParam(fileName);
    if(strstr(fileName, ".txt") == NULL){
        strncat(fileName, ".txt ", 4);
    }
    printf("\nPrinting to file: %s\n", fileName);
    openOutFile(fileName);
    
    Job* j = createJob(j);
    for(int i = 0; i < 9; i++) {
        j = addJobAttr(j, i, "*");
    }
    LinkedList* allJobs = getJobsInBT(bt->root, j, 0);
    writeToFile(allJobs);

}

/* First checks which types of LinkedList is to be printed; if parameter int is 0, it's an exact
 *   matching list, if parameter int is 1, it's a close matching list. Checks if the list is empty 
 *   and prints a message accordingly or prints the LinkedList provided using the printLinkedListJobs function
 *   Str and type variables are use for output messages only.
 */
void printSearchResults(LinkedList* list, int type){
    char str[6];
    if(type == 0) strcpy(str, "exact");
    if(type == 1) strcpy(str, "close");
    if(list->head == NULL) printf("\nCould not find any %s jobs that match.\n\n", str);
    else {
        printf("\nYour search has %d %s match(es):\n\n", list->size, str);
        printLinkedListJobs(list);
    }
}

/* Given the parameters for a starting index (included) and ending index (excluded) for a job's attributes,
 *   it initializes all of the attributes outside of the parameters' indexing range to wildcards, and initializes
 *   the ones inside the range to taking input from the user. Finally, creates a job out of the initialized parameters
 *   and returns the created job.
 */
Job* initializeParams(int startInd, int endInd){
    paramJob = createJob( paramJob );                           //create job to add attributes to
    paramList = (char**)malloc(sizeof(char*)*9);
    for(int i = 0; i < 9; i++) {
        paramList[i] = (char*)malloc(sizeof(char)*255);
        if(i < startInd || i >= endInd) {                       //initialize wildcards for excluded attributes 
            paramList[i] = "*";                                
            paramJob = addJobAttr(paramJob, i, paramList[i]);
        }
    }
    for(int i = startInd; i < endInd; i++) {                    //set user input for all included attributes
        printf(" - Enter %s:\n", paramJob->attrList[i]->name);

        fgets(paramList[i], 255, stdin);
        paramJob = addJobAttr(paramJob, i, paramList[i]);
    }
    return paramJob;
}


/*  Uses the job parameter and index parameter to check the attribute of said job at the index to see if the user entered nothing 
 *    and therefor a wildcard symbol was set as the attribute. If so, it outputs to the user that this index has to be filled.
 *    It then queries the user for an input until they input something and sets the attribute to the string inputted.
 */
Job* invalidParam(Job* j, int i){
    while(strcmp(j->attrList[i]->data[0], "*") == 0 ) {
        printf(" - Warning: search must have a %s. Please enter a %s for your search\n", j->attrList[i]->name, j->attrList[i]->name);
        fgets(paramList[i], 255, stdin);
        j = modifyAttribute(j, i, paramList[i]);
    }
    return j;
}

/* Creates a copy of the string parameter and uses strcspn to find and remove
 *   the first instance of a newline character, returning the newly modified string
 */
char* formatParam( char* str ){
    char* copyStr;
    copyStr = str;
    strcpy(copyStr, str);
    copyStr[strcspn(copyStr, "\n")] = '\0';
    return copyStr;
}