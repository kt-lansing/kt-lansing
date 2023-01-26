#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Job.h"
#include "BinaryTree.h"
#include "LinkedList.h"


/*FileHandler summary:
 *  Handles all actions related to the file inputting and outputting the jobs.
 *    Most importantly, creates the Jobs and the BinaryTree to be used by the
 *    program from the inFile's data.
 *  Major changes from v1: File Handler no longer creates an ArrayList, instead it creates
 *    a BinaryTree. Writing data to a file is now possible.
 */

FILE* inFile;         //pointer to the file to read the data from
FILE* outFile;        //pointer to the file to write the data to

BinaryTree* bt;       //pointer to the created BinaryTree

/* @brief Initializes the inFile variable as the file with its name equal to the parameter's string
 * @param char* name: char pointer of the name of the file to initialize
 */
void openInFile( char* );

/* @brief Initializes the outFile variable as the file with its name equal to parameter's string
 * @param char* name: char pointer of the name of the file to initialize
 */
void openOutFile(char* );

/* @brief Creates a BinaryTree* from the data in the global inFile variable/
 * @returns pointer to the BinaryTree* created from the data
 */
BinaryTree* createBTFromInFile();

/* @brief Adds a Job* to a BinaryTree* 
 * @param BinaryTree* tree: pointer to BinaryTree where Job* will be added
 * @param Job* j: pointer to Job to add to the tree
 */
void addToBinaryTree(BinaryTree*, Job*);

/* @brief Writes the data in the provided LinkedList* to the output file
 * @param LinkedList* jobsList: list 
 */
void writeToFile(LinkedList*);

/* @brief Closes all open global FILE variables (i.e. inFile and outFile)
 */
void closeFiles();

#endif // FILEHANDLER_H