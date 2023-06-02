#ifndef JOB_H
#define JOB_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>


/* Job Summary:
 *    Data Structure for a single Job and all of it's attributes. JobAttr (standing for 
 *      Job Atrributes) make up each category of data a Job can have. Each Job has a list of
 *      attributes that holds pointers to nine attributes that use the JobAttr structure to 
 *      keep track of the data, size, and name of each one.
 *      Methods of these Job files work to create, modify, and print Jobs and JobAttrs
 *   Major changes from v.1: Jobs hold a list of attributes instead of each attribute individually
 */

/* JobAttr struct:
 *   char** data: data of the attribute
 *   int size: size of the 2D data array (number of strings in the array)
 *   char* name: name of the attribute the JobAttr corresponds too
 */
typedef struct JobAttr {
    char** data;
    int size;
    char* name;
} JobAttr;

/* attrType enum:
 *   Not often used, but good for reference. Shows which attribute correspond to
 *   which index in a Job struct's attribute list (attrList). 
 */
enum attrType{
    jobTitle,       //0
    compName,       //1
    cityLoc,        //2
    stateLoc,       //3
    salaryRange,    //4
    industry,       //5
    reqSkill,       //6
    desSkill,       //7
    contactInfo     //8
};

/* JobAttr struct:
 *   JobAttr** attrList: a list of nine pointers that point to JobAttr pointers, one for 
 *      each type of attribute that needs to be kept track of (list of attribute types above).
 */
typedef struct Job {
    JobAttr** attrList;
} Job;

/* @brief allocates memory for a Job struct pointer.
 * @param Job* j: pointer to the Job of which to allocate memory for it and it's list of attributes
 * @returns pointer to the Job created
 */
Job* createJob( Job* );

/* @brief returns the name of the attribute given a number. The numbers 0-8 correspond to 
 * @returns 
 */
char* getAttrName (int );

/* @brief intializes the JobAttr of one of the Job's attributes in it's attrList
 * @param Job* j: pointer to the Job of which to create the JobAttr
 * @param int index: the index of the Job's attribute list that corresponds to the JobAttr to add
 * @param char* data: a string to turn into the JobAttr struct's 2D array of data 
 * @returns pointer to the Job with the newly modified attribute
 */
Job* addJobAttr( Job*, int, char* );

/* @brief calculates the number of rows needed to hold the data of a string for when it's turned into a 
 *   2D array. The number of rows increase when it reaches a comma in the string.
 * @param char* str: the string of which to determine the number of rows
 * @returns the integer value of the rows needed for a data array to hold the string
 */
int calcDataLength( char* );


/* @brief modifies an attribute of a Job given the attribute's index and the new data of the attribute
 * @param Job* j: pointer to the Job of which to modify the JobAttr
 * @param int index: the index of the Job's attribute list that corresponds to the JobAttr to modify
 * @param char* data: a string to turn into the JobAttr struct's 2D array of data
 * @returns pointer to the Job with the newly modified attribute
 */
Job* modifyAttribute(Job* j, int index, char* data);

/* @brief prints all data in each attribute of a Job
 * @param Job* j: pointer to the Job to print
 */
void printJob( Job* );

/* @brief prints the contents of the 2D char array, data, of a JobAttr pointer
 * @param JobAttr* jA: pointer to the JobAttr to print
 */
void printAttr( JobAttr* );

/* @brief sorts the contents of the 2D char array, data, of a JobAttr pointer in alphabetical order
 * @param JobAttr* jA: pointer to the JobAttr to sort
 */
JobAttr* sortAttr( JobAttr* );

/* @brief compares two Jobs to see if they are an exact or close match
 * @param Job* j1: pointer to first Job to compare
 * @param Job* j2: pointer to second Job to compare
 * @returns 0 if Jobs are an exact match, 1 if Jobs are a close match, -1 if Jobs do not match
 */
int compareJobs( Job*, Job* );

/* @brief compares two JobAttr to see if they are an exact or close match
 * @param Job* j1: pointer to first JobAttr to compare
 * @param Job* j2: pointer to second JobAttr to compare
 * @returns 0 if JobAttrs are an exact match, 1 if JobAttrs are a close match, -1 if JobAttrs do not match
 */
int compareAttr( JobAttr*, JobAttr* ); 


#endif // JOB_H