#ifndef UNITTEST_H
#define UNITTEST_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "Job.h"
#include "BinaryTree.h"
#include "FileHandler.h"
#include "LinkedList.h"
#include "Program.h"

/*unitTest summary:
 *  Includes unit tests for most functionality implemented as of project2
 *      was not a part of project1 so it may fail to include some of the testing done
 *      in previous versions.
 *  Includes it's own main function that should NOT be used to compile when running
 *      the main program. It should only be used for testing functionality.
 */

void testStartProgram();
void testJobCreation();
void testFileHandler();
void testBTCreation();
void testBTInsert();
void testBTInsertWithFile();
void testJobCompare();
void testDeleteFromLL();
void testDeleteFromBT();
void testCommands();
void testSearch();
void testLists();
void testAdd();
void testRemove();

#endif // UNITTEST_H