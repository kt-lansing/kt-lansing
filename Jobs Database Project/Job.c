#include "Job.h"

/* Allocates memory for one Job, and itializes the list of attributes that will be filled
 *   in once they are created. Also, allocates memory for each JobAttr in the attrList and
 *   assigns names to each index in the list
 */
Job* createJob( Job* j ){
    j = (Job*)malloc(sizeof(Job));

    j->attrList = (JobAttr**)malloc(sizeof(JobAttr*)*9);    //allocate space for 9 job attributes in list
    JobAttr** ptr = j->attrList;

    for(int i = 0; i < 9; i++){                             //allocate memory and assign name for each attribute      
        JobAttr* jAttr = (JobAttr*)malloc(sizeof(JobAttr)); //create the attribute
        jAttr->name = getAttrName(i);
        jAttr->size = -1;
        jAttr->data = NULL;
        *ptr = jAttr;
        ptr++;
    }
    return j;
}

/* Given a number, return the string of the attribute name that this number corresponds to in a
 *   job's attribute list. If the number is not 0-9, it returns NULL. Used by createJob and modifyAttribute fnx.
 */
char* getAttrName(int ind){
    
    char* name = (char*)malloc(sizeof(char)*12);

    if(ind == 0){
        strcpy(name, "jobTitle"); 
    }else if(ind == 1){
        strcpy(name, "compName"); 
    }else if(ind == 2){
        strcpy(name, "cityLoc"); 
    }else if(ind == 3){
        strcpy(name, "stateLoc"); 
    }else if(ind == 4){
        strcpy(name, "salaryRange"); 
    }else if(ind == 5){
        strcpy(name, "industry"); 
    }else if(ind ==6){
        strcpy(name, "reqSkill"); 
    }else if(ind == 7){
        strcpy(name, "desSkill"); 
    }else if(ind == 8){
        strcpy(name, "contactInfo"); 
    } else {
        name = NULL;
    }
    return name;
}

/* Gets the JobAttr of the given index in the given Job's attrList. First checks if the given data corresponds to a
 *   wildcard character, and initializes the attr and sets data to the * character. Otherwise, it allocates memory for the
 *   attributes data, removes any newline characters (\n and \r), and initializes the attributes size and data.
 */
Job* addJobAttr( Job* j, int index, char* data){
    JobAttr* jAttr = j->attrList[index];                    //get the correct attribute inside attribute list using index
    
    //if the data is empty, it becomes a wildcard spot
    if(strcmp(data, "\n") == 0 || strcmp(data, "") == 0 || strcmp(data, "\r\n") == 0 || strcmp(data, "*") == 0){
        jAttr->data = (char**)malloc(sizeof(char*));
        jAttr->data[0] = (char*)malloc(sizeof(char));
        jAttr->data[0] = "*";
        jAttr->size = 0;
        return j;
    }
    char* str = (char*)malloc(sizeof(char)*255);
    strcpy(str, data);
    if(strchr(str, '\n') != 0 || strchr(str, '\r') != 0){   //remove return characters (for windows, this results in \r and \n)
        char* checkNewLine = str;
        strcpy(checkNewLine, str);
        checkNewLine[strcspn(checkNewLine, "\n")] = '\0';
        checkNewLine[strcspn(checkNewLine, "\r")] = '\0';
        strcpy(str, checkNewLine);
    }
    if(index == salaryRange){                               //if the attribute is the salaryRange, do something specific with strtok
        jAttr->data = (char**)malloc(sizeof(char*)*2);
        jAttr->data[0] = (char*)malloc(sizeof(char)*255);
        jAttr->data[1] = (char*)malloc(sizeof(char)*255);
        char* token = strtok(str, " ");
        strcpy(jAttr->data[0], token);
        token = strtok(NULL, "\n");
        if(token != NULL) strcpy(jAttr->data[1], token);
        jAttr->size = 2;
        return j;
    }
    int arrayLen = calcDataLength(str);                     //For all other attributes, calculate length of the data array to create
    jAttr->size = arrayLen;
    jAttr->data = (char**)malloc(sizeof(char*)*arrayLen);   //create 2d data array using strtok
    char* token = strtok(str, ",");

    for(int i = 0; i < arrayLen; i++){
        jAttr->data[i] = (char*)malloc(sizeof(char)*(strlen(data)+1)); 
        strcpy(jAttr->data[i], token);
        token = strtok(NULL, ",");
    }
    jAttr = sortAttr(jAttr);                                //sort the attribute's data in alphabetical order
    return j;
}

/* Counts the number of commas in a given string to be used as data of a JobAttr.
 *   Returns the number of commas plus one to determine how big the 2D array should be
 *   for the data of the attribute. Used by addJobAttr function
 */
int calcDataLength(char* str){
    char c = ',';
    int count = 0;

    for(int i=0; str[i]; i++) {
    	if(str[i] == c ) {
          count++;
		}
 	}
    return count+1;
}

/* Given a job, an atrribute index, and a string of data, modify one of the attributes at said index in the 
 *   job's attribute list. Specifically, recreate the attribute with the new data passed to the function and
 *   return the modified job.
 */
Job* modifyAttribute(Job* j, int index, char* data){
    j->attrList[index] = (JobAttr*)malloc(sizeof(JobAttr)); //create the attribute
    j->attrList[index]->name = getAttrName(index);
    j->attrList[index]->size = -1;
    j->attrList[index]->data = NULL;
    j = addJobAttr(j, index, data);
    return j;
}

/* Loops through the attrList of each job and uses the printAttr function to print each 
 *   JobAttr's data 
 */
void printJob( Job* j ){
    for(int i = 0; i < 9; i++){
        JobAttr* jAttr = j->attrList[i];
        printAttr(jAttr);
    }
}

/* Prints all strings in the 2D char array, data, of the JobAttr passed to the function.
 */
void printAttr( JobAttr* jA){
    char** arrayPtr = jA->data;
    int size = jA->size;
    if(size == 1 || size == 0) {
        printf("%s\n", jA->data[0]);
    }else if (size == -1){
        printf(" not initialized.\n");
    } else {
        for(int i = 0; i < size; i++){
            if(i != size -1 ) {
                printf("%s, ", *arrayPtr);
                arrayPtr++;
            } else {
                printf("%s\n", *arrayPtr);
            }
        }
    }
}

/* Compares all strings in the 2D char array, data, of a JobAttr passed to the function and if the next one
 *    is smaller alphabetically, the function swaps the indicies of the strings to sort the data
 */
JobAttr* sortAttr( JobAttr* jA ){
    int s = jA->size;
    char* temp = (char*)malloc(sizeof(char)*255);
    if(s == 1) return jA;
    for(int i = 0; i < s; i++){
        for(int j = 0; j < s-1; j++){
            if(strcmp(jA->data[i], jA->data[j]) < 0){
                strcpy(temp, jA->data[i]);
                strcpy(jA->data[i], jA->data[j]);
                strcpy(jA->data[j], temp);
            }
        }
    }
    return jA;
}

/* Compares each attribute of two Jobs to each other using compareAttr() function and determines if the two 
 *   jobs are exact matches, close matches, or not matches using two boolean flags that change depending
 *   on the criteria given by the project description.
 */
 
int compareJobs( Job* j1, Job* j2){
    bool isExactMatch = true;
    bool isCloseMatch = true;

    for(int i = 0; i < 9; i++){     //compare all attributes 
        int isMatch = compareAttr(j1->attrList[i], j2->attrList[i]);
        if(isMatch != 0) isExactMatch = false;
        if(i == jobTitle || i == compName || i == stateLoc){
            if(isMatch != 0) isExactMatch = isCloseMatch = false;
        }
        if(i == reqSkill || i == desSkill){
            if(isMatch == -1) isExactMatch = isCloseMatch = false;
            if(isMatch == 1) isExactMatch = false;
        }
    }
    if(isExactMatch) return 0;      //if the jobs are an exact match, return 0
    if(isCloseMatch) return 1;      //if the jobs are a close match, return 1
    return -1;                      //if the jobs do not match, return -1
}


/* Compares two JobAttr's by comparing their data arrays and keeps track of the number of times
 *   the arrays match. Determines if the two JobAttr's are close or exact matches depending on 
 *   the amount of each type of matches.
 */
int compareAttr( JobAttr* jA1, JobAttr* jA2 ){
    if(jA1->data == NULL && jA2->data == NULL) return 0;                            //if both null, they are the same
    else if (jA1->data == NULL || jA2->data == NULL) return 1;                      //if one is null, they are different
    if(strcmp(jA1->data[0], "*") == 0 || strcmp(jA2->data[0], "*") == 0) return 0;  //if the wildcard symbol is present, they are the same
    
    int numMatches = 0;
    int exactMatches = 0;
    int innerSize = jA1->size;
    int outerSize = jA2->size;
    bool sizeMatch = false;
    if(innerSize == outerSize) sizeMatch = true;

    for(int i = 0; i < innerSize; i++){                         //check all cases of the two data arrays
        for(int j = 0; j < outerSize; j++){
            if(i == j && strcasecmp(jA1->data[i], jA2->data[j]) == 0){
                exactMatches++;
                numMatches++;
            } else if(strcasecmp(jA1->data[i], jA2->data[j]) == 0){
                numMatches++;
            }
        }
    }

    if(sizeMatch && innerSize == exactMatches) return 0;        //exact match returns 0
    else if(numMatches != 0)  return 1;                         //close match returns 1
    return -1;                                                  //not a match returns -1
}