#ifndef PROGRAM_H
#define PROGRAM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Job.h"
#include "LinkedList.h"
#include "BinaryTree.h"
#include "FileHandler.h"

/* Program Summary: 
 *   Includes the most high-level functionality of the program and handles interactions
 *     between the user and the program. Most functions correspond to a command.
 *   Major changes from v1: the structure of startProgram has been reworked and the main
 *     data structure is now a Binary Tree. More commands and corresponding functions added.
 */

char** paramList;           //List of parameters for temporary jobs that are created to match to during searches
Job* paramJob;              //A job with attributes created from the paramList and used to match to Jobs in the data structures
BinaryTree* bt;             //Stores the job array created by the main function & passed in by the function initializeBT()

/* @brief starts the "program", i.e. enters the main while loop of the program where
 *   the user inputs commands and the function calls other Program.c functions to interact with the
 *   data structures.
 */
void startProgram();

/* @brief initializes the global variable bt which is the Binary Tree data structure that will be used throughout the program
 * @param BinaryTree* tree; the binary tree that will be set as the global bt variable
 */
void initializeBT( BinaryTree*);

/* @brief prints all valid commands of the program that the user can input
*/
void printValidCommands();

/* @brief function for "p" command: prints all jobs in the database
*/
void printJobs();

/* @brief function for "s" command: searches for a job in the database given
 *   parameters from the user and returns all close and exactly matching jobs.
 *   Close jobs are based on the project description.
 */
void searchJobs();

/* @brief function for "l i" command: searches for a job in the database given
 *   an industry from the user and returns all matching jobs. 
 */
void listIndustry();

/* @brief function for "l l" command: searches for a job in the database given
 *   a location from the user and returns all close and exactly matching jobs.
 *   Close jobs match the state but not the city.
 */
void listLocation();

/* @brief function for "l t" command: searches for a job in the database given
 *   a title from the user and returns all matching jobs.
 */
void listTitle();

/* @brief function for "a" command: queries user for parameters for a new job and
 *   creates a job from those parameters, adding it to the database.
 *   State location is a required parameter for the job addition.
 */
void addJobs();

/* @brief function for "m" command: queries user for parameters for an existing job
 *   in the database to modify. Searches for the job in the database and allows the user
 *   to modify the job's data. Restarts parameter queries if the user's search results in
 *   multiple jobs found.
 *   Title, Company Name, and industry are required parameters for the job search.
 */
void modifyJobs();

/* @brief function for "r" command: queries user for parameters for an existing job
 *   in the database to remove. if the search results in more than one job, it asks the
 *   user to delete all found jobs or cancel.
 *   Title, Company Name, City Location, State Location, and Industry are required parameters for the job search.
 */
void removeJobs();

/* @brief function for "w" command: prints the current database to a file of which the 
 *   name of said file is inputted by the user.
 */
void writeJobs();

/* @brief prints all jobs in a LinkedList of jobs or notifies user that it's empty.
 *   Used after a search has been performed to print the resulting jobs.
 * @param LinkedList* list; list of jobs to be printed
 * @param int type; type of list to be printed: 0 = exact job matches; 1 = close job matches
 */
void printSearchResults(LinkedList*, int);

/* @brief initializes all strings in the global paramList variable with either wildcards, or user input depending on the indicies
 *   given by the parameters.
 * @param int startInd; the index in the paramList to start initializing with user input (included)
 * @param int endInd; the index in the paramList to stop initializing with user input (excluded)
 * @returns Job pointer to a job created using the newly initialized paramList strings as attributes
 */
Job* initializeParams(int, int);

/* @brief checks if a string in the global paramList is invalid, and queries the user for an input for the string
 * @param Job* j; job that will receive the strings in the paramList variable as attributes and will be updated
 * @param int i; index of the parameter in the paramList variable to check
 * @returns Job pointer to the job with the newly updated attribute inputted by the user
 */
Job* invalidParam(Job*, int);

/* @brief formats a string so that the newline character is deleted
 *   Was used more in the last version of the project.
 * @param char* str; string to be formatted
 * @returns formatted version of the parameter str without newlines
 */
char* formatParam( char*);

#endif // PROGRAM_H
