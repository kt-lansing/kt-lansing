
#include "Job.h"
#include "FileHandler.h"
#include "Program.h"

extern void openInFile(char*);
extern BinaryTree* createBTFromInFile();
extern void initializeBT();
extern void startProgram();
extern void closeFiles();

/* Main Summary:
 *   Primary main function (as opposed to unit testing main). Opens the jobs.txt file as an input file 
 *   Itializes the Binary Tree structure which adds all the jobs from jobs.txt into the Binary Tree
 *   Passes the Binary Tree to the program and starts the program.
 */
void main(){
    openInFile("jobs.txt");
    BinaryTree* bt = createBTFromInFile();
    initializeBT(bt);
    startProgram();
    closeFiles();
}
